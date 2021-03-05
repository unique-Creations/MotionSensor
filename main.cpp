#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define trigPin 13
#define echoPin 12
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    
     display.clearDisplay();
     display.setTextSize(1);             // Normal 1:1 pixel scale
     display.setTextColor(SSD1306_WHITE);        // Draw white text
     display.setCursor(30,20);             // Start at top-left corner
     display.println("Out of range");
     display.display();
     delay(10);
  }
  else {
    
    
    display.clearDisplay();

     display.setTextSize(2);             // Normal 1:1 pixel scale
     display.setTextColor(SSD1306_WHITE);        // Draw white text
     display.setCursor(40,20);             // Start at top-left corner
     display.print(distance);
     display.println(" cm");
     display.display();
     delay(10);
  }
  delay(500);
}
