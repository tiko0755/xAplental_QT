/******************** (C) COPYRIGHT 2022 INCUBECN *****************************
* File Name          : script_demo.c
* Author             : Tiko Zhong
* Date First Issued  : 09/21,2022
* Description        : This file provides a set of functions needed to manage the
*                      stepper ramp generator
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "script_demo.h"

const char DISCONNECT[] = {
	"start 'disconnect\r\n';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"req '2.m0.homing(64000)' 50;"
	"req '2.m1.homing(64000)' 50;"

	"move r0 100;"
"loopx:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch 'm0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loopx;"
	"jmp $timeout;"
"$$:"

	"move r0 100;"
"loop1:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch 'm1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"
	// cap pen carrier goes to standby position
	"req '1.output.writepin(2,1,3,0)\r\n' 50;"
	"move r0 80;"
"loop2:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop2;"
	"jmp $timeout;"
"$$:"

	// POGO disconnect
	"req '1.output.writepin(4,1,5,0)\r\n' 50;"
	"move r0 80;"
"loop3:"
	"req '1.input.readpin(12,4)\r\n' 50;"
	"res.switch '(12,1,4,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop3;"
	"jmp $timeout;"
"$$:"

	// before press carrier goes up, 下压之前的干涉查询
	"move r0 80;"
"loop4:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop4;"
	"jmp $timeout;"
"$$:"

	// press carrier goes up
	"req '1.output.writepin(6,1,7,0)\r\n' 50;"
	"move r0 80;"
"loop5:"
	"req '1.input.readpin(13,5)\r\n' 50;"
	"res.switch '(13,1,5,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop4;"
	"jmp $timeout;"
"$$:"

//	"req '2.m1.pos()\r\n' 50;"
	"req '1.output.writepin(0,1,1,0)\r\n' 50;"
	"move r0 80;"
"loop6:"
	"req '1.input.readpin(10,2)\r\n' 50;"
	"res.switch '(10,1,2,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop6;"
	"jmp $timeout;"
"$$:"

	"print '+ok@disconnect\r\n';"
	"jmp $90;"
"$timeout:"
	"print '+timeout@disconnect\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char CONNECT[] = {
	"start 'connect\r\n';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"req '2.m1.homing(64000)' 50;"
	"req '2.m0.homing(64000)' 50;"

	"move r0 80;"
"loop1:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch 'm0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"

	"move r0 80;"
"loop2:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch 'm1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop2;"
	"jmp $timeout;"
"$$:"

	"move r0 80;"
"loop3:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop3;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(6,0,7,1)\r\n' 50;"
	"move r0 80;"
"loop4:"
	"req '1.input.readpin(13,5)\r\n' 50;"
	"res.switch '(13,0,5,1)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop4;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(4,0,5,1)\r\n' 50;"
	"move r0 80;"
"loop5:"
	"req '1.input.readpin(12,4)\r\n' 50;"
	"res.switch '(12,0,4,1)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop5;"
	"jmp $timeout;"
"$$:"

	"print '+ok@connect\r\n';"
	"jmp $90;"
"$timeout:"
	"print '+timeout@connect\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char BUTTON_PUSH[] = {
	"start 'button.push %d\r\n' r7;"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '2.m1.pos(0)' $$;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(0,0,1,1)\r\n' 50;"
	"move r0 80;"
"loop1:"
	"req '1.input.readpin(10,2)\r\n' 50;"
	"res.switch '(10,0,2,1)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"

	"req '2.m1.moveto(26800,64700)\r\n' 50;"
	"move r0 80;"
"loop2:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '2.m1.pos(26800)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop2;"
	"jmp $timeout;"
"$$:"

	"req '2.m1.homing(64000)\r\n' 50;"
	"move r0 80;"
"loop3:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '2.m1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop3;"
	"jmp $timeout;"
"$$:"

	"print '+ok@button.push\r\n';"
	"jmp $90;"
"$timeout:"
	"print '+timeout@button.push\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char BUTTON_HOME[] = {
	"start 'button.home\r\n';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"

	"req '2.m1.homing(64700)\r\n' 50;"
	"move r0 80;"
"loop1:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '2.m1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(0,1,1,0)\r\n' 50;"
	"move r0 80;"
"loop2:"
	"req '1.input.readpin(10,2)\r\n' 50;"
	"res.switch '(10,1,2,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop2;"
	"jmp $timeout;"
"$$:"

	"print '+ok@button.home\r\n';"
	"jmp $90;"
"$timeout:"
	"print '+timeout@button.home\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char SCREEN_TOUCH[] = {
	"start 'screen.touch %d\r\n' r7;"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"

	"req '2.m0.homing(64700)\r\n' 50;"
	"move r0 80;"
"loop1:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(2,0,3,1)\r\n' 50;"
	"move r0 80;"
"loop2:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,0,1,1)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop2;"
	"jmp $timeout;"
"$$:"

	"req '2.m0.moveto(38000,64700)\r\n' 50;"
	"move r0 80;"
"loop3:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(38000)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop3;"
	"jmp $timeout;"
"$$:"

	"req '2.m0.homing(64700)\r\n' 50;"
	"move r0 80;"
"loop4:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop4;"
	"jmp $timeout;"
"$$:"

	"print '+ok@screen.touch\r\n';"
	"jmp $90;"
"$timeout:"
	"print '+timeout@screen.touch\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char SCREEN_HOME[] = {
	"start 'screen.home\r\n';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	// cap pen carrier goes to standby position
	"req '2.m0.homing(64700)\r\n' 50;"
	"move r0 100;"
"loop1:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(2,1,3,0)\r\n' 50;"
	"move r0 80;"
"loop2:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop2;"
	"jmp $timeout;"
"$$:"

	"print '+ok@screen.home\r\n';"
	"jmp $90;"
"$timeout:"
	"print '+timeout@screen.home\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_2_0_3_1[] = {
	"start '1.output.writepin 2 0 3 1';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(2,0,3,1)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(2,0,3,1)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_2_1_3_0[] = {
	"start '1.output.writepin 2 1 3 0';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(2,1,3,0)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(2,1,3,0)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_6_1_7_0[] = {
	"start '1.output.writepin 6 1 7 0';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(6,1,7,0)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(6,1,7,0)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_6_0_7_1[] = {
	"start '1.output.writepin 6 0 7 1';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(6,0,7,1)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(6,0,7,1)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_0_1_1_0[] = {
	"start '1.output.writepin 0 1 1 0';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '+ok@2.m1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(0,1,1,0)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(0,1,1,0)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_0_0_1_1[] = {
	"start '1.output.writepin 0 0 1 1';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '+ok@2.m1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(0,0,1,1)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(0,0,1,1)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_4_1_5_0[] = {
	"start '1.output.writepin 4 1 5 0';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '+ok@2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(4,1,5,0)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(4,1,5,0)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char OUT_4_0_5_1[] = {
	"start '1.output.writepin 4 0 5 1';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '+ok@2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '1.output.writepin(4,0,5,1)\r\n' 50;"
	"res.switch '+ok@1.output.writepin' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@1.output.writepin(4,0,5,1)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char M1_MOVE[] = {
	"start '2.m1.moveto 26800 64500';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '1.input.readpin(10,2)\r\n' 50;"
	"res.switch '(10,0,2,1)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '2.m1.moveto(26800,64500)\r\n' 50;"
	"res.switch '+ok@' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@2.m1.moveto(26800,64500)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char M0_MOVE[] = {
	"start '2.m0.moveto 38000 64500';"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' $timeout;"
	"move r0 80;"
"loop:"
	"req '1.input.readpin(12,4)\r\n' 50;"
	"res.switch '(12,1,4,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop;"
	"jmp $timeout;"
"$$:"
	"req '2.m0.moveto(38000,64500)\r\n' 50;"
	"res.switch '+ok@' $$;"
	"jmp $timeout;"
"$$:"
	"print res;"
	"jmp $90;"
"$timeout:"
	"print '+timeout@2.m0.moveto(38000,64500)\r\n';"
"$90:"
	"ret;"

"isr_cmd:"
	"reti;"
};

const char SCRIPT_MAIN[] = {
	"start 'main\r\n';"
	"move r7 0;"
"loop:"
	"delay 50;"
	"r7.switch '[1,1]' loop;"
	"req '1.input.readpin(9)\r\n' 50;"	// make sure door is close
	"res.switch '(9,0)' loop;"

	"req '1.input.readpin(0)\r\n' 50;"
	"res.switch '(0,0)' loop;"

	// do reset job
	// m1 gohome
	"req '2.m1.homing(64700)\r\n' 50;"
	"move r0 100;"
"loop1:"
	"req '2.m1.pos()\r\n' 50;"
	"res.switch '2.m1.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop1;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(0,1,1,0)\r\n' 50;"
	"move r0 80;"
"loop2:"
	"req '1.input.readpin(10,2)\r\n' 50;"
	"res.switch '(10,1,2,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop2;"
	"jmp $timeout;"
"$$:"

	// cap pen carrier goes to standby position
	"req '2.m0.homing(64700)\r\n' 50;"
	"move r0 100;"
"loop3:"
	"req '2.m0.pos()\r\n' 50;"
	"res.switch '2.m0.pos(0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop3;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(2,1,3,0)\r\n' 50;"
	"move r0 80;"
"loop4:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,999]' loop4;"
	"jmp $timeout;"
"$$:"

	// POGO disconnect
	"req '1.output.writepin(4,1,5,0)\r\n' 50;"
	"move r0 80;"
"loop5:"
	"req '1.input.readpin(12,4)\r\n' 50;"
	"res.switch '(12,1,4,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop5;"
	"jmp $timeout;"
"$$:"

	// before press carrier goes up, 下压之前的干涉查询
	"move r0 80;"
"loop6:"
	"req '1.input.readpin(11,1)\r\n' 50;"
	"res.switch '(11,1,1,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop6;"
	"jmp $timeout;"
"$$:"

	// press carrier goes up
	"req '1.output.writepin(6,1,7,0)\r\n' 50;"
	"move r0 80;"
"loop7:"
	"req '1.input.readpin(13,5)\r\n' 50;"
	"res.switch '(13,1,5,0)' $$;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop7;"
	"jmp $timeout;"
"$$:"

	"req '1.output.writepin(0,1,1,0)\r\n' 50;"
	"move r0 80;"
"loop8:"
	"req '1.input.readpin(10,2)\r\n' 50;"
	"res.switch '(10,1,2,0)' $90;"
	"delay 100;"
	"sub r0 1;"
	"r0.switch '[0,99]' loop8;"
	"jmp $timeout;"
	"jmp $90;"

"$timeout:"
	"print '+timeout@reset_event\r\n';"

"$90:"
	"jmp loop;"
"ret;"

"isr_cmd:"
	//"print 'main.broadcast\r\n';"
	"cmd.switch 'unlock_reset' $1;"
	"cmd.switch 'lock_reset' $2;"
	"jmp $90;"
"$1:"
	"move r7 0;"
	"jmp $90;"
"$2:"
	"move r7 1;"
"$90:"
	"reti;"
};

SCRIPT_T STARTS[SCRIPT_COUNT] = {
	{SCRIPT_MAIN, NULL},
	{DISCONNECT, NULL},
	{CONNECT, NULL},
	{BUTTON_PUSH, NULL},
	{BUTTON_HOME, NULL},
	{SCREEN_TOUCH, NULL},
	{SCREEN_HOME, NULL},
	{OUT_2_0_3_1, NULL},
	{OUT_2_1_3_0, NULL},
	{OUT_6_1_7_0, NULL},
	{OUT_6_0_7_1, NULL},
	{OUT_0_1_1_0, NULL},
	{OUT_0_0_1_1, NULL},
	{OUT_4_1_5_0, NULL},
	{OUT_4_0_5_1, NULL},
	{M1_MOVE, NULL},
	{M0_MOVE, NULL},
//	{NULL, NULL},
};

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
