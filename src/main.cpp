#include "Arduino.h" 

// Define the pins for the right encoder
const int PIN_encR_A = 35;
const int PIN_encR_B = 19;  // Not used in this code, can be used for rotation direction sensing

// Define the pins for the left encoder
const int PIN_encL_A = 39;
const int PIN_encL_B = 20;  // Not used in this code, can be used for rotation direction sensing

// Variables to store encoder ticks
volatile unsigned int encR_ticks = 0;
volatile unsigned int encL_ticks = 0;

// Function to increment right encoder tick count (Do not use directly)
void read_rightEncoder() { 
    encR_ticks++; 
}

// Function to increment left encoder tick count (Do not use directly)
void read_leftEncoder() { 
    encL_ticks++; 
}

// Function to reset right encoder tick count
void reset_encR() { 
    encR_ticks = 0; 
}

// Function to reset left encoder tick count
void reset_encL() { 
    encL_ticks = 0; 
}

// Function to get the current right encoder tick count (equivalent to millis())
unsigned int get_encR() { 
    return encR_ticks; 
}

// Function to get the current left encoder tick count (equivalent to millis())
unsigned int get_encL() { 
    return encL_ticks; 
}

// Setup function to configure pins and attach interrupts
void setupEncoders()
{
    // Configure right encoder pins
    pinMode(PIN_encR_A, INPUT_PULLUP);
    // pinMode(PIN_encR_B, INPUT_PULLUP);
    
    // Configure left encoder pins
    pinMode(PIN_encL_A, INPUT_PULLUP);
    // pinMode(PIN_encL_B, INPUT_PULLUP);
    
    // Attach interrupts for both encoders on rising edges
    attachInterrupt(digitalPinToInterrupt(PIN_encR_A), read_rightEncoder, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_encL_A), read_leftEncoder, RISING);
}

// Setup function to initialize encoders
void setup(){
    Serial.begin(115200);
    setupEncoders();
}

// Loop function 
unsigned int lastEncL = 0;
unsigned int lastEncR = 0;
void loop(){
    unsigned int currentEncL = get_encL();
    unsigned int currentEncR = get_encR();

    if (currentEncL>226){
        Serial.println("left wheel made 1 round");
        reset_encL();
    }
    if (currentEncR>226){
        Serial.println("right wheel made 1 round");
        reset_encR();
    }
    Serial.print("Left Encoder: "+String(currentEncL)+" Right Encoder: "+ String(currentEncR)+"\n");
    

}
