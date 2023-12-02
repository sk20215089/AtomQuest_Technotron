#include <Servo.h>
int data = 8;
int latch = 12;
int clk = 11;
Servo myservos[6];  // Assuming you have 2 servos, you can adjust this based on your actual number of servos

bool flag = false;
char lastChar;

void setup() {
  Serial.begin(115200);
  myservos[0].attach(10); 
  myservos[1].attach(4);
  myservos[2].attach(5);
  myservos[3].attach(6);
  myservos[4].attach(7);
  myservos[5].attach(9);
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  
  
}
void moveServo(int servoNumber, int angle) {
  if (servoNumber >= 0 && servoNumber < 6) {  // Check if the servoNumber is within the valid range
    myservos[servoNumber].write(angle);
  } else {
    Serial.println("Invalid servo number");
  }
}

void servoControl(int no ,bool &flag){
  Serial.println("drawer Called : ");
  Serial.println(no-1);
   if(no == 2 || no == 3){
    Serial.print("2 or 3 called");
  digitalWrite(latch,LOW);
  shiftOut(data,clk,MSBFIRST,0b00000001<<no-1);
  digitalWrite(latch,HIGH);
  for(int i = 80; i <= 180;i++){
        myservos[no-1].write(i);
        delay(30);
}
        delay(4000);
        for(int i = 180 ; i >= 80;i--){
        myservos[no-1].write(i);
        delay(30);
}
  digitalWrite(latch,LOW);
  shiftOut(data,clk,MSBFIRST,0b00000000);
  digitalWrite(latch,HIGH);
      flag = false;
}
else {
  Serial.println("others  called");
  digitalWrite(latch,LOW);
  shiftOut(data,clk,MSBFIRST,0b00000001<<no-1);
  digitalWrite(latch,HIGH);
  for(int i = 110 ; i >= 0;i--){
        moveServo(no - 1,i);
        delay(30);
}
       delay(4000);
        for(int i = 0 ; i <= 110;i++){
        moveServo(no - 1,i);
        delay(30);
}
  digitalWrite(latch,LOW);
  shiftOut(data,clk,MSBFIRST,0b00000000);
  digitalWrite(latch,HIGH);
      flag = false;
}
}
void loop() {
  if (Serial.available() > 0) {
    // Read the data from the serial port
    String receivedData = Serial.readStringUntil('\n');
    int stringLength = receivedData.length();
  
  // Get the last character
   lastChar = receivedData.charAt(stringLength - 2);
  
  // Convert the last character to an integer
   
  
  // Print the result
  Serial.print("Original String: ");
  Serial.println(receivedData);
  Serial.print("Last Value (as integer): ");
  Serial.println(lastChar);
    // Process the received data
//    Serial.print("Received Data: ");
//    Serial.println(receivedData);
      int lastval = lastChar - '0';
      Serial.println(lastval);
    if( lastval >=0 && lastval <=6 ){
      flag = true;
       Serial.println(flag);
        if(flag){
    servoControl(lastval,flag);
    Serial.println("called");
    
    }
  }
 
}
}