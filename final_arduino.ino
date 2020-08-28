#include <SD.h>
#include<SPI.h>
int CSPIN=10,ppr=51;
#define en 8
#define lm1 3 
#define lm2 5
#define ena A0
#define shr A5
#define bolten 7
#define bolt1 4
#define bolt2 6 
int counter;
int increcount; 
int unit=40;
File file;

void setup() {
   pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(en,INPUT);
  pinMode(shr,INPUT);
  pinMode(bolt1,OUTPUT);
  pinMode(bolt2,OUTPUT);
  pinMode(bolten,INPUT);
  
  Serial.begin(9600);
  Serial.println("initialising sd card....");
  //pinMode(CSPIN,OUTPUT);
  if(SD.begin(CSPIN))
  {
    Serial.println("SD card is ready...:)");
    
  }
  else
  {
    Serial.println("SD card initialisation failed");
    return;
  }
  file=SD.open("1234.txt",FILE_WRITE);
  Serial.println("press 1 to start");
  


}



double scandistance()
{
  double avg=0;
  for(int i=0;i<100;i++)
  {
    double v=analogRead(shr);
    delay(2);
    double d=((2914/(v+5))-1);
    avg=d+avg;
  }
  avg=avg/100;
  
  return(avg);
  
}
void sdwrite(double d)
{
  if(file)
  {
    file.println(d);
    
  }
  else
  {
    Serial.println("file could not be opened");
    
  }
}
void scanlayer()
{ counter=0;
  while(counter<ppr)
      {
         digitalWrite(lm1,LOW);
         digitalWrite(lm2,LOW);
  
         int k=digitalRead(en);
         delay(3);
  if(k==1)
  { 
    while(k==1)
    {analogWrite(ena,135);
      digitalWrite(lm1,HIGH);
    digitalWrite(lm2,LOW);
    k=digitalRead(en);
    delay(3);
    }analogWrite(ena,200);
    digitalWrite(lm1,LOW);
    digitalWrite(lm2,HIGH);
    delay(10);
    counter=counter+1;
    digitalWrite(lm1,LOW);
    digitalWrite(lm2,LOW);
    double h=scandistance();
    sdwrite(h);
  }
  else
  { 
    while(k==0)
    {
      analogWrite(ena,135);
      digitalWrite(lm1,HIGH);
    digitalWrite(lm2,LOW);
    k=digitalRead(en);
    delay(3);
    }
    analogWrite(ena,200);
    digitalWrite(lm1,LOW);
    digitalWrite(lm2,HIGH);
    delay(10);
    
    digitalWrite(lm1,LOW);
    digitalWrite(lm2,LOW);
  }
      }
     
   
  
}
void incrementz()
{
  int increment=1;
    
    increcount=0;
    while(increcount<(increment*unit))
    {
      digitalWrite(bolt1,LOW);
      digitalWrite(bolt2,LOW);
      counter=0;
  while(counter!=1)
{ 
  delay(2);
      digitalWrite(bolt1,HIGH);
      digitalWrite(bolt2,LOW);
      int c=1;
      int shr=digitalRead(bolten);
      while(shr==1)
      {shr=digitalRead(bolten);
      delay(2);
      
      if(c==1)
      {
        counter=counter+1;
        c=0;
      }
      
      }
     
      }
     digitalWrite(bolt1,LOW);
     digitalWrite(bolt2,HIGH);
     delay(10);
     
   digitalWrite(bolt1,LOW);
      digitalWrite(bolt2,LOW);

      increcount=increcount+1;
      //Serial.println(increcount);
    }
    
}
void loop() {
  if(Serial.available()>0)
  { int counter=0;
    int countbolten=0;
    int g=Serial.parseInt();
    int b=Serial.read();
    if(g==1)
    {double k=scandistance();
      while(k<15)
      { 
        scanlayer();
        incrementz();
        countbolten=countbolten+1;    
        k=scandistance();
        
      }
      file.close();
      Serial.println("file closed");
      Serial.println("scan completed");
      Serial.println("remove sd card");
      
    }
    


}}
