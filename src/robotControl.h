
/*
 * robotControl.h
 *
 * Created: 15.06.2023
 * Author : Marius
 */ 

#ifndef ROBOTCONTROL_H_
#define ROBOTCONTROL_H_

#include <stdint.h>
#include <tools/timeTask/timeTask.h>


typedef enum state {
	CHECK_DIRECTIONS,
	CHOOSE_DIRECTION,
	
	TURN_LEFT,
	TURN_RIGHT,
	TURN_AROUND,
	TURN_ADJUST,
	
	IDLE,
	DRIVE_FORWARD,
	DRIVE_ADJUST,
	WAIT_90,

	STOP,
	FINISH
} state_t;

void stateMachine();

void setState(const state_t newState);
	
state_t getState();

timeTask_time_t getStartTime();

#endif /* ROBOTCONTROL_H_ */