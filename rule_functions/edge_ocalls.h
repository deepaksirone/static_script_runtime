#ifndef _H_EDGE_OCALLS_H_
#define _H_EDGE_OCALLS_H_
#include <stdint.h>


void *ocall_get_trigger_data(char *trigger_url, int trigger_url_sz, char *rule_params, int *blob_size, uint64_t nonce);

#endif