/* PLEYADES IT
Brightness of a small 12V incandescent light bulb controlled with an Arduino Nano clone and a 2N2222 NPN BJT transistor.
The brightness increases or decreases (+/- 25%) by pressing the buttons and its status is displayed on a 128x64 OLED screen.
The buttons connect the digital pins of the microcontroller to GND when they are pressed (I have activated by code the internal pull-up resistors of the two digital pins).
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int LEDpin = 9;
const int Button1 = 3;
const int Button2 = 4;
int Button1Pressed;
int Button2Pressed;
int PWMValue = 0;
int Percentage = 0;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  digitalWrite(LEDpin, LOW);
  
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.print("2N2222");
  display.setCursor(5,25);
  display.print("CONTROLLED");
  display.setCursor(40,48);
  display.print("BULB");
  display.display();
  delay(5000);
  display.clearDisplay();
  display.setCursor(15,15);
  display.print("Pleyades");
  display.setCursor(55,40);
  display.print("IT");
  display.display();
  delay(5000);
  display.clearDisplay();
}

void loop()
{
  Button1Pressed = digitalRead(Button1);
  if (Button1Pressed == LOW && Percentage > 0)
  {
    Percentage = Percentage - 25;
    delay(100);
  }
  Button2Pressed = digitalRead(Button2);
  if (Button2Pressed == LOW && Percentage < 100)
  {
    Percentage = Percentage + 25;
    delay(100);
  }

  PWMValue = map(Percentage, 0, 100, 0, 255);
  analogWrite(LEDpin, PWMValue);

  display.setTextSize(2);
  display.setCursor(5,5);
  display.print("Brightness");
  display.setTextSize(3);
  display.setCursor(25,40);
  display.print(String(Percentage) + " %");
  display.display();
  display.clearDisplay();
}
