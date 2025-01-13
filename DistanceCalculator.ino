/* DISTANCE CALCULATOR */

/* 
BY:
MANOJ R P - P06MC22S038001
*/

#include <SoftwareSerial.h>

// Pin Definitions
#define TRIG_PIN 13    // Trigger pin of the ultrasonic sensor
#define ECHO_PIN 12    // Echo pin of the ultrasonic sensor
#define LED_PIN 2      // LED pin
#define BUZZER_PIN 3   // Buzzer pin

// Constants
#define DISTANCE_THRESHOLD 20  // Distance threshold in cm
#define MAX_DISTANCE 200       // Maximum measurable distance in cm
#define SOUND_SPEED 29.1       // Speed of sound in cm/us

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Configure pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Ensure the trigger pin is LOW at start
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  // Variables for duration and distance
  long duration;
  float distance;

  // Send a 10-microsecond pulse to trigger pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance (in cm)
  distance = (duration / 2.0) / SOUND_SPEED;

  // Check if the distance is within range
  if (distance >= MAX_DISTANCE || distance <= 0) {
    Serial.println("NOT IN RANGE");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    // Display the distance on Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Activate LED and Buzzer if distance is below the threshold
    if (distance < DISTANCE_THRESHOLD) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  // Short delay before the next measurement
  delay(500);
}