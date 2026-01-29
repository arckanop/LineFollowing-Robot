#define PWMA 8
#define AIN2 7
#define AIN1 6
#define STBY 5
#define BIN1 4
#define BIN2 3
#define PWMB 2

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);

  // Enable motor driver
  digitalWrite(STBY, HIGH);
}

int speed = 10;

void setMotor(int leftSpeed, int rightSpeed) {
  if (leftSpeed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    leftSpeed = -leftSpeed;
  }

  if (rightSpeed >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    rightSpeed = -rightSpeed;
  }

  leftSpeed  = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(PWMA, leftSpeed);
  analogWrite(PWMB, rightSpeed);
}


void loop() {
  setMotor(40, 40);
  delay(2000);

  setMotor(0, 0)
}
