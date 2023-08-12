#include "cli.h"
/*
 * Command line interface library.
 * A pool of basic command to set configuration parameters
 * */

static GPIO_Handler_t cli_tx;
static GPIO_Handler_t cli_rx;
static USART_Handler_t usart1;

uint8_t input_data_from_user[MAX_CMDLINE_LENGTH];
uint8_t in = 0;

Command command_table[] = {
    {"help", cmd_help},
	{"apn",cmd_apn},
	{"ip",cmd_ip},
	{"port",cmd_port},
	{"protocol",cmd_protocol},
    {NULL, NULL}
};

/*
 * printf implementation
 * */
int __io_putchar(int ch)
{
	usart_tx(&usart1,(uint8_t)ch);
	return ch;
}


/*Configure all hardware necessary for serial port used by command line interface*/
void command_line_interface_init(void)
{
	rcc_enable_clock(GPIO_PORT_A);
	gpio_init(&cli_tx,GPIOA_BASE_ADDRESS,GPIO_pin_9,GPIO_Alternate_function_output_Push_pull,GPIO_Output_mode_max_speed_10_MHz);
	gpio_config(&cli_tx);
	gpio_init(&cli_rx,GPIOA_BASE_ADDRESS,GPIO_pin_10,GPIO_Floating_input,GPIO_Input_mode);
	gpio_config(&cli_rx);

	rcc_enable_clock(SERIAL_PORT_1);
	usart_init(&usart1,USART1_BASE_ADDRESS,BAUDRATE,0,0,0,0);
	usart_config(&usart1);
	usart_interrupt_enable(&usart1);

	// configure interruption
	nvic_set_irq_priority(2,SERIAL_PORT_1);
	nvic_enable_irq(SERIAL_PORT_1);
}

void command_line_interface(void)
{
	input_data_from_user[in] = '\0';
	while(usart_available(&usart1)>0){
		input_data_from_user[in] = usart_read(&usart1);
	    if(input_data_from_user[in] != '\r'){
	    	in++;
	    }
	    else
	    {
	    	input_data_from_user[in] = '\0';
	    	in = 0;
	    	if (strlen((const char *)input_data_from_user) > 0) {
	    		execute_command((char *)input_data_from_user);
	    	}
	    }
	}
}

void execute_command(char *line)
{
    char *argv[MAX_CMDLINE_ARGS];
    int argc = 0;

    char *token = strtok(line, " ");
    while (token != NULL && argc < MAX_CMDLINE_ARGS) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    for (Command *command = command_table; command->name != NULL; command++) {
        if (strcmp(argv[0], command->name) == 0) {
            command->function(argc, argv);
            return;
        }
    }

    printf("unknown command: %s\n", argv[0]);
}

void cmd_help(int argc, char *argv[]) {
    printf("Available commands:\n");
    for (Command *command = command_table; command->name != NULL; command++) {
        printf("  %s\n", command->name);
    }
}

void cmd_apn(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Use: apn [value]\n");
		return;
	}
	if(strlen(argv[1])>0){
		printf("apn: %s\n",(char*)argv[1]);
	}else{
		printf("error apn value\n");
	}
}

void cmd_ip(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Use: ip [value]\n");
		return;
	}
	if(strlen(argv[1])>0){
		printf("ip: %s\n",(char*)argv[1]);
	}else{
		printf("error");
	}
}

void cmd_port(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Use: port [value]\n");
		return;
	}
	if(strlen(argv[1])>0){
		printf("port: %s\n",(char*)argv[1]);
	}else{
		printf("error");
	}
}

void cmd_protocol(int argc, char *argv[])
{

}


void USART1_IRQHandler()
{
	usart_receive(&usart1);
}
