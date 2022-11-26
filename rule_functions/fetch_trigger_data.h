#ifndef _H_FETCH_TRIGGER_DATA_H_
#define _H_FETCH_TRIGGER_DATA_H_
#define RAPIDJSON_HAS_CXX11_RVALUE_REFS 1

#include "../library.h"
#include <stdint.h>

#include "rule_params.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

extern rapidjson::Document parsed_trigger_data[MAX_TRIGGERS];
extern rapidjson::Document parsed_action_data[MAX_ACTIONS];
//extern char * parsed_trigger_data[MAX_TRIGGERS];
//extern char * parsed_action_data[MAX_ACTIONS];
extern int action_skipped[MAX_ACTIONS];

C_LIBRARY_EXPORT int validate_and_init_trigger_data(int trig_id, char *trigger_data, uintptr_t nonce, char *trigger_url, int trigger_url_sz, char *rule_params, uint64_t timeout);
C_LIBRARY_EXPORT void clear_data();
C_LIBRARY_EXPORT char *get_action_data(int i, int32_t *size, char *action_params, int32_t action_param_sz);
C_LIBRARY_EXPORT int *get_action_skip_vector(); 



#endif