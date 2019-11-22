void remove(void){
	while(1){
		if(SensorValue[dgtl1]==1&&vexRT[Btn8D]==0){
			SensorValue[dgtl2]=0;
			Shoot(0);
		}
		if((vexRT[Ch4]>=20||vexRT[Ch4]<=-20)||(vexRT[Ch3]<=-20||vexRT[Ch3]>=20))
			Go_Run_Single_2();
		else{
			Run(0);
		}
		Bnt_Control_2();
		Shoot_Auto();
		dishes();
		tall();
	}
}
