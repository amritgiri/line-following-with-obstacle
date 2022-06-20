// ultra sonic
#define L_TRIGGER_PIN 9
#define L_ECHO_PIN 10
#define R_TRIGGER_PIN 6
#define R_ECHO_PIN 5

//sensor
#define R_SENSOR 3
#define M_SENSOR 4
#define L_SENSOR 2

//motor
#define rightmotorpin1 12
#define leftmotorpin1 8
#define rightmotorpin2 11
#define leftmotorpin2 7 

int leftsensorstate;
int midsensorstate;
int rightsensorstate;
int result;


long duration , distance, duration2, distance2;

void setup() {
  
  pinMode(L_TRIGGER_PIN, OUTPUT);         // set trig pin as output
  pinMode(L_ECHO_PIN, INPUT);             //set echo pin as input to capture reflected waves
  pinMode(R_TRIGGER_PIN, OUTPUT);
  pinMode(R_ECHO_PIN, INPUT);
  
  pinMode(R_SENSOR, INPUT);
  pinMode(M_SENSOR, INPUT);
  pinMode(L_SENSOR, INPUT);
  pinMode(rightmotorpin1, OUTPUT);
  pinMode(rightmotorpin2, OUTPUT);
  pinMode(leftmotorpin1, OUTPUT);
  pinMode(leftmotorpin2, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  leftsensorstate = digitalRead(L_SENSOR);
  midsensorstate = digitalRead(M_SENSOR);
  rightsensorstate = digitalRead(R_SENSOR);
  
  
  result = (leftsensorstate<<2|midsensorstate<<1|rightsensorstate<<0);
   
   //ultra sensor
  if(result == 0b000){//0b for binary
    ultra();
  
  }
   //ir sensor
  else{
    irs();
  }
}

//ultrasonic
void ultra(){
  // INPUT DISTANCE
  //FOR LEFT ULTRA SENSOR
  digitalWrite(L_TRIGGER_PIN, LOW);
  delayMicroseconds(2);//if default is high then to make it low
  digitalWrite(L_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(L_ECHO_PIN, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  delay(50);
  
  //FOR RIGHT ULTRA SENSOR
  digitalWrite(R_TRIGGER_PIN, LOW);
  delayMicroseconds(2);//if default is high then to make it low
  digitalWrite(R_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  duration2 = pulseIn(R_ECHO_PIN, HIGH); // receive reflected waves
  distance2 = duration2 / 58.2;   // convert to distance
  delay(50);

  //DISTANCE CHECK
  if(distance<15 && distance2<15){
    forward();
  }
  else if(distance<15 && distance2>15){
    right();
  }
  else if(distance>15 && distance2<15){
    left();
  }
  else{
    loop();
  }
      
}

//ir sensor
void irs(){
  if(result == 0b010){
    forward();
  }
  else if(result== 0b011 || result == 0b001){
    right();
  }
  else if(result == 0b110 || result == 0b100){
    left();
  }
}


void left(){
    digitalWrite(leftmotorpin1, HIGH);
    digitalWrite(leftmotorpin2, LOW);
    digitalWrite(rightmotorpin1, LOW);
    digitalWrite(rightmotorpin2, LOW);

    delay(50); // DELAY CAN BE IGNORED
}


void right(){
  digitalWrite(leftmotorpin1, LOW);
    digitalWrite(leftmotorpin2, LOW);
    digitalWrite(rightmotorpin1, HIGH);
    digitalWrite(rightmotorpin2, LOW);
    
    delay(50);
}


void forward(){
  
    digitalWrite(leftmotorpin1, HIGH);
    digitalWrite(leftmotorpin2, LOW);
    digitalWrite(rightmotorpin1, HIGH);
    digitalWrite(rightmotorpin2, LOW);

}

void stopr(){
  
    digitalWrite(leftmotorpin1, LOW);
    digitalWrite(leftmotorpin2, LOW);
    digitalWrite(rightmotorpin1, LOW);
    digitalWrite(rightmotorpin2, LOW);

}