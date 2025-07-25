#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <RCSwitch.h>

// -----------------------------------------------------
// Define pins for connected components
// -----------------------------------------------------
const int servoPin = 4;       // Pin for controlling the servo motor
const int receiverPin = 3;    // Pin for receiving RF signals (433 MHz)

// -----------------------------------------------------
// Initialize LCD display, servo, and RF receiver objects
// -----------------------------------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD display with I2C address 0x27
Servo servo;                         // Servo motor object
RCSwitch mySwitch = RCSwitch();     // RF receiver

// -----------------------------------------------------
// Expected counters for command validation
// -----------------------------------------------------
unsigned long expectedLockCounter = 0;
unsigned long expectedUnlockCounter = 0;
unsigned long expectedTrunkCounter = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Enable RF receiver on interrupt-capable pin
  mySwitch.enableReceive(digitalPinToInterrupt(receiverPin));

  // Attach servo to its designated pin
  servo.attach(servoPin);
  servo.write(90); // Default position (locked)

  // Initialize LCD display
  lcd.begin(16, 2);       // 16 columns and 2 rows
  lcd.backlight();        // Turn on backlight
  lcd.setCursor(0, 0);    
  lcd.print("Status: Locked"); // Initial display state
}

void loop() {
  // Check if a signal has been received
  if (mySwitch.available()) {
    unsigned long receivedCode = mySwitch.getReceivedValue(); // Read received signal

    Serial.print("Received code: ");
    Serial.println(receivedCode);

    // Split the message into command identifier and counter
    unsigned long counter = receivedCode % 1000;   // Last 3 digits = counter
    unsigned long command = receivedCode / 1000;   // First digit(s) = command ID (1, 2, 3)

    // Process command based on type
    if (command == 1) {  // Lock command
      if (counter > expectedLockCounter && (counter - expectedLockCounter) <= 3) {
        expectedLockCounter = counter;      // Update expected counter
        servo.write(180);                   // Move servo to locked position
        lcd.setCursor(0, 0);
        lcd.print("Status: Locked  ");
      } else {
        Serial.println("Attack detected on lock button.");
        lcd.setCursor(0, 0);
        lcd.print("Attack detected! ");
      }

    } else if (command == 2) { // Unlock command
      if (counter > expectedUnlockCounter && (counter - expectedUnlockCounter) <= 3) {
        expectedUnlockCounter = counter;
        servo.write(0);                    // Move servo to unlocked position
        lcd.setCursor(0, 0);
        lcd.print("Status: Unlocked ");
      } else {
        Serial.println("Attack detected on unlock button.");
        lcd.setCursor(0, 0);
        lcd.print("Attack detected! ");
      }

    } else if (command == 3) { // Trunk command
      if (counter > expectedTrunkCounter && (counter - expectedTrunkCounter) <= 3) {
        expectedTrunkCounter = counter;
        lcd.setCursor(0, 0);
        lcd.print("Trunk Opened      ");

        // Simulate double trunk action with servo movement
        for (int i = 0; i < 2; i++) {
          servo.write(0);
          delay(500);
          servo.write(180);
          delay(500);
        }
      } else {
        Serial.println("Attack detected on trunk button.");
        lcd.setCursor(0, 0);
        lcd.print("Attack detected! ");
      }
    }

    // Clear the received signal flag
    mySwitch.resetAvailable();
  }
}