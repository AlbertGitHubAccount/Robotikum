/*
 * RobotControl.c
 *
 * Created: 10.06.2023 15:36:13
 * Author : daniel
 */ 

#include <stdio.h>
#include <io/uart/uart.h>
#include <communication/communication.h>
#include <tools/timeTask/timeTask.h>
#include <tools/powerSaver.h>
#include <io/led/led.h>
#include <motor/motor.h>
                 
#include "robotControl.h"
#include "IR.h"
#include "OwnLaby.h"
#include "Position.h"



static state_t state = IDLE;
static timeTask_time_t startTime;		//timeTask_getTimestamp();

void setState(const state_t newState) {
	state = newState;
}

state_t getState() {
	return state;
}

timeTask_time_t getStartTime(){
	return startTime;
}

void driveForward() {
	Motor_setPWM(3000, 3010);
	//timeTask_getTimestamp(&startTime);
	//setState(WAIT_90);
}

void driveBackward() {
	Motor_setPWM(-3000, -3010);
}

void driveAdjust() {
	if (ownLaby_getPose()->cardinalDirection == DIRECTION_NORTH)
		if (ownLaby_getRobotPose()->y < position_getCurrentPose()->y)
			driveForward();
		else
			driveBackward();
	
	if (ownLaby_getPose()->cardinalDirection == DIRECTION_EAST)
		if (ownLaby_getRobotPose()->x > position_getCurrentPose()->x)
			driveForward();
		else
			driveBackward();
	
	if (ownLaby_getPose()->cardinalDirection == DIRECTION_SOUTH)
		if (ownLaby_getRobotPose()->y > position_getCurrentPose()->y)
			driveForward();
		else
			driveBackward();
	
	if (ownLaby_getPose()->cardinalDirection == DIRECTION_WEST)
		if (ownLaby_getRobotPose()->x < position_getCurrentPose()->x)
			driveForward();
		else
			driveBackward();
}

/*
void driveForward_1() {
	Motor_setPWM(3000, 3000);
}
*/


void wait_90() {
	timeTask_time_t now;
	timeTask_getTimestamp(&now);
	if (timeTask_getDuration(&startTime, &now) > 1050000UL) 
		setState(STOP);
}

/*
void wait_180() {
	timeTask_time_t now;
	timeTask_getTimestamp(&now);
	if (timeTask_getDuration(&startTime, &now) > 2100000UL) {
		Motor_stopAll();
		setState(IDLE);
	}
}

void turn_180(){
	Motor_setPWM(-3000, 3000);
	timeTask_getTimestamp(&startTime);
	setState(WAIT_180);
}
*/

void turnLeft() {
	Motor_setPWM(-3000, 3000);
	//timeTask_getTimestamp(&startTime);
	//setState(WAIT_90);
}

void turnRight() {
	Motor_setPWM(3000, -3000);
	//timeTask_getTimestamp(&startTime);
	//setState(WAIT_90);
}






// Funktion zur Steuerung des Roboters
void stateMachine() {
	switch (state) {
		case: CHOOSE_DIRECTION:
		case IDLE:
			break;
		case DRIVE_FORWARD:
			driveForward();
			break;
		case DRIVE_ADJUST:
			driveAdjust();
			break;
		//case DRIVE_FORWARD_TILE:
		//	driveForward_1();
		//	break;
		case WAIT_90:
			wait_90();
			break;
		//case WAIT_180:
		//	wait_180();
		//	break;
		case TURN_LEFT:
			turnLeft();
			break;
		case TURN_RIGHT:
			turnRight();
			break;
		case TURN_AROUND:
			turnLeft();
			break;
		case TURN_AROUND:
			turnRight();
			break;
		case STOP:
			Motor_stopAll();
			setState(IDLE);
			break;
	}	
}






