#pragma config(Sensor, dgtl1,  cubeSolonoid,   sensorDigitalOut)
#pragma config(Motor,  port1,           rightShoulder, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightArm1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftArm2,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightArm2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftArm1,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftFront,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftShoulder,  tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//// PRE AUTON VARIABLES ////
bool MrunAutonomous = true;
string currentAutonomous = "none";

//// COMPETITION STUFF ////
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

// Manual Control Variables
//long elapsedTime = 0;
int armAngle = 0;
int armTarget = 0;
//int lArmAngle = 0;
//int rArmAngle = 0;
//int sixBarDifference = 0;
//bool skills = false;

//void resetSensors() {
//	SensorValue(lArmEncoder) = 0;
//	SensorValue(rArmEncoder) = 0;

//	SensorValue(lBaseEncoder) = 0;
//	SensorValue(rBaseEncoder) = 0;
//}

int baseCurve(int joy) {
	if (abs(joy) < 10) {
		return 0;
	}
	else {
		float curve = 1.04;
		float slope = 97.0/(pow(curve, 117) - 1);
		return (slope * (pow(curve, abs(joy)-10) - 1) + 30)* joy / abs(joy);
	}
}

int turnCurve(int joy) {
	if (abs(joy) < 50) {
		return 0;
	}
	else {
		float curve = 1.06;
		float slope = 117.0/(pow(curve, 77) - 1);
		return (slope * (pow(curve, abs(joy) - 50) - 1) + 10) * joy / abs(joy);
	}
}

//void setSensors() {
//	rArmAngle = SensorValue(rArmEncoder);
//	lArmAngle = SensorValue(lArmEncoder);
//	armAngle = (rArmAngle + lArmAngle)/2;
//}

//LCD STUFF
void waitForButtonRelease() {
	while (nLCDButtons != 0) {
		wait1Msec(10);
	}
}
//STILL LCD STUFF
void waitForButtonPress() {
	while (nLCDButtons == 0) {
		wait1Msec(10);
	}
}

void pre_auton() {
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;
	displayLCDPos(0,1);
	displayNextLCDString("Raven Robotics");
	displayLCDPos(1,6);
	displayNextLCDString("2560E");

	const short leftButton = 1;
	const short centerButton = 2;
	const short rightButton = 4;
	int autonNum = 0;
	string autonCodes[2] = {
		"redRight",
		"blueRight",
	};
	string autonNames[2] = {
		"Red Right Zone",
		"Blue Right Zone",
	};

	currentAutonomous = autonCodes[0];
	displayLCDCenteredString(0, autonNames[0]);
	displayLCDCenteredString(1, "<-  Enter  ->");

	wait1Msec(1500);

	while (true) { //loop
		waitForButtonPress();
		if (nLCDButtons == centerButton) {//right button
			break;
		}
		else if (nLCDButtons == rightButton) {//right button
			autonNum++;
			if (autonNum > 1) {
				autonNum = 0;
			}
		}
		else if (nLCDButtons == leftButton) {//left button
			autonNum--;
			if (autonNum < 1) {
				autonNum = 3;
			}
		}
		currentAutonomous = autonCodes[autonNum];
		displayLCDCenteredString(0, autonNames[autonNum]);
		waitForButtonRelease();
	}
	displayLCDCenteredString(1, "Selected");
	wait1Msec(1000);

	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, "Raven Robotics");
	displayLCDCenteredString(1, "2560E");
}

void moveForwardFor(int speed, float time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		motor[LeftBack] = speed;
		motor[LeftFront] = speed;
		motor[RightFront] = speed;
		motor[RightBack] = speed;
	}
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}

void raiseArmFor (int armPower, float time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		motor[rightArm1] = armPower;
		motor[rightArm2] = armPower;
		motor[rightShoulder] = armPower;

		motor[leftArm1] = armPower;
		motor[leftArm2] = armPower;
		motor[leftShoulder] = armPower;
	}
	motor[rightArm1] = 15;
	motor[rightArm2] = 15;
	motor[rightShoulder] = 15;

	motor[leftArm1] = 15;
	motor[leftArm2] = 15;
	motor[leftShoulder] = 15;

}

void turnLeftFor (int speed, float time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		motor[LeftBack] = -speed;
		motor[LeftFront] = -speed;
		motor[RightFront] = speed;
		motor[RightBack] = speed;
	}
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}

void turnRightFor (int speed, float time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		motor[LeftBack] = speed;
		motor[LeftFront] = speed;
		motor[RightFront] = -speed;
		motor[RightBack] = -speed;
	}
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}

void strafeLeftFor (int speed, float time) {
	while (time1[T1] < time * 1000) {
		motor[LeftBack] = -speed;
		motor[LeftFront] = speed;
		motor[RightFront] = speed;
		motor[RightBack] = -speed;
	}
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}

void strafeRightFor (int speed, float time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		motor[LeftBack] = speed;
		motor[LeftFront] = -speed;
		motor[RightFront] = -speed;
		motor[RightBack] = speed;
	}
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}

