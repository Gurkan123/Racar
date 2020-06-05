//XPERT MIND.
//This program is used to control a robot using a app that communicates with Arduino through a bluetooth module.
//Error Code Chart: Code 01; Turnradius is higher than Speed; Code 02; Speed is higher than 255;
#define in1 12 //L298n Motor Driver pins.
#define in2 9
#define in3 10
#define in4 11

const int trigPin1 = 2;
const int echoPin1= 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;


long duration;
int distance,distance1,distance2,distance3,difference;
//Distance 1 - SOL
// DİSTANCE 2- ORTA

int command; //Int to store app command state.
int Speed = 255; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(trigPin3,OUTPUT);
  pinMode(echoPin3,INPUT);


  Serial.begin (9600);
  Serial1.begin(9600);

}

void loop()          
{
  Speed = 255;

   if(Serial1.available() <= 0) {
    
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration = pulseIn(echoPin1, HIGH);
    distance1 = (duration/2) / 29.1;

     digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration = pulseIn(echoPin2, HIGH);
    distance2 = (duration/2) / 29.1;

     digitalWrite(trigPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
    duration = pulseIn(echoPin3, HIGH);
    distance3 = (duration/2) / 29.1;
  //DİSTANCE 1 SAĞ, DİSTANCE 2 ORTA, DİSTANCE 3 SOL,



    if (distance2 > 22 && (distance3 > 16 && distance1 > 16)){ //ÖNÜ BOŞSA ÖNE GİT
        forward();
    }
    else if (distance1 > 20 || distance3 > 20)
    { 
       if (distance1 >= distance3){
          forwardright();
        }else{
          forwardleft();
         }
    }
      else {
      back();
    }

   }



    if(Serial1.available() > 0) {
      command = Serial1.read();
      switch (command) {
        case 'F':
          forward();
          break;
        case 'B':
          back();
          break;
        case 'L':
          left();
          break;
        case 'R':
          right();
          break;
        case 'G':
          forwardleft();
          break;
        case 'I':
          forwardright();
          break;
        case 'H':
          backleft();
          break;
        case 'J':
          backright();
          break;
        case '0':
          Speed = 100;
          break;
        case '1':
          Speed = 140;
          break;
        case '2':
          Speed = 153;
          break;
        case '3':
          Speed = 165;
          break;
        case '4':
          Speed = 178;
          break;
        case '5':
          Speed = 191;
          break;
        case '6':
          Speed = 204;
          break;
        case '7':
          Speed = 216;
          break;
        case '8':
          Speed = 229;
          break;
        case '9':
          Speed = 242;
          break;
        case 'q':
          Speed = 255;
          break;
      }
      Speedsec = Turnradius;
      if (brkonoff == 1) {
        brakeOn();
      } else {
        brakeOff();
      }
    }
}

void forward() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
  analogWrite(in1,0);
  analogWrite(in3,0);
}

void back() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
  analogWrite(in2,0);
  analogWrite(in4,0);
}

void left() {
  analogWrite(in1, Speed);
  analogWrite(in4, Speed);
   analogWrite(in2,0);
  analogWrite(in3,0);
}

void right() {
  analogWrite(in2, Speed);
  analogWrite(in3, Speed);
  analogWrite(in1,0);
  analogWrite(in4,0);
}
void forwardleft() {


//DOGRUSU
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
}
void forwardright() {


//DOGRUSU
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
}
void backright() {

//DOGRUSU
   analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
}
void backleft() {

  //DOGRUSU
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (lastButtonState == 'F') {
      if (buttonState == 'S') {
        back();
        delay(brakeTime);
        Stop();
      }
    }
    if (lastButtonState == 'B') {
      if (buttonState == 'S') {
        forward();
        delay(brakeTime);
        Stop();
      }
    }
    if (lastButtonState == 'L') {
      if (buttonState == 'S') {
        right();
        delay(brakeTime);
        Stop();
      }
    }
    if (lastButtonState == 'R') {
      if (buttonState == 'S') {
        left();
        delay(brakeTime);
        Stop();
      }
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}
void brakeOff() {

}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}
