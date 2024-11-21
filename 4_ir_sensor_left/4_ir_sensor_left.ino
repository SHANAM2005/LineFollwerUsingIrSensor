// IR 

int lftM = 13; // left most ir
int rghtM = 2; // right most ir
int a = 11;   // left
int b =12;    // right

//motors
int rt_1 = 8;   //RIGHT
int rt_2 = 10;  // RIGHT

int iter =0;
int h = 6;  //RIGHT


int e = 5;   //LEFT
int f = 9;   //LEFT


int lft = 3;   // LEFT

int rspeed = 200 ;
int lspeed = 186;
int l = 0;


void setup(){

// IR SIGNAL
pinMode(a,INPUT);
pinMode(b,INPUT);
pinMode(lftM,INPUT);
pinMode(rghtM,INPUT);
//RIGHT MOTOR 
pinMode(rt_1,OUTPUT);
pinMode(rt_2,OUTPUT);

//LEFT MOTOR
pinMode(e, OUTPUT);
pinMode(f,OUTPUT);

//CONTROL SPEED
analogWrite(h,rspeed);
analogWrite(lft,lspeed);
//LEFT
pinMode(lft,OUTPUT);
//RIGHT
pinMode(h,OUTPUT);

digitalWrite(rt_1,HIGH);
digitalWrite(rt_2,LOW);
digitalWrite(f,HIGH);
digitalWrite(e,LOW);
delay(200);
Serial.begin(9600);

}

void loop(){

bool left = digitalRead(a);
bool right = digitalRead(b);
bool lftMost = digitalRead(lftM);
bool rghtMost = digitalRead(rghtM);


if(!left)
{
  Serial.print(1);
  if(!right)
  {
    if (lftMost) 
    {
      iter =0;
      hardLeft();
      while(!(left || right))
      {
        hardLeft();
        left = digitalRead(a);
        right = digitalRead(b);
      }
      l = 2;
    } else if (rghtMost) {
      iter =0;
      hardRight();
      l = 1;
    } else {
      if (l==1)
      {
        iter =0;
        turnRight();
        l = 1;
      } else if (l==2) {
        iter =0 ;
        turnLeft();
        l = 2;
      } else {
        digitalWrite(rt_1,HIGH);
        digitalWrite(rt_2,LOW);
        digitalWrite(f,HIGH);
        digitalWrite(e,LOW);
        analogWrite(h,rspeed);
        analogWrite(lft,lspeed);
        delay(10);

        iter += 1;
        if (iter > 30) {
            // Dead end detected! Perform a U-turn
            while (!(left || right))
            {
              hardRight();
              left = digitalRead(a);
              right = digitalRead(b);
              delay(10);
            }
            iter = 0;  // Reset the timer after the U-turn
        }
        l=0;
      }
    } 
  } else {
    iter = 0;
    if (lftMost) 
    {
      hardLeft();
      while(!(left || right))
      {
        hardLeft();
        left = digitalRead(a);
        right = digitalRead(b);
      }
      l = 2;
    } else if (rghtMost) {
      hardRight();
      l = 1;
    } else {
      turnRight();
      l = 1;
    }
  }
} else if(!right) {
  iter =0;
  if (rghtMost) {
      hardRight();
      l = 1;
  } else if (lftMost) 
    {
      hardLeft();
      while (!(left || right))
      {
        hardLeft();
        left = digitalRead(a);
        right = digitalRead(b);
      }
      l = 2;
    } else {
      turnLeft();
      l=2;
  }
} else {
  iter =0;
  if (lftMost && rghtMost)
  {
    digitalWrite(rt_1,HIGH);
    digitalWrite(rt_2,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(e,LOW);
    analogWrite(h,rspeed);
    analogWrite(lft,lspeed);
    delay(10);
    l=0;
  }
  else if (lftMost){
    hardLeft();
    while(!(left || right))
    {
      hardLeft();
      left = digitalRead(a);
      right = digitalRead(b);
    }
    l=2;
  } else {
    digitalWrite(rt_1,HIGH);
    digitalWrite(rt_2,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(e,LOW);
    analogWrite(h,rspeed);
    analogWrite(lft,lspeed);
    l=0;
  }
}

}

void turnLeft()
{
  digitalWrite(rt_1,HIGH);
      digitalWrite(rt_2,LOW);
      digitalWrite(f,HIGH);
      digitalWrite(e,LOW);
      analogWrite(h,rspeed);
      analogWrite(lft,0);
      delay(10);
}
void turnRight()
{
  digitalWrite(f,HIGH);
      digitalWrite(rt_2,LOW);
      digitalWrite(rt_1,HIGH);
      digitalWrite(e,LOW);
      analogWrite(h,0);
      analogWrite(lft,lspeed);
      delay(10);
}
void hardLeft()
{
   digitalWrite(f,LOW);
   digitalWrite(rt_2,LOW);
   digitalWrite(rt_1,HIGH);
   digitalWrite(e,HIGH);
   analogWrite(h,rspeed);
   analogWrite(lft,lspeed-50);
   delay(10);
}
void hardRight()
{
  digitalWrite(f,HIGH);
      digitalWrite(rt_2,HIGH);
      digitalWrite(rt_1,LOW);
      digitalWrite(e,LOW);
      analogWrite(h,rspeed-50);
      analogWrite(lft,lspeed);
      delay(10);
}