void pause(int time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		motor[LeftBack] = 0;
		motor[LeftFront] = 0;
		motor[RightFront] = 0;
		motor[RightBack] = 0;

		motor[rightArm1] = 15;
		motor[rightArm2] = 15;
		motor[rightShoulder] = 15;

		motor[leftArm1] = 15;
		motor[leftArm2] = 15;
		motor[leftShoulder] = 15;
	}
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;

	motor[rightArm1] = 15;
	motor[rightArm2] = 15;
	motor[rightShoulder] = 15;

	motor[leftArm1] = 15;
	motor[leftArm2] = 15;
	motor[leftShoulder] = 15;

}

void dropCubes(int time) {
	time1[T1] = 0;
	while (time1[T1] < time * 1000) {
		SensorValue(cubeSolonoid) = true;
	}
	SensorValue(cubeSolonoid) = false;
}


task autonomous() {
	int side;

	if (strcmp(currentAutonomous, "redRight") == 0) { //if it's the red side
		side = 1;
	}
	else {
		side = 2;
	}

	bool mRunAutonomous = true;
	if (mRunAutonomous == true) {
		wait1Msec(5);

		if (side == 2) { // BLUE

			raiseArmFor(127, 0.5);
			moveForwardFor(127, 0.5);
			pause(0.5);


			raiseArmFor(-127, 0.75);
			pause(0.5);
			raiseArmFor(127, 1.5);
			pause(0.5);
			moveForwardFor(-127, 0.5);
			pause(0.5);


			turnRightFor(80, 0.6);
			pause(0.5);
			dropCubes(1.5);
			pause(0.75);
			moveForwardFor(-127, 0.75);
			//turnLeftFor(80, 1);
			//pause(1);


			//moveForwardFor(127, 1);
			//pause(0.5);
			//raiseArmFor(-30, 1);
			//pause(2);
			//raiseArmFor(127, 1.5);
			//pause(0.5);


		}// end of side

		if (side == 1) { // RED

			raiseArmFor(127, 0.5);
			moveForwardFor(127, 0.5);
			pause(0.5);


			raiseArmFor(-127, 0.75);
			pause(0.5);
			raiseArmFor(127, 1.5);
			pause(0.5);
			moveForwardFor(-127, 0.5);
			pause(0.5);


			turnLeftFor(80, 0.6);
			pause(0.5);
			dropCubes(1.5);
			pause(0.75);
			moveForwardFor(-127, 0.75);


		}// end of side
	}// end of run auton
}
///////// why is the sky blue

task usercontrol() { // manual driver drive driving
	//setSensors();
	armTarget = 0;
	//	int oldArmAngle = armAngle;
	//	int armSpeed = 0;
	//	int armCounter = 0;
	while (true) {
		wait1Msec(10);

		// Sensor Setup ////////////////////
		//		setSensors();

		//armCounter++;
		//if (armCounter == 5) { // Once every 50ms
		//	armCounter = 0;
		//	armSpeed = armAngle - oldArmAngle; // Determine rate of change in arm height
		//	oldArmAngle = armAngle;
		//}

		// Base Control ////////////////////////////////////////
		// (commence math stuff)

		float angle = PI/2; //Default 90 degrees

		if (vexRT[Ch3] == 0) { // Prevent divide by 0 problem
			if (vexRT[Ch4] < 0) // If going left
				angle = -PI/2; //
		}
		else {
			angle = atan(vexRT[Ch4]/(float)vexRT[Ch3]); // Find desired angle for the robot to drive (
			if (vexRT[Ch3] < 0)
				angle += PI;
		}

		float throttle = 1.414*baseCurve(sqrt(pow(vexRT[Ch3], 2) + pow(vexRT[Ch4], 2)));

		int lf;
		int rf;
		int lb;
		int rb;

		lf = throttle*sin(angle+PI/4);
		rf = throttle*cos(angle+PI/4);
		lb = throttle*cos(angle+PI/4);
		rb = throttle*sin(angle+PI/4);

		if (abs(vexRT[Ch1]) > 50) { // Steering
			lf += turnCurve(vexRT[Ch1]);
			rf -= turnCurve(vexRT[Ch1]);
			lb += turnCurve(vexRT[Ch1]);
			rb -= turnCurve(vexRT[Ch1]);
		}

		motor[LeftFront]  = lf;
		motor[RightFront] = rf;
		motor[LeftBack]   = lb;
		motor[RightBack]  = rb;



		// new shoulder

		int armPower = 15;

		if (vexRT[Ch2] > 20) {
			armPower = (1.649*(vexRT[Ch2]-20));
		}

		if (vexRT[Ch2] < -20) {
			armPower = (1.649*(vexRT[Ch2]+20))/4;
		}

		motor[rightArm1] = armPower;
		motor[rightArm2] = armPower;
		motor[rightShoulder] = armPower;

		motor[leftArm1] = armPower;
		motor[leftArm2] = armPower;
		motor[leftShoulder] = armPower;

		SensorValue(cubeSolonoid) = vexRT[Btn6U];

	}
}
// this is the end of the code
