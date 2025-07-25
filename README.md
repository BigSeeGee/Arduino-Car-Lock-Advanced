# Arduino Car Lock Advanced

## Objective

The Arduino Car Lock Advanced project was developed as part of my master’s thesis focused on the security of remote keyless entry (RKE) systems in modern vehicles. 
This prototype simulates a vehicle locking mechanism using Arduino boards and RF communication modules, enhanced with a counter-based mechanism to detect replay attacks - one of the most common threats against wireless car remotes.

The project builds on a basic transmitter/receiver design and adds state tracking, conditional logic, and visual feedback via an LCD display to simulate secure vehicle locking behavior and illustrate how lightweight embedded security features can improve real-world system resilience.

### Tools Used

- Arduino UNO (x2)
- RF 433 MHz Transmitter and Receiver modules
- LCD 16x2 with I2C interface
- Servo motor (SG90 or equivalent)
- Push buttons (LOCK, UNLOCK, TRUNK)
- Libraries: Servo.h, LiquidCrystal_I2C.h, RCSwitch.h

## Hardware Design

The Arduino Car Lock Advanced project is divided into two physically separate modules: a transmitter (remote control) and a receiver (vehicle lock simulator). Both use Arduino UNO boards and communicate wirelessly over 433 MHz RF modules.

**Transmitter Module**

The transmitter simulates a car remote with three buttons representing the Lock, Unlock, and Trunk functions. Each button press sends an encoded RF signal along with a monotonically increasing counter, which ensures that every transmission is unique.

- Microcontroller: Arduino UNO
- Wireless module: 433 MHz RF Transmitter
- Inputs:
  - Button 1 – Lock (Pin 3)
  - Button 2 – Unlock (Pin 4)
  - Button 3 – Trunk (Pin 2)
  - Power: 9V battery regulated through Arduino VIN
- Logic: Each button press sends a signal like UNLOCK|counter:42 via RF.

<img width="2266" height="1686" alt="Vysielac_Rolling_bb" src="https://github.com/user-attachments/assets/43435331-3c9d-424f-9d15-b998402bf8e6" />

<div>

**Receiver Module**

The receiver processes incoming RF signals, validates the counter value, and performs a specific action using a servo motor and a 16×2 LCD display for status feedback.

- Microcontroller: Arduino UNO
- Wireless module: 433 MHz RF Receiver
- Servo motor: Controls lock/unlock position (Pin 4)
- LCD Display: 16×2 with I2C interface (SDA: A4, SCL: A5)
- Logic:
  - If received counter is within valid range → perform action and update servo.
  - If counter gap > 3 → display "ATTACK DETECTED" on LCD and ignore the signal.
<img width="2404" height="2106" alt="Prijmac_Rolling_bb" src="https://github.com/user-attachments/assets/345b77fe-025a-4bdd-bc07-41e424cf98af" />

<div>
