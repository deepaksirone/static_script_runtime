#include "fetch_trigger_data.h"
#include "../library.h"
#include <stdio.h>

using namespace rapidjson;

static char *call_length = "123";

C_LIBRARY_EXPORT char *Weather_tomorrowsForecastCallsFor_ConditionImageURL()
{
    //TESTONLY
    /*Document doc;
    Document value;
    if (doc.Parse(parsed_trigger_data[0]).HasParseError()) {
        printf("[Rule API call] Error Parsing JSON\n");
        return NULL;
    }

    if (value.Parse(doc["data"].GetString()).HasParseError()) {
        printf("[Rule API call] Error Parsing value JSON\n");
        return NULL;
    }*/
    
    //printf("[Rule API call] Weather_tomorrowsForecastCallsFor_ConditionImageURL: %s\n", (char *)parsed_trigger_data[0]["ConditionImageUrl"].GetString());
    return (char *)parsed_trigger_data[0]["ConditionImageUrl"].GetString();
    //return (char *)"ConditionImageUrl: Data here\n";
}

C_LIBRARY_EXPORT void Smartthings_turnOnSmartthings_skip() 
{
    action_skipped[0] = 1;
}

C_LIBRARY_EXPORT char *AndroidPhone_placeAPhoneCall_CallLength() {

    return call_length;
    
    if (parsed_trigger_data[0]["AndroidPhone"].IsString()) {
        return call_length;
    }
    return (char *)parsed_trigger_data[0]["CallLength"].GetString();
}

C_LIBRARY_EXPORT void GoogleCalendar_addDetailedEvent_setEndTime(char *end_time) {
    rapidjson::Value::MemberIterator endtime_member = parsed_action_data[0]["GoogleCalendar"].FindMember("EndTime");
    if (endtime_member != parsed_action_data[0]["GoogleCalendar"].MemberEnd()) {
        endtime_member->value.SetString(end_time, parsed_action_data[0].GetAllocator());
    }
}