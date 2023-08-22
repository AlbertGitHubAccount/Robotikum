/*
 * OwnLaby.h
 *
 * Created: 02.08.2023 14:41:42
 *  Author: Marius
 */ 


#ifndef OWNLABY_H_
#define OWNLABY_H_

#include <stdint.h>
#include <communication/packetTypes.h>

typedef enum {
	LEFT		= 0,
	FORWARD		= 1,
	RIGHT		= 2,
	BACKWARD	= 3,
} RobotDirection_t;


typedef struct __attribute__((__packed__)) {
	uint8_t row;
	uint8_t column;
	Direction_t cardinalDirection;
	///<   - cardinalDirection = 0 => (north)
	///<   - cardinalDirection = 1 => (east)
}LPose_t;

LPose_t labyPose;
const LPose_t* ownLaby_getPose();
void ownLaby_setPose(const Pose_t* expextedPose);

Pose_t labyRobotPose;
const Pose_t* ownLaby_getRobotPose();
void ownLaby_setRobotPose(const LPose_t* labyPose);

bool robot_canContinue();
bool robot_isWall(RobotDirection_t localDirection);
bool robot_canMove(RobotDirection_t localDirection);

void robot_rotate(RobotDirection_t exitDir);
bool robot_move(RobotDirection_t moveState);

int8_t robot_getExitDirection();
void robot_setExitDirection();





#endif /* OWNLABY_H_ */