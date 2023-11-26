#include <S3C2440.H>  

#define ON 0
#define OFF 1


void delay()  
{  
    int i,j;  
    for(i=0;i<10000;i++)  
    {  
        for(j=0;j<50;j++);  
    }  
}  

void led(int GPBX, int State)
{
	if(State == 1){
		GPBDAT |= 0xFFFF;
	}
	else
		GPBDAT = ~(1 << GPBX);
	
}


int main()  
{  
	//RESET B1,B5~B8
	GPBCON &= 0XFFFC03F3;
	//GPB1->00
	GPBCON &= 0XFFFFFFF3;
	//GPB5~8->01
//	GPBCON |= ~(0xFFFEABFF);
	GPBCON |=  1 << 8 *2;
	GPBCON |=  1 << 7 *2;
	GPBCON |=  1 << 6 *2;
	GPBCON |=  1 << 5 *2;
	led(5,OFF);
	led(6,OFF);
	led(7,OFF);
	led(8,OFF);
	delay();
	while(1)
	{
		
		
		//GPB1为高电平
		if((GPBDAT & 0x00000002) == 1)
		{
			led(5,ON);
			delay();
			led(5,OFF);
			led(6,ON);
			delay();
			led(6,OFF);
			led(7,ON);
			delay();
			led(7,OFF);
			led(8,ON);
			delay();
			led(8,OFF);
			//拉低GPB1电平
			GPBDAT &= 0 << 1;
		}
		else
		{
			led(8,ON);
			delay();
			led(8,OFF);
			led(7,ON);
			delay();
			led(7,OFF);
			led(6,ON);
			delay();
			led(6,OFF);
			led(5,ON);
			delay();
			led(8,OFF);
			//拉高GPB1电平
//			GPBUP |= 1 << 1;
		}
		
	}
	
}
	
