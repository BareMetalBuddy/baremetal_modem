#ifndef APP_CLI_H_
#define APP_CLI_H_

#include <stdint.h>
#include <stdio.h>
#include "usart.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "queue.h"
#include "router.h"


#define MAX_CMDLINE_ARGS 5
#define MAX_CMDLINE_LENGTH 50
#define TRANSPARENT_MODE  1
#define COMMAND_LINE_MODE 2

typedef void (*command_fn)(int argc, char *argv[]);

typedef struct {
	char* name;
    command_fn function;
} Command;


/*
 * Prototypes
 * */

void command_line_interface_init(void);
void command_line_interface(void);
void execute_command(char *line);

void cmd_help(int argc, char *argv[]);
void cmd_apn(int argc, char *argv[]);
void cmd_connection(int argc, char *argv[]);
void cmd_set_parameters(int argc, char *argv[]);


#endif /* APP_CLI_H_ */
