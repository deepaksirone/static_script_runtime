#include "fetch_trigger_data.h"
#include "../syscall_keystone.h"
#include "../library.h"
#include "edge_ocalls.h"


//static std::string rule_params[MAX_TRIGGERS] = JSON_PARAMS;

using namespace rapidjson;

Document parsed_trigger_data[MAX_TRIGGERS];
Document parsed_action_data[MAX_ACTIONS];
int action_skipped[MAX_ACTIONS];


static uint64_t get_unix_time() {
	uint64_t epoch_seconds = SYSCALL_0(SYSCALL_GET_TIME);
	return epoch_seconds;
}

static bool validate_timestamp(uint64_t timestamp, uint64_t timeout)
{
	uintptr_t current_timestamp = get_unix_time();
	//printf("Current timestamp: %lu, timestamp: %lu, timeout: %lu\n", current_timestamp, timestamp, timeout);
	if (current_timestamp > timestamp) {
		return (current_timestamp - timestamp) < timeout;
	}
		
	return (timestamp - current_timestamp) < timeout;

}

	
C_LIBRARY_EXPORT int validate_and_init_trigger_data(int trig_id, char *trigger_data, uintptr_t nonce, char *trigger_url, int trigger_url_sz, char *rule_params, uint64_t timeout)
{
	//clear_data();
	Document trig_data;
	Document json_schema;

	if (trig_id >= MAX_TRIGGERS) {
		return -1;
	}


	if (json_schema.Parse(rule_params).HasParseError()) {
		// Invalid Rule Params
		printf("Invalid Rule Params: %s\n", rule_params);
		return -2;
	}

	if (trig_data.Parse(trigger_data).HasParseError()) {
		return -3;
	}

	if (!trig_data.HasMember("nonce") || !trig_data.HasMember("data")) {
		return -4;
	}

	Value& s = trig_data["nonce"];
	uint64_t n = s.GetUint64();

	if (SYSCALL_1(SYSCALL_VERIFY_NONCE, n) == 0) {
		printf("[Validate] Nonce verifiation failed!\n");
	}
	/*if (nonce != n) {
		printf("[Validate] Nonce validation failed\n");
		return -5;
	}*/

	Value& timest = trig_data["timestamp"];
	uint64_t timestamp = timest.GetUint64();

	if (!validate_timestamp(timestamp, timeout)) {
		printf("[Validate] Timestamp validation failed\n");
		return -6;
	}


	for (Value::MemberIterator itr = json_schema.MemberBegin(); itr != json_schema.MemberEnd(); ++itr) {

		printf("[Validate] Checking for field: %s\n", itr->name.GetString());
		Value::MemberIterator val = trig_data.FindMember(itr->name.GetString());
		if (val == trig_data.MemberEnd()) {
			printf("[Validate] Field not found\n");
			return -7;
		}
		
		if (val->value != itr->value) {
			printf("[Validate] Field not a match\n");
			return -8;
		}
	}

	if (parsed_trigger_data[trig_id].Parse(trig_data["data"].GetString()).HasParseError()) {
		printf("Failed to store parsed trigger data\n");
		return -9;
	}
	//parsed_trigger_data[trig_id] = trigger_data;

	return 1;

}

// Assumes that there is just one trigger service and it is already parsed at parsed_trigger_data[0] 
C_LIBRARY_EXPORT int format_action_data(char **action_data_json, int num_actions, char **ingredients, int num_ingredients)
{
	//TODO: Complete the formatting
	/*char ingredient[100];

	for (int i = 0; i < num_actions; i++) {
		for(int j = 0; j < num_ingredients; j++) {
			snprintf(ingredient, 100, "{{%s}}", ingredients[j]);
			
		}
	}*/

	//Just loading the action data template for now
	for (int i = 0; i < num_actions; i++) {
		if (parsed_action_data[i].Parse(action_data_json[i]).HasParseError()) {
			printf("Failed to store parsed action data: %d\n", i);
			return -1;
		}
	}

	return 0;

}

C_LIBRARY_EXPORT int *get_action_skip_vector()
{
	return (int *)&action_skipped;
}

C_LIBRARY_EXPORT char *get_action_data(int i, int32_t *size, char *action_params, int32_t action_param_sz) 
{
	Value s;
	s.SetString(action_params, action_param_sz);
	parsed_action_data[i].AddMember("action_service_params", s, parsed_action_data[i].GetAllocator());

	uintptr_t nonce = SYSCALL_0(SYSCALL_GENRAND_WORD);
	Value nonceval;
	nonceval.SetUint64(nonce);
	parsed_action_data[i].AddMember("action_service_nonce", nonceval, parsed_action_data[i].GetAllocator());

	uint64_t timestamp = get_unix_time();
	Value timestamp_val;
	timestamp_val.SetUint64(timestamp);
	parsed_action_data[i].AddMember("action_service_timestamp", timestamp_val, parsed_action_data[i].GetAllocator());

	StringBuffer buffer;
	buffer.Clear();
	Writer<StringBuffer> writer(buffer);
	parsed_action_data[i].Accept(writer);
	*size = strlen(buffer.GetString());

	return strdup(buffer.GetString());
}

C_LIBRARY_EXPORT void clear_data()
{
	//TODO: Clear Parsed JSON
	for(int i = 0; i < MAX_TRIGGERS; i++) {
		parsed_trigger_data[i].clear_and_init_extern();
	}

	for(int i = 0; i < MAX_ACTIONS; i++) {
		parsed_action_data[i].clear_and_init_extern();
	}
}
