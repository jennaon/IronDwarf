#include <p18f4520.h>
#include <delays.h>

void init( void );
void searchA( void );
void options( void );
void march( unsigned char time );
void reverse( unsigned char time );
void turnright( unsigned char time);
void turnleft ( unsigned char time);

unsigned char front;
unsigned char right;
unsigned char left;
unsigned char back;

unsigned char normal;
unsigned char turnleftfirst;
unsigned char turnrightfirst;
unsigned char backthefuckup;

unsigned char time;

void main( void ) {
  init();	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
  while( 1 ) { 
	march(1);
	searchA();
  }            
	
}

void init( void ){
	ADCON1 = 0x0F; //15
	
	PORTA = 0;
	PORTC = 0;
	PORTD = 0;

	TRISA = 0xFF; //255
	TRISC = 0;	
	TRISD = 0xFF; 
	
	options();
	march(5);
}

void searchA( void ){
	front = PORTAbits.RA1;
	if(front==1){ //front sensor
		reverse(3);
		turnleft(4);
	}
  
	left = PORTAbits.RA2;
	if(left==1){ //left sensor
		turnright(4);
	}

	right = PORTAbits.RA3;
	if(right==1){ //right sensor
		turnleft(4);
	}

	back = PORTAbits.RA0;
	if(back==1){ //back sensor
		turnright(2);
		turnleft(2);
		turnright(2);
		turnleft(2);
		march(4);
	}
}

void options( void ){
	normal = PORTDbits.RD4;
	if(normal==1){  //move forward without using sensors
		march(4);
	}

	turnleftfirst = PORTDbits.RD5;
	if(turnleftfirst==1){ //turn left to face center
		turnleft(3);
	}

	turnrightfirst = PORTDbits.RD6;
	if(turnrightfirst==1){ //turn right to face center
		turnright(3);
	}

	backthefuckup = PORTDbits.RD7;
	if(backthefuckup==1){ //backs the fuck up
		reverse(5); 
		turnright(10);
	}
}

void march (unsigned char time){
	int i;
	PORTC = 80;
	for(i=0;i<time;i++){
		Delay10KTCYx(1255); //delay "time" seconds
	}
}

void reverse (unsigned char time){
	int i;
	PORTC = 160;
	for(i=0;i<time;i++){
		Delay10KTCYx(1255); 
		Delay10KTCYx(1255);
		Delay10KTCYx(1255);
	}
}

void turnright (unsigned char time){
	int i;
	PORTC = 96;
	for(i=0;i<time;i++){
		Delay10KTCYx(1255); 
		Delay10KTCYx(1255);
		Delay10KTCYx(1255);		
	}
}

void turnleft (unsigned char time){
	int i;
	PORTC = 144;
	for(i=0;i<time;i++){
		Delay10KTCYx(1255); 
		Delay10KTCYx(1255);
		Delay10KTCYx(1255);		
	}
}
