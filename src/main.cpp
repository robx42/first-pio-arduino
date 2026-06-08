// First project with PlatformIO 
// This project demonstrates a hello-world type program with your Ardunio ATMEGA2650 
// We'll use it to:
// 1. Test a serial connection to your device
// 2. Practice using the debugger
// 3. Practice using the Logic Analyzer

#include <Arduino.h>   // If you are using Arduino IDE, this include is hidden beneath the hood.

//#define DEBUG   // Enables print to serial port for debug.  Can only use this or debugger, not both. 
#define USEDEBUGGER  // This define is for the avr debugger.  With our board, we can't use Serial port & DEBUGGER at the same time.

#ifdef USEDEBUGGER
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#endif

// Define some macros for GPIO pins we are planning to use
// What's a macro?  Read more here: https://www.geeksforgeeks.org/cpp/cpp-macros/ 
#define TIMER_GPIO_PIN 13
#define DELAY_GPIO_PIN 12

// put function declarations here. 
int myFunction(int, int);
void setupTimers();

// Global variable definitions
static int x = 0;   // global count variable for debugging demonstration
static bool out13state = 0;  // gpio state variable for timer-based output toggle

void setup() {
  // put your setup code here, to run once:

  // Sets up the avr debugger, if you have selected to use it
  #ifdef USEDEBUGGER
  debug_init();
  #endif
  
  // Sets up print-to-serial for debugging, if you have selected to use it
  #ifdef DEBUG
  // Set up serial connection
  Serial.begin(9600);  // 9600 baud rate

  // Clear terminal and set to home - note that the Arduino IDE serial monitor does not handle these correctly
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command

  // Print some startup info to screen
  Serial.print("Hello World!\n");
  Serial.print("Debug statements are a great way to troubleshoot your code.\n");
  Serial.print("It's typically good to keep them contained within '#ifdef DEBUG #endif' statements so that you can turn them off once you are done debugging!\n");
  #endif

  // Initialize GPIO - put this into a function
  pinMode(TIMER_GPIO_PIN,OUTPUT);
  pinMode(DELAY_GPIO_PIN,OUTPUT);

  // Set up timers
  setupTimers();

  // Add other initialization calls here.  It's usually best to write functions, similar to what is shown for the setupTimers() function
}

void loop() {
  // put your main code here, to run repeatedly:

 
  x = myFunction(x,1);  // We'll place a watch on x to observe it's value with the debugger

  // Below is one way to implement a timed IO signal.  This is not efficient, since we are spending processor time doing nothing
  digitalWrite(DELAY_GPIO_PIN,HIGH);
  delay(1000); // set to 100 to make equal to timer
  digitalWrite(DELAY_GPIO_PIN,LOW);
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

// Setup timers and interrupts
void setupTimers()
{
    cli();//stop interrupts
    //set timer4 interrupt at 1Hz
    TCCR4A = 0;// set entire TCCR1A register to 0
    TCCR4B = 0;// same for TCCR1B
    TCNT4  = 0;//initialize counter value to 0
    // set compare match register for 10hz increments
    OCR4A = 1563;// = (16*10^6) / (10*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR4B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR4B |= (1 << CS12) | (1 << CS10);  
    // enable timer compare interrupt
    TIMSK4 |= (1 << OCIE4A);

    sei();//allow interrupts
}

// Interrupt service routines.  These are handled differently depending on your platform.
// For the ATMEGA2650, we use the ISR mactro and pass to it an interrupt vector which specifies the interrupt we are handling
// ISR functions should be short.  If you need to trigger something large to occur, consider using a "flag" variable
// which can signal to your main loop that action should be taken.
ISR(TIMER4_COMPA_vect){//timer4 interrupt 10Hz toggles pin 13 
//generates pulse wave of frequency 10Hz/2 = 5Hz (takes two cycles for full wave- toggle high then toggle low)
//this interrupt is the Timer/Counter4 Compare/Match A  
// this is a better way to implement something you would like to do infrequently.  

 digitalWrite(TIMER_GPIO_PIN,out13state);
    out13state = !out13state;

}