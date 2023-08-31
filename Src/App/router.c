#include "router.h"


RouterControl router_control = {NULL,NULL,NULL,0,0,0};

/*
* router_dynamic_fifo_add
* Insert item into the list.
* @brief list
*/
uint8_t router_dynamic_fifo_add(Package * package, uint8_t list){

  DinamicFIFOList * pNodo = (DinamicFIFOList*)malloc(sizeof(DinamicFIFOList));
  pNodo->next    = NULL;
  pNodo->package = package;

  DinamicFIFOList * runner = NULL;

  switch(list){
      case 0:
        router_control.size_create++;
        if(router_control.create==NULL){
        	router_control.create = pNodo ;
        } else {
        	runner = router_control.create;
        }
        break;
      case 1:
    	  router_control.size_status++;
        if(router_control.status == NULL){
        	router_control.status = pNodo;
        } else {
        	runner = router_control.status;
        }
        break;
      case 2:
    	  router_control.size_monitoring++;
        if(router_control.monitoring == NULL){
        	router_control.monitoring = pNodo;
        } else {
        	runner = router_control.monitoring;
        }
        break;
    }

  if(runner == NULL){
    return 1 ; // was inserted!
  }

  /* looking for the last position and insert */
  for(;runner->next != NULL; runner = runner->next){ ; }
  runner->next = pNodo;

  return 1;
}
/******************************************************************************
* router_dynamic_fifo_get
* Return the first item of the list, also destroy the container.
* @brief list
*/
Package* router_dynamic_fifo_get(uint8_t list){

    Package * return_package = NULL;

    switch(list)
    {

    case 0:
    	if(router_control.create){
    		router_control.size_create--;
    		return_package = router_control.create->package ;
    		DinamicFIFOList * free_me   = router_control.create;
    		router_control.create = router_control.create->next;
    		free(free_me);
    	}
    	break;

    case 1:
    	if(router_control.status){
    		router_control.size_status--;
    		return_package = router_control.status->package;
    		DinamicFIFOList * free_me   = router_control.status;
    		router_control.status = router_control.status->next;
    		free(free_me);
    	}
    	break;

    case 2:
    	if(router_control.monitoring){
    		router_control.size_monitoring--;
    		return_package = router_control.monitoring->package;
    		DinamicFIFOList * free_me   = router_control.monitoring;
    		router_control.monitoring = router_control.monitoring->next;
    		free(free_me);
    	}
    	break;

    default:
      break;

    }

    return return_package;
}
