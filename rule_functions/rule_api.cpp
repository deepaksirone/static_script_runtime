#include "fetch_trigger_data.h"
#include "../library.h"
#include <stdio.h>

using namespace rapidjson;

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

    printf("[Rule API call] Weather_tomorrowsForecastCallsFor_ConditionImageURL: %s\n", (char *)parsed_trigger_data[0]["ConditionImageUrl"].GetString());
    return (char *)parsed_trigger_data[0]["ConditionImageUrl"].GetString();
    //return (char *)"ConditionImageUrl: Data here\n";
}

C_LIBRARY_EXPORT void Smartthings_turnOnSmartthings_skip() 
{
    action_skipped[0] = 1;
}
