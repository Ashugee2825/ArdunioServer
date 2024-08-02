// Include necessary libraries
#include <Arduino.h>

const int led1 = D0; // GPIO5
const int led2 = D1; // GPIO4
const int led3 = D2; // GPIO0
// Function to generate a random float number between min and max
float getRandomFloat(float min, float max) {
  // Generate a random integer
  long randInt = random(0, 10000);
  
  // Convert the random integer to a float in the range [0, 1)
  float randFloat = randInt / 10000.0;
  
  // Scale and shift to the desired range
  return min + randFloat * (max - min);
}

void setup() {
  // Initialize serial communication for debugging
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(115200);
  

  // Initialize random seed
  randomSeed(analogRead(A0));

  // Generate and print random float numbers
  for (int i = 0; i < 10; i++) {
    float randNum = getRandomFloat(0.0, 100.0); // Generate random float between 0 and 100
    Serial.println(randNum);
    delay(5000); // Add a delay to make the output readable
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    if (randNum <= 35) {
      digitalWrite(led1, HIGH);
      Serial.println("LED 1 is ON");
      
          delay(1000);
          //digitalWrite(led1, LOW);
          //delay(500);
    } else if (randNum >=36 && randNum <= 50 ) {
      digitalWrite(led2, HIGH);
      Serial.println("LED 2 is ON");
      
          delay(1000);
          //digitalWrite(led2, LOW);
          //delay(500);
    } else {
      digitalWrite(led3, HIGH);
      Serial.println("LED 3 is ON");
          delay(1000);
          //digitalWrite(led3, LOW);
          //delay(500);  
        }
  }
}

void loop() {
  // Put your main code here, to run repeatedly:
    
}

