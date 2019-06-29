// Tutorial 5a. LED luminaire w. joystick colour temperature control

// Main parts: Adafruit Metro Mini, analog 2-axis joystick w. select button,
// CC-PSUs w. PWM dimming input, high-power LEDs (one 2700K, one 4000K)

// Variables that remain constant
const byte pinJoyX = A0; // Analog input pin from joystick x-axis
const byte pinJoyY = A1; // Analog input pin from joystick y-axis
const byte pinJoySwitch = 3; // Digital input pin from joystick select button
const byte pinCC_PSUleft = 5; // Digital output pin to CC-PSU (LED left)
const byte pinCC_PSUright = 6; // Digital output pin to CC-PSU (LED right)
const int dzJoyLow = 256; // Joystick dead zone low end
const int dzJoyHigh = 768; // Joystick dead zone high end
const int stepTime = 100; // Adjust for faster or slower PWM change
const byte changePWM = 8; // PWM change per step (2, 4, 8 or 16)
const byte minPWM = 8; // PWM minimum (2, 4, 8 or 16; must match changePWM)

// Variables that can change
int joyX; // Joystick potentiometer's x-axis tilt value
int joyY; // Joystick potentiometer's y-axis tilt value
byte lastSwitchState = HIGH; // Store joystick's switch state
bool lightOn = true; // Light is turned on at start
byte maxPWM = 0; // PWM maximum (will be calculated from changePWM)
int leftPWM = 128; // Default brightness
int rightPWM = 128; // Default brightness

void setup()
{
  // Initialise the joystick's switch pin with an internal pull-up resistor
  // so that the momentary switch is read as open (= HIGH) at start
  pinMode(pinJoySwitch, INPUT_PULLUP);
  
  // Calculate maximum possible PWM value from selected PWM change per step,
  // possible PWM values (8 bit) range from 0 - 255
  maxPWM = 256 - changePWM;
}

void loop()
{
  // The momentary switch is hardware debounced with a 1uF capacitor; no
  // debouncing code is necessary. See http://www.gammon.com.au/switches
  // Read the voltage from the momentary switch pin to see if something
  // has changed (was the button pressed or released?)
  byte switchState = digitalRead (pinJoySwitch);

  // Has the momentary switch state changed since the last time it was
  // checked (once every loop() iteration)?
  if (switchState != lastSwitchState)
  {
    // First, store the current switch state for the next time around
    lastSwitchState = switchState;

    // Next, test if the switch was closed (button pressed)
    if (switchState == LOW)

    { // If so, toggle the light from off to on
      lightOn = !lightOn;

      // Always turn back on at default brightness
      leftPWM = 128;
      rightPWM = 128;
    }
    // One could also add an else statement here, if one would want to
    // trigger something when the button was released (switch = HIGH)
  }

  // A call to this function continuously sets both LED's brightness
  // independently (once every loop() iteration) depending on the
  // joystick's tilt
  changeBrightness();

  // Slow PWM value updates a bit to allow for easier adjustment
  delay(stepTime);
}

void changeBrightness()
{
  // If the light is on
  if (lightOn)
  {
    // Read the joystick's tilt
    readJoystick();

    // If the joystick is tilted left
    if (joyX < dzJoyLow)
    {

      // And is somewhere in the PWM value matrix' quadrant 1 or 4
      if ((leftPWM < maxPWM) && (rightPWM > minPWM))
      {

        // Then change both PWM values accordingly
        leftPWM += changePWM;
        rightPWM -= changePWM;

        // And write them to both CC-PSUs
        setPWM(leftPWM, rightPWM);
      }
    }

    // If joystick is tilted right...
    if (joyX > dzJoyHigh)
    {
      if ((leftPWM > minPWM) && (rightPWM < maxPWM))
      {
        leftPWM -= changePWM;
        rightPWM += changePWM;
        setPWM(leftPWM, rightPWM);
      }
    }

    // If joystick is tilted up...
    if (joyY > dzJoyHigh)
    {
      if ((leftPWM < maxPWM) && (rightPWM < maxPWM))
      {
        leftPWM += changePWM;
        rightPWM += changePWM;
        setPWM(leftPWM, rightPWM);
      }
    }

    // If joystick is tilted down...
    if (joyY < dzJoyLow)
    {
      if ((leftPWM > minPWM) && (rightPWM > minPWM))
      {
        leftPWM -= changePWM;
        rightPWM -= changePWM;
        setPWM(leftPWM, rightPWM);
      }
    }
  }

  // If the switch was pressed while the light was on, turn the light off
  else
  {
    setPWM(0, 0);
  }
}

void readJoystick()
{
  // Read the joystick's x and y axes potentiometer values. In this case,
  // when the joystick is centered, x reads 497 and y reads 509; these
  // values differ for each joystick (never exactly 512)
  joyX = analogRead(pinJoyX);
  joyY = analogRead(pinJoyY);
}

void setPWM(int leftPWM, int rightPWM)
{
  // Update both CC-PSU PWM values (= change both LED's brightness)
  analogWrite(pinCC_PSUleft, leftPWM);
  analogWrite(pinCC_PSUright, rightPWM);
}
