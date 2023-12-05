# ESP32 PS4 Controller Control System

This code implements a control system using an ESP32 microcontroller to interact with a PS4 controller, manage a servo motor, ultrasonic sensor, and a DC motor.

## Components

1. **Servo Motor**
   - Controls a servo motor's position based on the PS4 controller's right stick movement.
   - Pin: 25

2. **Ultrasonic Sensor**
   - Measures distance using an ultrasonic sensor.
   - Trigger Pin: 4
   - Echo Pin: 5

3. **DC Motor**
   - Drives a DC motor based on the PS4 controller's left stick movement.
   - PWM Pin: 12
   - Direction Control Pins: 32, 33

4. **Buzzer**
   - Indicates conditions based on ultrasonic sensor readings.
   - Pin: 13

## Functionality

- `notify()`: Monitors PS4 controller input for the 'Cross' button press.
- `motorDc()`: Controls the DC motor direction and speed based on the PS4 controller's input.
- `servoM()`: Adjusts the position of the servo motor according to the PS4 controller's right stick movement.
- `setup()`: Initializes pin modes, serial communication, PS4 controller connection, servo motor, and DC motor settings.
- `loop()`: Executes the main control loop, managing servo and DC motor movements, measuring distance using the ultrasonic sensor, and controlling a buzzer based on predefined conditions.

## Usage

1. Connect the PS4 controller via Bluetooth or USB to the ESP32.
2. Connect the servo motor, ultrasonic sensor, DC motor, and buzzer to their respective GPIO pins as specified in the code.
3. Upload the code to the ESP32 board using the Arduino IDE or a compatible platform.
4. Monitor the serial output for status updates and interaction information.

## Notes

- Ensure proper wiring and connection of components to avoid malfunctions.
- Adjust pin configurations if necessary, depending on the actual hardware setup.
