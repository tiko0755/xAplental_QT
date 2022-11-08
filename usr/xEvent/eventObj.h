/**********************************************************
filename: eventObj.h
**********************************************************/
#ifndef _EVENT_OBJ_H_
#define _EVENT_OBJ_H_

#define EVNT_TAB_LEN	8	// one item use 32 bytes

typedef void (*cb_any)(int argc, ...);
typedef void (*cb_str)(const char*, ...);

// event functions
#define EVNT_NAME_LEN 16
#define EVNT_CB_LEN 4
typedef struct{
	char evnt[EVNT_NAME_LEN];
	cb_any cb[EVNT_CB_LEN];
}EventCBs_t;

s32 evntBind(const char* EVNT, cb_any cb);
s32 evntRemove(const char* EVNT, cb_any cb);

cb_any evntGet(const char* EVNT);

void evntExeSync(const char* EVNT, ...);		// execute immediatly
void evntExeAsync(const char* EVNT);	// put in event table only
void evntNextTick(const char* EVNT);	// execute asynchronous

#endif

