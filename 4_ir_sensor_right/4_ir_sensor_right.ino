// IR 

int lftM = 13; // left most ir
int rghtM = 2; // right most ir
int a = 11;   // left
int b =12;    // right
int lftC = 7;
int rghtC = 4;

//motors
int rt_1 = 8;   //RIGHT
int rt_2 = 10;  // RIGHT


int h = 6;  //RIGHT


int e = 5;   //LEFT
int f = 9;   //LEFT


int lft = 3;   // LEFT

int rspeed = 150 ;
int lspeed = 145;
int l = 0;

int iter = 0;

void setup(){

// IR SIGNAL
pinMode(a,INPUT);
pinMode(b,INPUT);
pinMode(lftM,INPUT);
pinMode(rghtM,INPUT);
pinMode(rghtC,INPUT);
pinMode(lftC,INPUT);
pinMode(A0,OUTPUT);
pinMode(A1,OUTPUT);
pinMode(A2,OUTPUT);
pinMode(A3,OUTPUT);
digitalWrite(A1,HIGH);
digitalWrite(A0,LOW);
digitalWrite(A2,LOW);
digitalWrite(A3,HIGH);
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
bool lftCen = digitalRead(lftC);
bool rghtCen = digitalRead(rghtC);


if(!left)
{
  if(!right)
  {
    if (rghtMost ) {
      iter = 0;

      hardRight();
      while(!(right || left) )
      {
        hardRight();
        left = digitalRead(a);
        right = digitalRead(b);
        delay(10);
      }
      l = 1;
    } else if (lftMost ) 
    {
      iter = 0; 

      hardLeft();
      l = 2;
    } else {
      if (l==1)
      {
        turnRight();
        delay(10);
        
        if (!lftCen && !rghtCen)
        {
           //deadend
           iter += 1;
            if (iter > 20) {
            // Dead end detected! Perform a U-turn
            while (!(left || right))
            {
              hardRight();
              left = digitalRead(a);
              right = digitalRead(b);
            }
            iter = 0;  // Reset the timer after the U-turn
            }
        } 
        l = 1;
      } else if (l==2) {
        turnLeft();
        delay(10);
        if (!lftCen && !rghtCen)
        {
           //deadend
           iter += 1;
            if (iter > 20) {
            // Dead end detected! Perform a U-turn
            while (!(left || right))
            {
              hardLeft();
              left = digitalRead(a);
              right = digitalRead(b);
            }
            iter = 0;  // Reset the timer after the U-turn
            }
        }
        l = 2;
      } else {
        digitalWrite(rt_1,HIGH);
        digitalWrite(rt_2,LOW);
        digitalWrite(f,HIGH);
        digitalWrite(e,LOW);
        analogWrite(h,rspeed);
        analogWrite(lft,lspeed);
        delay(10);

        // if (back == 0) {
          iter += 1;
        if (iter > 30) {
            // Dead end detected! Perform a U-turn
            while (!(left || right))
            {
              hardLeft();
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

    if (rghtMost ) {
      hardRight();
      while(!(right || left))
      {
        hardRight();
        right = digitalRead(b);
        left = digitalRead(a);
      }
      l = 1;
    } else if (lftMost) {
      hardLeft();
      l = 2;
    } else {
      turnRight();
      l = 1;
    }
  }
} else if(!right) {
  iter = 0;

  if (rghtMost) {
      hardRight();
      while (!(right || left))
      {
        hardRight();
        left = digitalRead(a);
        right = digitalRead(b);
      }
      l = 1;
  } else if (lftMost) 
    {
      hardLeft();
      l = 2;
    } else {
      turnLeft();
      l=2;
  }
} else {
  iter =0;
   Serial.println(2);
  if (lftMost && rghtMost)
  { 
    while((lftMost || rghtMost) && (left || right))
    {
    digitalWrite(rt_1,HIGH);
    digitalWrite(rt_2,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(e,LOW);
    analogWrite(h,rspeed);
    analogWrite(lft,lspeed);
    delay(10);
    }
    l=0;
  }
  else if (rghtMost){
    hardRight();
    while(!(left || right))
    {
      hardRight();
      left = digitalRead(a);
      right = digitalRead(b);
      Serial.println(10);
    }
    l=1;
  } else {
    digitalWrite(rt_1,HIGH);
    digitalWrite(rt_2,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(e,LOW);
    analogWrite(h,rspeed);
    analogWrite(lft,lspeed);
    Serial.println(11);
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
   analogWrite(lft,lspeed);
   delay(10);
}
void hardRight()
{
  digitalWrite(f,HIGH);
      digitalWrite(rt_2,HIGH);
      digitalWrite(rt_1,LOW);
      digitalWrite(e,LOW);
      analogWrite(h,rspeed);
      analogWrite(lft,lspeed);
      delay(10);
}