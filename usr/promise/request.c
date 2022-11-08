/******************** (C) COPYRIGHT 2022 INCUBECN *****************************
* File Name          : request.c
* Author             : Tiko Zhong
* Date First Issued  : 26/oct,2022
* Description        : This file provides a set of functions needed to manage the
*                      stepper ramp generator
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "request.h"
#include <string.h>
#include <stdio.h>
#include "board.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static s32 request_Add (requestRsrc_t*, const char* req, u32 timeout, cb_resp cb, void* id);
static void request_PeriodJob(requestRsrc_t*);
static void request_AsyncJob(requestRsrc_t*, const char* RECV_LINE);

/*******************************************************************************
* Function Name  : aplentalQT_periodJob
* Description    : rampCmd function commands
* Input          : - CMD, command line
				 : - brdAddr, board address
				 : - print function
* Output         : None
* Return         : None
*******************************************************************************/
void setup_request(requestDev_t* dev, void (*xPrintS)(const char* ORG))
{
	requestRsrc_t* r = &dev->rsrc;
	r->xPrintS = xPrintS;

	dev->Add = request_Add;
	dev->PeriodJob = request_PeriodJob;
	dev->AsyncJob = request_AsyncJob;

	RingBuffer_Init(&r->reqRB, r->cmdPool, 1, REQUEST_POOL_LEN);
	RingBuffer_Init(&r->respRB, r->respPool, sizeof(request_resp_t), REQUEST_DEPTH);

	r->squ = 1;
}

//u16 fetchLineFromRingBuffer(RINGBUFF_T* rb, char* line, u16 len);
static s32 request_Add (requestRsrc_t* r, const char* req, u32 timeout, cb_resp cb, void* id){
	request_resp_t obj;
	s32 i = strlen(req);

	if( i<=0 ){	return 0;	}
	obj.timeout = timeout;
	obj.cb = cb;
	obj.id = id;
	obj.reqLen = i;
	RingBuffer_InsertMult(&r->reqRB, req, i);
	RingBuffer_Insert(&r->respRB, &obj);
	return 0;
}

#define REQUEST_BUFF_LEN 64
static void request_PeriodJob(requestRsrc_t* r){
	s32 i;
	char cmdReq[REQUEST_BUFF_LEN] = {0};
	switch(r->squ){
	case 0:
		break;
	case 1:
		if(RingBuffer_GetCount(&r->respRB) <= 0){	break;	}
		memset(&r->curResp, 0, sizeof(request_resp_t));
		RingBuffer_Pop(&r->respRB, &r->curResp);
		i = RingBuffer_PopMult(&r->reqRB, cmdReq, r->curResp.reqLen);
		r->xPrintS(cmdReq);
		r->squ++;
		r->tick = 0;
		break;
	case 2:
		//r->tick += tick;	// move to tick_irq
		if(r->tick >= r->curResp.timeout){
			if(r->curResp.cb){
				r->curResp.cb(r->curResp.id, "+$timeout@req\r\n");
			}
			r->squ = 1;
		}
		break;
	}
}

static void request_AsyncJob(requestRsrc_t* r, const char* RECV_LINE){
	if(r->squ != 2){	return;	}
	//else if(strncmp(RECV_LINE, "+msg@", strlen("+msg@")) == 0){	return;	}
	else if(r->curResp.cb){
		r->curResp.cb(r->curResp.id, RECV_LINE);
	}
	r->squ = 1;
}


/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
