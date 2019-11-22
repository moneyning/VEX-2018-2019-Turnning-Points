void Shoot_Auto();
void tall(){
	if(vexRT[Ch2] <= -20||vexRT[Ch2] >= 20){
		motor[port5] = -vexRT[Ch2];
	}
	else{
		motor[port5] = 0;
	}
}
const unsigned int PutSpeed[128] =	//speed table  Nonlinear correspondence to Improving Operational Sense
{
	0,  1,  2,  3,  4,  5,  6,  7,  8, 9,
	10, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	19,20, 21, 22, 23, 24, 25, 26, 27, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 95, 100, 105, 110,120,127,127
};
/******************************************************************/
void setMotorPwm(char port ,int Value)
{
	if(Value<=0)
	{
		motor[port]= -PutSpeed[-Value];
	}
	else
	{
		motor[port]=  PutSpeed[Value];
	}
}
/******************************************************************/
void Run(int spd)
{
	setMotorPwm(LeftRun_1,spd);
	setMotorPwm(LeftRun_2,spd);
	setMotorPwm(RightRun_1,-spd);
	setMotorPwm(RightRun_2,-spd);
}
/*****************************************************************/
void Run2(int left,int right)
{
	motor[LeftRun_1]=right;
	motor[LeftRun_2]=right;
	motor[RightRun_1]=left;
	motor[RightRun_2]=left;
	//setMotorPwm(LeftRun_1,left);
	//setMotorPwm(LeftRun_2,left);
	//setMotorPwm(RightRun_1,right);
	//setMotorPwm(RightRun_2,right);
}
/******************************************************************/
void Shoot(int shootspd)
{
	motor(Shoot_1)=(shootspd);
	//setMotorPwm(UpDown_2,upspd);
	//setMotorPwm(UpDown_3,-upspd);
	//setMotorPwm(UpDown_4,-upspd);
}
/******************************************************************/
void Intake(int getspd)
{
	motor(Intake_1)=(getspd);
	//setMotorPwm(intake_2,-getspd);
}
/******************************************************************/
void Turn(int turnspd)
{
	Run2((side*turnspd),(side*turnspd));
}
/******************************************************************/

/******************************************************************/

/******************************************************************/

/******************************************************************/

/******************************************************************/

/******************************************************************/
/*void TurnDegree(int degrees)
{
int TurnSide;
int TimeOut=20*abs(degrees)+500;
SensorValue[Gyro] = 0;
if (degrees < 0)
{TurnSide=-1;}
else if (degrees > 0)
{TurnSide=1; }
float ticks = abs(degrees*gro)/10;
clearTimer(T4);

while(abs(SensorValue[Gyro]) < ticks)
{
////////////////////////////////////FAILASFE TIMEOUT
if(time1[T4] > TimeOut && TimeOut > 0)
{
//FailSafeEngaged = 1;
break;
}
////////////////////////////////////////////////////
Turn(TurnSide*60);
}
Turn(-15*TurnSide);
wait1Msec(100);
Run(0);
}*/
/******************************************************************/

void Go_Run_Single_1()
{
	int left_pwm=0;
	int right_pwm=0;
	int pwm;
	pwm=abs(vexRT[Ch1])+abs(vexRT[Ch3])+1;
	left_pwm  = (  vexRT[Ch3]*abs(vexRT[Ch3])/pwm) + (vexRT[Ch1]*abs(vexRT[Ch1])/pwm);
	right_pwm = ( -vexRT[Ch3]*abs(vexRT[Ch3])/pwm) + (vexRT[Ch1]*abs(vexRT[Ch1])/pwm);


	if(left_pwm>=127)  left_pwm=127;
	if(left_pwm<=-127) left_pwm=-127;

	if(right_pwm>=127)  right_pwm=127;
	if(right_pwm<=-127) right_pwm=-127;

	if((abs(vexRT[Ch3])>20)||(abs(vexRT[Ch1])>20))
	{
		Run2(left_pwm,right_pwm);
	}
	else
	{
		Run(0);
	}

}
void Go_Run_Single_2()
{
	int left_pwm=0;
	int right_pwm=0;

	left_pwm  = (-vexRT[Ch4] + (vexRT[Ch3])*0.7);  // (y - x)/2
	right_pwm = (vexRT[Ch4] + (vexRT[Ch3]*0.7)); // (y + x)/2

	if(left_pwm>=127)
		left_pwm=127;

	if(left_pwm<=-127)
		left_pwm=-127;

	if(right_pwm>=127)
		right_pwm=127;

	if(right_pwm<=-127)
		right_pwm=-127;

	if((abs(vexRT[Ch3])>20)||(abs(vexRT[Ch4])> 20))
	{

		Run2(left_pwm,right_pwm);
		if (left_pwm>0)
		{brake_left=-1;}
		else if (left_pwm<0)
		{brake_left=1;}
		//else
		//{brake_left=0;}

		if (right_pwm>0)
		{brake_right=-1;}
		else if (right_pwm<0)
		{brake_right=1;}
		//else
		//{brake_right=0;}

	}
	else
	{
		Run2(brake_left*brake_pwm,brake_right*brake_pwm);
	}

}

