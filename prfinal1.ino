#define enA 11//Enable1 L298 Pin enA 
#define in1 4 //Motor1  L298 Pin in1 
#define in2 5 //Motor1  L298 Pin in1 
#define in3 6 //Motor2  L298 Pin in1 
#define in4 7 //Motor2  L298 Pin in1 
#define enB 10 //Enable2 L298 Pin enB 
#define L_S A3 //ir sensor Left
#define R_S A4 //ir sensor Right
#define echo A2    //Echo pin
#define trigger A1 //Trigger pin
#define servo A5 //servo motor pin
int Set=10;
int distance_L, distance_F, distance_R, right, left; 

void setup(){ // put your setup code here, to run once
Serial.begin(9600); // start serial communication at 9600bps
pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input
pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  
pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 
analogWrite(enA, 255); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 255); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
pinMode(servo, OUTPUT);
servoPulse(servo,90);
distance_F = Ultrasonic_read();
delay(500);
}

void loop(){    
distance_F = Ultrasonic_read();
right=digitalRead(R_S);
left=digitalRead(L_S);
Serial.print("D F= ");Serial.println(distance_F);
Serial.print("right ");Serial.println(right);
Serial.print("left ");Serial.println(left);

 if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){
  if(distance_F > Set){
    forward();
    }
                  else{Stop();delay(1000);
                    Check_side();}  
 }  
else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){Stop();delay(1000);turnRight();delay(50);}  
else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){Stop();delay(1000);  turnLeft();delay(50);} 
else{
  Stop();
}
    
delay(500);
}
void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;      // Convert angle to microseconds
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(100); // Refresh cycle of servo
}

long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}
void compareDistance(){
    if(distance_L > distance_R){
  turnLeft();
  delay(250);
  forward();
  delay(600);
  turnRight();
  delay(100);
    
  }
  else{
  turnRight();
  delay(200);
  forward();
  delay(600);
  turnLeft();
  delay(100);
}
}
void Check_side(){
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
    Serial.print("D R=");Serial.println(distance_R);
    delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    Serial.print("D L=");Serial.println(distance_L);
    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    compareDistance();
}
void forward(){  //forward
digitalWrite(in1, LOW);  
digitalWrite(in2, HIGH); 
digitalWrite(in3, LOW);  
digitalWrite(in4, HIGH); 
}
void turnRight(){ //turnRight
digitalWrite(in1, HIGH);  
digitalWrite(in2, LOW);  
digitalWrite(in3, LOW); 
digitalWrite(in4, HIGH); 
}
void turnLeft(){ //turnLeft
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH); 
digitalWrite(in3, HIGH);  
digitalWrite(in4, LOW);  
}
void Stop(){ //stop
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW);  
digitalWrite(in3, LOW); 
digitalWrite(in4, LOW);  
}
