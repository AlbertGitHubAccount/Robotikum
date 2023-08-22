/*
 * path.c
 *
 * Created: 12.07.2023 15:10:24
 *  Author: Daniel
 */ 

#include "path.h"
#include "robotControl.h"
#include "Position.h"
#include <motor/motor.h>
#include <math.h>
#include <communication/packetTypes.h>


float calcDifAngle(const Pose_t* pose, const FPoint_t* lookahead);
//static float thetaRobot = pose.theta;

void calculateDriveCommand(const Pose_t* pose, const FPoint_t* lookahead){
	float dif;
	dif = calcDifAngle(pose, lookahead);
	
	
	if(dif < -0.05f){
		Motor_setPWM(6000,1000);
	}
	else if(dif > 0.05f)
		{Motor_setPWM(1000,6000);
	}
	
	
	else{
		Motor_setPWM(3000,3000);
	}
	
	
}

float calcDifAngle(const Pose_t* pose, const FPoint_t* lookahead){
	float pLx = lookahead->x;
	float pLy = lookahead->y;
	float pRx = pose->x;
	float pRy = pose->y;
	float a = pLy - pRy;
	float b = pLx - pRx;
	float gamma = atan2(a, b);
	float dif = gamma - pose->theta;
	if(dif < -M_PI){
		dif += 2*M_PI;
		}else if(dif > M_PI){

		dif -= 2*M_PI;
	}
	return dif;
}