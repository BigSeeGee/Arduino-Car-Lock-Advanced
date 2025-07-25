// -------------------------------------------------
// Required library for RF communication
// -------------------------------------------------
#include <RCSwitch.h>

// -------------------------------------------------
// Create an instance of the RF transmitter object
// -------------------------------------------------
RCSwitch mySwitch = RCSwitch();

// -------------------------------------------------
// Define pins for buttons on the remote control
// -------------------------------------------------
const int trunkButtonPin = 2;   // Button pin for trunk release
const int lockButtonPin = 3;    // Button pin for locking the vehicle
const int unlockButtonPin = 4;  // Button pin for unlocking the vehicle

// -------------------------------------------------
// Initialize counters to simulate a rolling code
// -------------------------------------------------
unsigned long lockCounter = 0;    // Counter for the lock button
unsigned long unlockCounter = 0;  // Counter for the unlock button
unsigned long trunkCounter = 0;   // Counter for the trunk button

// -------------------------------------------------
// setup() function – system initialization
// -------------------------------------------------
void setup() {
    Serial.begin(9600);                  // Start serial communication for debugging (9600 baud)
    mySwitch.enableTransmit(10);         // Set pin 10 for RF signal transmission

    // Configure button pins as inputs with internal pull-up resistors
    pinMode(lockButtonPin, INPUT_PULLUP);    
    pinMode(unlockButtonPin, INPUT_PULLUP);  
    pinMode(trunkButtonPin, INPUT_PULLUP);   
}

// -------------------------------------------------
// loop() function – main program loop
// -------------------------------------------------
void loop() {
    // Check if the lock button is pressed
    if (digitalRead(lockButtonPin) == LOW) {
        lockCounter++;  // Increment lock counter
        char message[10];
        sprintf(message, "L%lu", lockCounter); // Create message in format "L<number>"
        mySwitch.send(message);               // Send message via RF transmitter
        Serial.print("Sending: ");
        Serial.println(message);              // Print sent message to serial monitor
        delay(500);                           // Short delay to prevent rapid repeats
    }

    // Check if the unlock button is pressed
    if (digitalRead(unlockButtonPin) == LOW) {
        unlockCounter++; // Increment unlock counter
        char message[10];
        sprintf(message, "U%lu", unlockCounter); // Create message in format "U<number>"
        mySwitch.send(message);                  // Send message via RF transmitter
        Serial.print("Sending: ");
        Serial.println(message);
        delay(500);
    }

    // Check if the trunk button is pressed
    if (digitalRead(trunkButtonPin) == LOW) {
        trunkCounter++; // Increment trunk counter
        char message[10];
        sprintf(message, "T%lu", trunkCounter); // Create message in format "T<number>"
        mySwitch.send(message);                 // Send message via RF transmitter
        Serial.print("Sending: ");
        Serial.println(message);
        delay(500);
    }
}