#include <math.h>
#include <Servo.h>

#define SERVO_COUNT 3
#define STRING_LENGTH 128
#define TOKENS_COUNT 4
#define START_ANGLE 0
#define END_ANGLE 180

Servo servos[SERVO_COUNT];
const int pins[] = { 8, 9, 10 };
const int default_angles[] = { 120, 120, 120 };

void setup() {
    Serial.begin(9600);

    for (size_t i = 0; i < SERVO_COUNT; ++i) {
        servos[i].attach(pins[i]);
        delay(500);
        servos[i].write(default_angles[i]);
        delay(500); 
    }
}

void loop() {
    while(Serial.available() == 0);
    String request = Serial.readString(); 
    if (request.startsWith("move")) {
        delay(500);
        Serial.println(request);
        delay(500);
        char delimiter[] = " ";
        char string[STRING_LENGTH];
        String tokens[TOKENS_COUNT];
      
        request.toCharArray(string, sizeof(string));
        int i = 0;
        char* current_token = strtok(string, delimiter);
        while(current_token && i < TOKENS_COUNT) {
            tokens[i] = current_token;
            current_token = strtok(NULL, delimiter);
            ++i;  
        }
        int angle;
        for (size_t i = 0; i < SERVO_COUNT; ++i) {
            angle = round(tokens[i + 1].toDouble());
            servos[i].write(angle);
            delay(500);
            Serial.println(angle);
        }
    }
}