void Go_Run_Single_3()
{
	int left_pwm=0;
	int right_pwm=0;

	left_pwm  = -(-vexRT[Ch2] + (vexRT[Ch1]*0.7));  // (y - x)/2
	right_pwm = -(vexRT[Ch2] + (vexRT[Ch1]*0.7)); // (y + x)/2

	if(left_pwm>=127)
		left_pwm=127;

	if(left_pwm<=-127)
		left_pwm=-127;

	if(right_pwm>=127)
		right_pwm=127;

	if(right_pwm<=-127)
		right_pwm=-127;

	if((abs(vexRT[Ch2])>20)||(abs(vexRT[Ch1])> 20))
	{

		Run2(left_pwm*0.5,right_pwm*0.5);
		if (left_pwm>0)
		{brake_left=-1;}
		else if (left_pwm<0)
		{brake_left=1;}
		//else
		//{brake_left=0;}

		if (right_pwm>0)
		{brake_right=-1;}
		else if (right_pwm<0)
		{brake_right=1;}
		//else
		//{brake_right=0;}

	}
	else
	{
		Run2(brake_left*brake_pwm,brake_right*brake_pwm);
	}

}


void Bnt_Control_2()
{

	if	(SensorValue(TouchSensor_Updown) == 1)
	{
		//SensorValue[Encode_Updown]=0;
		Flager=2;
	}
	if(vexRT[Ch2]>=threshold)
	{

		Flager=1;
		Flager_Shoot=0;
	}
	else	if((vexRT[Ch2]<=-threshold)&&(SensorValue(TouchSensor_Updown) != 1))
	{

		Flager=0;
	}

	else if(Flager==0)
	{

	}
	else if(Flager==1)
	{
	}
	else if(Flager==2)
	{

	}
	/////////////////////////////////////////////////////////////////////////////////


	if(vexRT[Btn5U]==1)
	{

		Flager_Claw=1;
		Flager=0;
	}
	else	if(vexRT[Btn5D]==1)
	{

		Flager_Claw=0;
	}
	else if(Flager_Claw==0)
	{

	}
	else if(Flager_Claw==1)
	{

	}


	/////////////////////////////////////////////////////////////////////
	if(vexRT[Btn6U]==1)
	{
		Intake(127);
	}
	else if(vexRT[Btn6D]==1)
	{
		Intake(-127);
	}
	else
	{
		Intake(0);
	}
	if(vexRT[Btn8L]==1)
	{

	}

}

void Load_Control()
{
	int finish=1;
	clearTimer(T2);

	while(time1[T2]<=600)
	{

		if (finish==1)
		{
			if(SensorValue[dgtl2]<=n)
			{
				Shoot(127);
			}

			else
			{
				SensorValue[dgtl2]=0;
				Shoot(10);
				finish=0;
			}
		}
		else
		{

			break;
		}
	}



}

void Shoot_Auto()
{
	/////////////////////////////////////////////////////////////////////
	if(vexRT[Btn8U]==1)
	{
		Shoot(-60);
		Flager_Shoot=0;
		Flager_Claw=0;
	}
	else if(vexRT[Btn8D]==1)
	{
		Shoot(127);
		Flager_Shoot=1;
		Flager_Claw=1;
	}

	else if(vexRT[Btn8R]==1)
	{
		if (Flager_Shoot==0)
		{
			Flager_Claw=1;
			Load_Control();
			Flager_Shoot=1;
		}
		else	if (Flager_Shoot==1)
		{
			Flager_Shoot=0;
			Flager_Claw=0;
		}
	}
	else	if(Flager_Shoot==0)
	{
		Shoot(-10);
	}
	else if(Flager_Shoot==1)
	{
		Shoot(20);
	}
}

void testmotor(int motorport)
{
	motor[motorport]=80;
	wait1Msec(200);
	motor[motorport]=0;
	wait1Msec(200);
	motor[motorport]=-80;
	wait1Msec(200);
	motor[motorport]=0;
}
void dishes(){
	if(vexRT[Btn5U]==1){
		motor[port3]=100;
	}
	else if(vexRT[Btn5D]==1){
		motor[port3]=-100;
	}
	else{
		motor[port3]=0;
	}
}

/*void Bnt_Control()
{
if(vexRT[Btn7U]==1)
{
testmotor(LeftRun_1);
}
if(vexRT[Btn7L]==1)
{
testmotor(LeftRun_2);
}
if(vexRT[Btn7D]==1)
{
testmotor(RightRun_1);
}
if(vexRT[Btn7R]==1)
{
testmotor(RightRun_2);
}
if(vexRT[Btn8U]==1)
{
testmotor(UpDown_1);
}
if(vexRT[Btn8L]==1)
{
testmotor(Shoot_1);
}
if(vexRT[Btn8R]==1)
{
testmotor(Claw_1);
}
if(vexRT[Btn8D]==1)
{
testmotor(Intake_1);
}
}*/
