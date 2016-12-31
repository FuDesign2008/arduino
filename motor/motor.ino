
#define SWITCH_PIN 2
#define MOTOR_PIN_1 3
#define MOTOR_PIN_2 4
#define SPEED_PIN 9
#define POT_PIN 0

int mSpeed = 0;

void setup()
{
    pinMode(SWITCH_PIN, INPUT);

    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(SPEED_PIN, OUTPUT);
}

void loop()
{
    mSpeed = analogRead(POT_PIN) / 4;
    analogWrite(SPEED_PIN, mSpeed);
    if (digitalRead(SWITCH_PIN)) {
        digitalWrite(MOTOR_PIN_1, LOW);
        digitalWrite(MOTOR_PIN_2, HIGH);
    } else {
        digitalWrite(MOTOR_PIN_1, HIGH);
        digitalWrite(MOTOR_PIN_2, LOW);
    }
}


