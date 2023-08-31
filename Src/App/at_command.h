#ifndef APP_AT_COMMAND_H_
#define APP_AT_COMMAND_H_

/*specific at commands library to handler modem SIMCOM SIM7600E */

#include <stdint.h>
#include <stdio.h>
#include "modem.h"

typedef struct{
	uint8_t apn[96];
	uint8_t server[96];
	uint8_t user_msg_to_send[96];
}CONFIG_t;

typedef enum {
	OK=0,
	FAIL,
	WAIT,
}result_codes;

typedef enum {
	at_test_state=0,
	at_echo_state,
	at_cpin_state,
	at_creg_state,
	at_cgatt_state,
	at_cgdcont_state,
	at_qnetopen_state,
	at_wait_new_msg_state,
	at_netopen_state,
	at_cipopen_state,
	at_cipsend_state,
	at_send_data_state,
	at_cipclose_state,
	at_netclose_state
}socket_state_machine_codes;

void at_command_init(void);
result_codes at_command_init_server_configuration(void);
result_codes at_command_init_apn_configuration(void);
result_codes at_command_reset(void);

result_codes at_command_test(void);
result_codes at_command_echo(void);
result_codes at_command_cpin(void);
result_codes at_command_creg(void);
result_codes at_command_cgatt(void);
result_codes at_command_set_cgatt(void);
result_codes at_command_cgdcont(void);
result_codes at_command_qnetopen(void);
///////////////////////////////////////////////

result_codes at_command_http_init(void);
result_codes at_command_http_set_url(void);
result_codes at_command_http_get_request(void);
result_codes at_command_http_read_content(void);
result_codes at_command_http_stop_service(void);

///////////////////////////////////////////////
result_codes at_command_wait_new_msg(void);

result_codes at_command_netopen(void);
result_codes at_command_cipopen(void);
result_codes at_command_cipsend(void);
result_codes at_command_send_data(void);
result_codes at_command_cipclose(void);
result_codes at_command_netclose(void);

/////////////////////////////////////////////////////////////

result_codes at_check_response(uint8_t at_cmd_id,uint8_t* response);

#endif /* APP_AT_COMMAND_H_ */
