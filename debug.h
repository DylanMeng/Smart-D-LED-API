/***************************************************************
* FILE NAME: debug.h
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

#define DEBUG_EN // Comment this line to remove all serial print function

#ifdef DEBUG_EN
	#define DEBUG_SERIAL_INIT(x) Serial.begin(x); 
	#define DEBUG_PRINT(x)		 Serial.print(x)
	#define DEBUG_PRINT_LN(x)	 Serial.println(x)
	#define DEBUG_PRINT_HEX(x)	 Serial.print(x, HEX)
#else
	#define DEBUG_SERIAL_INIT(x) 
	#define DEBUG_PRINT(x)
	#define DEBUG_PRINT_LN(x)
	#define DEBUG_PRINT_HEX(x)
#endif

extern "C" char *sbrk(int i);
int freeRam() {
	char stack_dummy = 0;
	return &stack_dummy - sbrk(0);
}

class debugClass {


public:

};

debugClass debug;