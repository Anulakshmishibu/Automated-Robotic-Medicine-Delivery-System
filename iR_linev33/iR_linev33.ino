// Define sensor pins
#define IR_SENSOR_RIGHT_PIN A2
#define IR_SENSOR_LEFT_PIN A0
#define IR_trig A3
const int trigPin = 6;
const int echoPin = 7;
long duration, cm, inches;

// Define motor pins
#define MOTOR1_PIN1 3
#define MOTOR1_PIN2 2
#define MOTOR2_PIN1 4
#define MOTOR2_PIN2 5

int trigFlag , count , flag ;
void setup() {
  // Initialize sensor pins as inputs
  Serial.begin(9600);
  pinMode(IR_SENSOR_RIGHT_PIN, INPUT);
  pinMode(IR_SENSOR_LEFT_PIN, INPUT);
  pinMode(IR_trig, INPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
analogWrite(9,150);
analogWrite(10,150);
  // Initialize motor pins as outputs
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void loop() {
  // Read sensor values
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
   pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  

  
  int sensorRightValue = digitalRead(IR_SENSOR_RIGHT_PIN);
  int sensorLeftValue = digitalRead(IR_SENSOR_LEFT_PIN);
  Serial.print("right =");
  Serial.println(digitalRead(IR_SENSOR_RIGHT_PIN));
  Serial.print("Left =");
  Serial.println(digitalRead(IR_SENSOR_LEFT_PIN));
  Serial.print("TRig =");
  Serial.println(digitalRead(IR_trig));
 trigFlag= digitalRead(IR_trig);
 
Serial.println(count);

  // If both sensors detect the line
  if (sensorRightValue == LOW && sensorLeftValue == LOW  && count == 1 && cm>=15) {
    moveForward();
  }

  if (sensorRightValue == LOW && sensorLeftValue == LOW  && count == 2 && cm>=15) {
    moveForward();
  }
  else if (sensorRightValue == LOW && sensorLeftValue == LOW  && count == 3 && cm>=15) {
    moveback();
  }
  else if (sensorRightValue == LOW && sensorLeftValue == LOW  && count == 4 && cm>=15) {
    moveback();
  } 
  // If only the left sensor detects the line
  else if (sensorLeftValue == LOW &&( count == 1 ||  count == 2) && cm>=15) {
    // Turn right
    turnRight();
  } 
  // If only the right sensor detects the line
  else if (sensorRightValue == LOW && ( count == 1 ||  count == 2)&& cm>=15) {
    // Turn left
    turnLeft();
  } 

  else if (sensorLeftValue == LOW &&( count == 3 ||  count == 4)&& cm>=15) {
    // Turn right
    turnLeft();
        Serial.println("Reverse left");

  } 
  // If only the right sensor detects the line
  else if (sensorRightValue == LOW && ( count == 3 ||  count == 4)&& cm>=15) {
    // Turn left
            Serial.println("Reverse left");
    turnRight();
  } 
  // If both sensors don't detect the line
  else if(sensorRightValue == HIGH && sensorLeftValue == HIGH && count==0&& cm>=15 ) {
    stopMotors(); 
    if(!trigFlag)
    count =1;
    
  }

    else if(sensorRightValue == HIGH && sensorLeftValue == HIGH && count==1 && cm>=15) {
        moveForward();
        count = 2;
        delay(2000);
  }

    else if(sensorRightValue == HIGH && sensorLeftValue == HIGH && count==2 && cm>=15 ) {
    stopMotors(); 
    if(trigFlag)
    count =3;
    
  }
      else if(sensorRightValue == HIGH && sensorLeftValue == HIGH && count==3 && cm>=15) {
       moveback();
        count = 4;
        delay(2000);
    
  }

        else if(sensorRightValue == HIGH && sensorLeftValue == HIGH && count== 4 && cm>=15 ) {
        count = 0;
        stopMotors(); 

    
  }
  else
  {
    stopMotors();
  }
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
analogWrite(9,150);
analogWrite(10,150);
}

void moveback() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, HIGH);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, HIGH);
analogWrite(9,150);
analogWrite(10,150);
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
  
analogWrite(9,130);
analogWrite(10,130);
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
  
analogWrite(9,130);
analogWrite(10,130);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
}
