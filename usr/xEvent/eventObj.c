/******************** (C) COPYRIGHT 2015 INCUBECN *****************************
* File Name          : misc.c
* Author             : Tiko Zhong
* Date First Issued  : 07/03/201
* Description        : 
*                      
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "eventObj.h"
#include "string.h"
#include "stdio.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static EventCBs_t eventTab[EVNT_TAB_LEN] = {0};

/* Private function prototypes -----------------------------------------------*/
/*******************************************************************************
* Function Name  : evntBind
* Description    :
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
s32 evntBind(const char* EVNT, cb_any cb){
	u8 i,j;
	for(i=0;i<EVNT_TAB_LEN;i++){
		if(strlen(eventTab[i].evnt) > 0){	continue;	}
		for(j=0;j<EVNT_CB_LEN;j++){
			if(eventTab[i].cb[j] != NULL){	continue;	}
			strcpy(eventTab[i].evnt, EVNT);
			eventTab[i].cb[j] = cb;
			return i;
		}
	}
	return -1;
}

/*******************************************************************************
* Function Name  : evntExeSync
* Description    : execute immediatly
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void evntExeSync(const char* EVNT, ...){
	u8 i,j;
	s16 len;
	if(strlen(EVNT) <= 0)	return;
	for(i=0;i<EVNT_TAB_LEN;i++){
		if(strncmp(EVNT, eventTab[i].evnt, strlen(eventTab[i].evnt)) != 0){	continue;	}
		len = strlen(eventTab[i].evnt);
		for(j=0;j<EVNT_CB_LEN;j++){
			if(eventTab[i].cb[j] == NULL){	continue;	}
			return i;
		}
	}
}

cb_any evntGet(const char* EVNT){
	u8 i,j;
	s16 len;
	if(strlen(EVNT) <= 0)	return;
	for(i=0;i<EVNT_TAB_LEN;i++){
		if(strncmp(EVNT, eventTab[i].evnt, strlen(eventTab[i].evnt)) != 0){	continue;	}
		len = strlen(eventTab[i].evnt);
		for(j=0;j<EVNT_CB_LEN;j++){
			if(eventTab[i].cb[j] == NULL){	continue;	}
//			eventTab[i].cb[j]();
			return i;
		}
	}
}

/*******************************************************************************
* Function Name  : evntExeAsync
* Description    : put in event table only
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void evntExeAsync(const char* EVNT){

}

/*******************************************************************************
* Function Name  : evntNextTick
* Description    : execute asynchronous
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void evntNextTick(const char* EVNT){

}





/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
