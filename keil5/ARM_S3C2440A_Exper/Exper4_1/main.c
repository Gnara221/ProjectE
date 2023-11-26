#include <S3C2440.H>

extern int CAL(int i1,int i2,int i3,int i4,int i5,int i6);

__asm int convertNum(int i)
{
	;1111000000000000
	mov r1, #61440
	;0000111100000000
	mov r2, #3840
	;0000000011110000
	mov r3, #240
	;0000000000001111
	mov r4, #15
	and r1, r1, r0
	and r2, r2, r0
	and r3, r3, r0
	and r4, r4, r0
	mov r0, #0
	mov r4, r4,lsl#12
	mov r3, r3,lsl#4
	mov r2, r2,lsr#4
	mov r1, r1,lsr#12
	orr r0, r1, r0
	orr r0, r2, r0
	orr r0, r3, r0
	orr r0, r4, r0
	bx lr
}
	
	
	
int main(void)
{
	int i1 = 1,i2 = 2,i3 = 3,i4 = 4,i5 = 5,i6 = 6;
	
	i1 = CAL(i1,i2,i3,i4,i5,i6);
	
	
	int a=1,b=2,tmp=0;
	__asm {
		
		ADD tmp,a,b
		MUL tmp,tmp,8
	}
	i1 = convertNum(44117);	//1010	1100	0101	0101
	
	

	return i1;
}
	
