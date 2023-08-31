#include "cli.h"
/*
 * Command line interface library.
 * A pool of basic command to set configuration parameters
 * */

static GPIO_Handler_t cli_tx;
static GPIO_Handler_t cli_rx;
static USART_Handler_t usart1;

static uint8_t input_data_from_user[MAX_CMDLINE_LENGTH];
static uint8_t in = 0;
static uint8_t cmd_command_mode = COMMAND_LINE_MODE;

/*List of supported commands*/
Command command_table[] = {
    {"help", cmd_help},
	{"set_apn",cmd_apn},
	{"set_connection",cmd_connection},
	{"parameters",cmd_set_parameters},
    {NULL, NULL}
};

/* printf implementation */
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
	in = 0;
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
	    	if (strlen((const char *)input_data_from_user) > 0){
	    		if(cmd_command_mode == TRANSPARENT_MODE){
	    			if(strcmp((const char*)"+++",(const char*)input_data_from_user)!=0){
	    				static_queue_push_method(input_data_from_user);
	    			}else{
	    				cmd_command_mode = COMMAND_LINE_MODE;
	    			}
	    		}
	    		else{
	    			execute_command((char *)input_data_from_user);
	    		}
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

/*Help Command : displayed all supported commands*/
void cmd_help(int argc, char *argv[]) {
    printf("Available commands:\n");
    for (Command *command = command_table; command->name != NULL; command++) {
        printf("  %s\n", command->name);
    }
}

/*APN command: used to set access point network*/
void cmd_apn(int argc, char *argv[])
{
	Package pkg;

	if (argc < 2) {
		printf("Use: set_apn [value]\n");
		return;
	}
	if(strlen(argv[1])>0){
		printf("apn: %s\n",(char*)argv[1]);
		pkg.data1 = (uint8_t*)argv[1];
		router_dynamic_fifo_add(&pkg,1);
	}else{
		printf("error apn value\n");
	}
}

/*set connection parameters :protocol address and port*/
void cmd_connection(int argc, char *argv[])
{
	Package pkg;

	if (argc < 4) {
		printf("Use: set_connection [TCP/UDP] [xxx.xxx.xxx.xxx] [xxxx]\n");
		return;
	}
	if(strlen(argv[1])>0 && strlen(argv[2])>0 && strlen(argv[3])>0){
		printf("connection: %s %s %s\n",(char*)argv[1],(char*)argv[2],(char*)argv[3]);
		pkg.data1 = (uint8_t*)argv[1];
		pkg.data2 = (uint8_t*)argv[2];
		pkg.data3 = (uint8_t*)argv[3];
		router_dynamic_fifo_add(&pkg,2);

	}else{
		printf("error connection parameters");
	}
}

/*If the user call this function, the modem enter into transparent mode
 * In order to change mode, the user must to send the sequence +++*/
void cmd_set_parameters(int argc, char *argv[])
{
	Package pkg;
	cmd_command_mode = TRANSPARENT_MODE;
	printf("%s\n",(char*)argv[1]);
	pkg.data1 = (uint8_t*)argv[1]; // don't need ask for dynamic memory , it is enough just a copy of pointers
	router_dynamic_fifo_add(&pkg,0);
}


void USART1_IRQHandler()
{
	usart_receive(&usart1);
}
