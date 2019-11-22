#define step_2_tp 127
#define step_2_1_lp 70
#define step_2_1_rp 70
#define step_2_2_lp 0
#define step_2_2_rp 0
#define step_2_3_lp 50
#define step_2_3_rp 50
#define step_2_5_lp -90
#define step_2_5_rp -90
#define step_2_5_tp 100
#define step_3_1_tp 50
#define step_3_1_lp -70
#define step_3_1_rp 70
#define step_3_2_lp 80
#define step_3_2_rp 80
#define step_3_3_lp 30
#define step_3_3_rp 100
#define step_4_1_lp -40
#define step_4_1_rp -40

int i;
int auto_1;
int remove_1;
float left_power;
float right_power;
float take_power;
float sl;
float sr;
float time[2] = {
	690,500,
};
float encoder[5] = {
	830,940,1350,750,400,
};
void choose(){
	i++;
	if(vexRT[Btn8D] == 1){
		auto_1= 1;
	}
	else{
		auto_1 = 0;
	}
	if(vexRT[Btn8U] == 1){
		remove_1 = 1;
	}
	else{
		remove_1 = 0;
	}
}
void pause(){
	motor[LeftRun_1]	=	0;
	motor[LeftRun_2]	=	0;
	motor[RightRun_1]	=	0;
	motor[RightRun_2]	=	0;
}
void move(){
	motor[LeftRun_1]	=	left_power;
	motor[LeftRun_2]	=	left_power;
	motor[RightRun_1]	=	right_power;
	motor[RightRun_2]	=	right_power;
}
void stop_n(){
	left_power = -15;
	right_power = -15;
	move();
	delay(5);
}
void check()
{
	pause();
	delay(50);
}
void SensorValue_named(){
	sl = SensorValue[dgtl2];
	sr = -SensorValue[dgtl5];
}
void SensorValue_start(){
	SensorValue[dgtl2] = 0;
	sl = 0;
	sr = 0;
	SensorValue[dgtl5] = 0;
}
void take(){
	motor[Intake_1] = take_power;
}
void shoot(){
	motor[Shoot_1] = 100;
}
void stop_shoot(){
	motor[Shoot_1] = 0;
	SensorValue_start();
}
void shoot_wait(){
	motor[Shoot_1] = 27;
}
void clt_1(){
	clearTimer(T1);
}
void clt_2(){
	clearTimer(T2);
}
/*
	step_1 used
	1.put down the shoot
	2.keep the shoot down
*/
void step_1(){
	clt_2();
	while(time1[T2] <= time[0]){                                     //1.put down the shoot
		shoot();
	}
	shoot_wait();                                                    //2.keep the shoot down
}
/*
	step_2 used
	1.go with high speed
	2.pause and reveser
	3.take ball with low speed
	4.stop and take ball for
	5.go back to cheak
*/
void step_2(){
	SensorValue_start();
	take_power = step_2_tp;                                          //take the ball
	while(sl <= encoder[0]){                                         //1.go with high speed
		left_power = step_2_1_lp;                                      //step_2_1
		right_power = step_2_1_rp;
		move();
		SensorValue_named();
	}
	clt_1();
	while(time1[T1] <= time[1]){                                     //2.pause and reverse
		left_power = step_2_2_lp;                                      //step_2_2
		right_power = step_2_2_rp;
		move();
		SensorValue_named();
		take();
	}
	while(sl <= encoder[3]){                                         //3.take ball with low speed
		left_power = step_2_3_lp;
		right_power = step_2_3_rp;
		move();
		take();
		SensorValue_named();
	}
	clt_1();
	pause();                                                         //4.stop and take ball for 0.5s
	while(time1[T1] <= time[1]){
		take();
	}
	clt_1();
	while(sr >= encoder[4]&&time1[T1] <= 4000){                      //5.go back to chack
		take_power = step_2_5_tp;                                      //step_2_5
		left_power = step_2_5_lp;
		right_power = step_2_5_rp;
		take();
		move();
		SensorValue_named();
	}
	pause();
	delay(2000);
	check();
}
/*
step_3 used
1.turn right
2.go straight
3.check
*/
void step_3(){
	SensorValue_start();
	check();
	clearTimer(T1);
	while(sl >= -200&&time1[T1] <= 1800){                             //2.turn right
	  left_power = step_3_1_lp;                                       //step_3_1
		right_power = step_3_1_rp;
		take_power = step_3_1_tp;
		move();
		SensorValue_named();
	}
	stop_n();
	SensorValue_start();
	clt_1();
	while(sl <= 1350&&time1[T1] <= 2000){                             //2.go straight
		SensorValue_named();                                            //step_3_2
		left_power = step_3_2_lp;
		right_power = step_3_2_rp;
		move();
	}
	check();
	SensorValue_start();
	clearTimer(T1);
	while(sl<=400&&time1[T1] <= 1000){                                //3.check
		SensorValue_named();                                            //step_3_3
		left_power = step_3_3_lp;
		right_power = step_3_3_rp;
		move();
	}
	check();
	pause();
}
/*step_4 used
1.go back
2.shoot the ball
*/
void step_4(){
	SensorValue_start();
	clearTimer(T1);
	while(sl >= -880&&time1[T1] <= 5000){                                    //1.go back
		left_power = step_4_1_lp ;
		right_power = step_4_1_rp ;
		move();
		SensorValue_named();
	}
	SensorValue_start();
	clt_1();
	while(sl <= 50&&time1[T1] <= 500){
		left_power = 10;
		right_power = -10;
		move();
		SensorValue_named();
	}
	pause();
	clearTimer(T1);
	while(time1[T1] <= 3000){                                            //2.shoot the ball
		if(time1[T1] <= 900){
			take_power = step_2_tp;
			pause();
			take();
		}
		else if(time1[T1] >= 1200){
			shoot();
		}
	}
	stop_shoot();
}


void auto()
{
	while(SensorValue[dgtl4] != 1){
		}
	step_1();
	step_2();
	step_3();
	step_4();
}
