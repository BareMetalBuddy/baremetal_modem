#include "at_command.h"

static CONFIG_t config;

result_codes at_command_init_server_configuration(void)
{
	//sprintf(config.server,"AT+CIPOPEN=0,%s,%s,%s\r",1);
	return 1;
}

result_codes at_command_init_apn_configuration(void)
{
	//sprintf(config.apn,"AT+CGDCONT=1,\"IP\",\"%s\"\r",1);
	return 1;
}

result_codes at_command_http_init(void)
{
	return 1;//return (modem_at_command_write((uint8_t*)"AT+HTTPINIT\r",at_http_init_state,20));
}

/*Set HTTP Parameters value*/
result_codes at_command_http_set_url(void)
{
	return 1;//return (modem_at_command_write((uint8_t*)"AT+HTTPPARA=\"URL\",\"http://152.44.38.81:5000/time\"\r",at_http_set_url_state,20));
}

result_codes at_command_http_get_request(void)
{
	return 1;//return (modem_at_command_write((uint8_t*)"AT+HTTPACTION=0\r",at_http_get_request_state,20));
}

result_codes at_command_http_read_content(void)
{
	return 1; //return (modem_at_command_write((uint8_t*)"AT+HTTPREAD=0,200\r",at_http_read_content_state,20));
}

result_codes at_command_http_stop_service(void)
{
	return 1;//return (modem_at_command_write((uint8_t*)"AT+HTTPTERM\r",at_http_stop_service_state,20));
}

void at_command_init(void)
{
	modem_init();
}

result_codes at_command_reset(void)
{
	return 1;
}

result_codes at_command_test(void)
{
	return (modem_at_command_write((uint8_t*)"AT\r",at_test_state,10));
}

result_codes at_command_echo(void)
{
	return (modem_at_command_write((uint8_t*)"ATE0\r",at_echo_state,10));
}

result_codes at_command_cpin(void)
{
	return (modem_at_command_write((uint8_t*)"AT+CPIN?\r",at_cpin_state,10));
}

result_codes at_command_creg(void)
{
	return (modem_at_command_write((uint8_t*)"AT+CREG?\r",at_creg_state,10));
}

/*Ask for Packet domain attach or detach. 0 – detached,  1 – attached */
result_codes at_command_cgatt(void)
{
	return (modem_at_command_write((uint8_t*)"AT+CGATT?\r",at_cgatt_state,10));
}

/*If result is detached, write value to attach */
result_codes at_command_set_cgatt(void)
{
	return 1; //return (modem_at_command_write((uint8_t*)"AT+CGATT=1\r",at_cgatt_set_state,10));
}

result_codes at_command_cgdcont(void) // set APN context
{
	return (modem_at_command_write(config.apn,at_cgdcont_state,20));
}

result_codes at_command_wait_new_msg(void)
{
	// call to static_queue_pop_method(config.user_msg_to_send)
	result_codes value = OK;
	return value;
}

/* Start TCPIP service. If the result of operation is 0, is a success, other value is failure.*/
result_codes at_command_netopen(void)
{
	return (modem_at_command_write((uint8_t*)"AT+NETOPEN\r",at_netopen_state,20));
}

/* Setup TCP/UDP client socket connection :
 * 0 - Operation succeeded | 1 - Network failure
 * */
result_codes at_command_cipopen(void)
{
	return (modem_at_command_write(config.server,at_cipopen_state,120));
}

/* Send TCP/UDP data with changeable length*/
result_codes at_command_cipsend(void)
{
	return (modem_at_command_write((uint8_t*)"AT+CIPSEND=0,\r",at_cipsend_state,10));
}

result_codes at_command_send_data(void)
{
	return(modem_at_command_write((uint8_t*)"Hello World\x1A\r",at_send_data_state,10));
}

result_codes at_command_cipclose(void) // to close TCP client socket connection
{
	return 1; (modem_at_command_write((uint8_t*)"AT+CIPCLOSE=0\r",at_cipclose_state,10));
}

result_codes at_command_netclose(void) // stop TCPIP service
{
	return (modem_at_command_write((uint8_t*)"AT+NETCLOSE\r",at_netclose_state,10));
}

result_codes at_command_qnetopen(void)
{
	return (modem_at_command_write((uint8_t*)"AT+NETOPEN?\r",at_qnetopen_state,10));
}

result_codes at_check_response(uint8_t at_cmd_id,uint8_t* response)
{
	result_codes result = WAIT;

	switch(at_cmd_id)
	{
	case at_test_state:
	case at_echo_state:
	//case at_cgatt_set_state:
	case at_cgdcont_state:
	//case at_http_init_state:
	//case at_http_set_url_state:
	//case at_http_stop_service_state:
	case at_send_data_state:
		if(strstr((const char*)response,(const char*)"OK")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"ERROR")){
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	case at_cpin_state:
		if(strstr((const char*)response,(const char*)"+CPIN: READY")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"ERROR")){
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	case at_creg_state:
		if(strstr((const char *)response,(const char *)"+CREG: 0,1") || strstr((const char *)response, (const char *)"+CREG: 0,5")){
			result = OK;
		}
		else if(strstr((const char *)response,(const char *)"+CREG: 0,0") || strstr((const char *)response, (const char *)"+CREG: 0,2")){
			result = WAIT;
		}
		else if(strstr((const char *)response,(const char *)"+CREG: 0,3") || strstr((const char *)response, (const char *)"+CREG: 0,4")){
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	case at_cgatt_state:
		if(strstr((const char*)response,(const char*)"+CGATT: 1")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"+CGATT: 0")){
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	case at_qnetopen_state:
		if(strstr((const char*)response,(const char*)"+NETOPEN: 0")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"+NETOPEN: 1")) {
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	/*case at_http_get_request_state:
		if(strstr((const char*)response,(const char*)"+HTTPACTION: 0,200,30")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"ERROR") || strstr((const char*)response,(const char*)"HTTPACTION: 0,714,0")){
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;*/

	/*case at_http_read_content_state:
		if(strstr((const char*)response,(const char*)"+HTTPREAD: DATA,30")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"ERROR")){
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;*/

	case at_wait_new_msg_state: // at_wait_new_msg_state , no parameters to check
		break;

	case at_netopen_state:
		if(strstr((const char*)response,(const char*)"+NETOPEN: 0")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"+IP ERROR: Network is already opened")) {
			result = FAIL;
		}
		else{
			result = WAIT; // in case the result was +NETOPEN but with a value different than zero
		}
		break;

	case at_cipopen_state:
		if(strstr((const char*)response,(const char*)"+CIPOPEN: 0,0")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"+CIPOPEN: 0,1")) {
			result = FAIL;
		}
		else{
			result = WAIT; 	// if the result of +CIPOPEN is different than zero also must be considerer as an error
		}
		break;

	case at_cipsend_state:
		if(strstr((const char*)response,(const char*)">")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"ERROR")) {
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	case at_cipclose_state:
		if(strstr((const char*)response,(const char*)"+CIPCLOSE: 0,0")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"ERROR")) {
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	case at_netclose_state:
		if(strstr((const char*)response,(const char*)"+NETCLOSE: 0")){
			result = OK;
		}
		else if(strstr((const char*)response,(const char*)"+NETCLOSE: 2")) {
			result = FAIL;
		}
		else{
			result = WAIT;
		}
		break;

	default:
		break;
	}

	return result;
}




