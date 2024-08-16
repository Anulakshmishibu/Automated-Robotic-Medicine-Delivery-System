#include <SoftwareSerial.h>
 #include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


#define SIM800_TX_PIN 7
#define SIM800_RX_PIN 8
SoftwareSerial sim800(SIM800_TX_PIN, SIM800_RX_PIN);

int trigPin = 4;    // Trigger
int echoPin = 5;    // Echo
long duration, cm, inches;
int flag = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("initializing...");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(11 , LOW);
  pinMode(A0, INPUT);
    dht.begin();

    sim800.begin(9600);
  sendATCommand("AT+CMGF=1\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:

   digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
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
  Serial.print("A0 = ");
  Serial.println(analogRead(A0));
  if(analogRead(A0)<290)
  {
    digitalWrite(12,LOW);
  }
  else
  {
        digitalWrite(12,HIGH);

  }
  int Mvalue = map(cm,2 , 12 , 200 , 0);
  if(Mvalue> 200 && flag ==1)
  {
     digitalWrite(11 , LOW);
    Serial.println("full");
     sendSMS("+917034297806", "Water full Pump off");
     delay(1000);
    sendSMS("+917034297806", "Water full pump off");

    flag = 0;
  }

  
  Serial.print("level = ");
  Serial.println(Mvalue);



if(Mvalue <= 63)
{
      digitalWrite(11 , HIGH);

  Serial.println("WATER LOW");
  sendSMS("+917034297806", "Water Low Pump ON");
 flag=1;
}

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
delay(500);
}

void sendSMS(String phoneNumber, String message) {
  // Set phone number
  sim800.print("AT+CMGS=\"");
  sim800.print(phoneNumber);
  sim800.println("\"");
  delay(1000);
  
  // Set SMS text
  sim800.print(message);
  delay(1000);
  
  // Send the termination character
  sim800.println((char)26);
  delay(1000);
  
  // Wait for the SMS to be sent (it takes some time)
///  while (!sim800.available()) {}
  
  // Print the response from SIM800L module
 // while (sim800.available()) {
 //   Serial.write(sim800.read());
 // }
}

String sendATCommand(String command) {
  sim800.print(command);
  delay(1000);
  
  String response = "";
  while (sim800.available()) {
    char c = sim800.read();
    response += c;
  }
  
  return response;
}
