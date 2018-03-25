#include <EEPROM.h>
//DHT22 TEMPERATURE RANGE: -40 TO 80 DEGREE CERCIUS
//DHT22 HUMIDITY RAGNE: 0 TO 100 %
//#include <dht11.h>
#include "DHTesp.h"
DHTesp dht;
#include <LiquidCrystal.h>

//dht11 sensor;

LiquidCrystal lcd(2,3,4,5,6,7);//rs,e,d4,d5,d6,d7
#define dht11pin 8



#define tempActuator 9 //rel2()
#define humActuator 10 //rel1()
#define resetbtn 11
#define plusbtn 12
#define negbtn 13
#define nextbtn 1

//function declaration
void  setScreen(int ,int ,int ,int );


//variable declarations
static int t1=0,t2=0,h1=0,h2=0,temp=0;//hold temperature and humidity value ranges

static int val=0,btnPress=0;
//static int checkState=0;
int state,state2;
static int test=0;//test the next press

//static int valForT1,valForT2,btnPressT;
//static int valForH1,valForH2,btnPressH;

int cursPos1,cursPos2;

//static int pos1=0,pos2=0,pos3=0,pos4=0;
static int setVal=0;

void setup() {

dht.setup(8); // Connect DHT sensor to pin 8

    lcd.begin(16,2);
  lcd.clear();

   pinMode(tempActuator,OUTPUT);
  pinMode(humActuator,OUTPUT);
 
  
  //declaring the buttons
  //pinMode(resetbtn,INPUT);
  pinMode(nextbtn,INPUT_PULLUP);
  pinMode(plusbtn,INPUT_PULLUP);
  pinMode(negbtn,INPUT_PULLUP);
  
//---------------READING THE PREVIOUS t1,t2,h1,h2 set values----------------
t1=EEPROM.read(2);//t1
t2=EEPROM.read(5);//t2
h1=EEPROM.read(8);//h1
h2=EEPROM.read(11);//h2

}

void loop() {
  //int sens=sensor.read(dht11pin); //read dht values 
  //int tempVal=sensor.temperature;//temperature value
 // int humVal=sensor.humidity;//humidity value

  int humVal = dht.getHumidity();
  int tempVal = dht.getTemperature();

  //HOME SCREEN
  homeScreen();
  delay(100);
}

void homeScreen()
{
  lcd.clear();
  lcd.print("T :");
  lcd.print((int)dht.getTemperature());
  lcd.print("C");
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.print((int)dht.getHumidity());
  lcd.print("%");
  lcd.setCursor(1,1);
  
  //--------------------t1 HAS TO BE ENTERED BY THE USER------------------------------
  lcd.print(t1);//minimum temperature in the range
  lcd.setCursor(3,1);
  lcd.print("-");

  //--------------------t2 HAS TO BE ENTERED BY THE USER-------------------------------
  lcd.print(t2);//max temperature in the range
  lcd.setCursor(6,1);
  lcd.print("C");
  lcd.setCursor(10,1);

   //--------------------h1 HAS TO BE ENTERED BY THE USER-------------------------------
  lcd.print(h1);//min humidity in the range
  lcd.setCursor(12,1);
  lcd.print("-");

   //--------------------h2 HAS TO BE ENTERED BY THE USER-------------------------------
  lcd.print(h2);
  lcd.setCursor(15,1);
  lcd.print("%");
  /*
  state=digitalRead(modebtn);//1,0
  if(state==1)
  {
    //digitalWrite(led,HIGH);
    setScreen(t1,t2,h1,h2);
  }
  else if (state==0)
  {
   // digitalWrite(led,LOW);
   ;
  }
  */
  nextFunct();//check if the nextbtn is being pressed to change the values
  //delay for the home screen
  delay(100);

}


  void nextFunct()
  {
    //if the home screen button is pressed then move to it
   /*if(digitalRead(modebtn))
    {
      goto END;
    }
   */
    //while nextbtn is once pressed go to 1*1

    START:
    delay(100);
    if(digitalRead(nextbtn)&&(test==0))
    {
      delay(100);
      posAdjust(1,0,0,0);
     // delay(100);
       while(!digitalRead(nextbtn));
      test++;
 
    }
    //while nextbtn is twice pressed go to 4*1
    if(digitalRead(nextbtn)&&(test==1))
    {
      
      posAdjust(0,1,0,0);
     // delay(100);
       while(!digitalRead(nextbtn));
      test++;
    }
    
    //while nextbtn is thrice pressed go to 10*1
    if(digitalRead(nextbtn)&&(test==2))
    {
      posAdjust(0,0,1,0);

    //  delay(100);
       while(!digitalRead(nextbtn));
      test++;
    }
    //while nextbtn is pressed for the forth times go to 13*1
    if(digitalRead(nextbtn)&&(test==3))
    {
      
      posAdjust(0,0,0,1);
      
      
    //  delay(100);
      //adjustIt(h2);
      while(!digitalRead(nextbtn));
      test++;
    }
    //while nextbtn is pressed then turn off the cursor blinking
    if(digitalRead(nextbtn)&&(test==4))
    {
      
      posAdjust(0,0,0,0);
      
      
    //  delay(100);
      //adjustIt(h2);
      while(!digitalRead(nextbtn));
      test=0;
      goto START;
    }
    
  }

  int posAdjust(int pos1,int pos2,int pos3,int pos4)
{
  //setting the cursor position 
  
  
   //CURSOR  POSITIONS
  //************************************************************************************//
  delay(100);
 //@t1
  if (pos1==1 && pos2==0&& pos3==0 && pos4==0)//for T1
  {
    cursPos1=1;
    cursPos2=1;
    lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForT1,btnPressT
      //return(t1);
      //RETURNING CURSOR POSITIONS
//-------------------------READING t1's val,btnPress VALUES FROM EEPROM------------------------
 val=EEPROM.read(0);//reading val from address 0
  
  btnPress=EEPROM.read(1);//reading btnPress from address 1
//----------------------------------------------------------------------------------------

      
      //PASSING THE VALUES TO FUNCTION
      setScreenAdjust(cursPos1,cursPos2);//call and return its value to position 1
      t1=setVal;
  //----------------------------WRITING all t1 values to EEPROM-------------------------
      //updating t1 val EEPROM memory address 0
  EEPROM.update(0,val);
  //updating t1 btnPress in the EEPROM memory address 1
  EEPROM.update(1,btnPress);
  //updating the t1 new value set for the t1 address 2
  EEPROM.update(2,val*10+btnPress);
  //-------------------------------------------------------------------------------
 
      
      //lcd.print(t1);
      pos1=0;pos2=1;pos3=0;pos4=0;
      delay(100);
      
  }
  //@t2
  if (pos1==0 && pos2==1&& pos3==0 && pos4==0)//for T2
  {
    cursPos1=4;
    cursPos2=1;
  lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForT2,btnPressT
//-------------------------READING t2's val,btnPress VALUES FROM EEPROM------------------------
 val=EEPROM.read(3);//reading val from address 3
  
  btnPress=EEPROM.read(4);//reading btnPress from address 4
//----------------------------------------------------------------------------------------

      //PASSING THE VALUES TO FUNCTION
      setScreenAdjust(cursPos1,cursPos2);
      t2=setVal;
   //----------------------------WRITING all t2 values to EEPROM-------------------------
 //updating t2 val in its EEPROM memory address 3
  EEPROM.update(3,val);
  //updating t2 btnPress in the EEPROM memory address 4
  EEPROM.update(4,btnPress);
  //updating the t2 new value set for the t2 address 5
  EEPROM.update(5,val*10+btnPress);
  //-------------------------------------------------------------------------------
 
      //WRITING t2 to EEPROM
    
      pos1=0;pos2=0;pos3=1;pos4=0;
      delay(100);
      
  }

  //@h1
  if (pos1==0 && pos2==0&& pos3==1 && pos4==0)//for H1
  {
     cursPos1=10;
    cursPos2=1;
    lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForH1,btnPressH
//-------------------------READING h1's val,btnPress VALUES FROM EEPROM------------------------
 val=EEPROM.read(6);//reading val from address 6
  
  btnPress=EEPROM.read(7);//reading btnPress from address 7
//----------------------------------------------------------------------------------------

      //PASSING THE VALUES TO FUNCTION
      setScreenAdjust(cursPos1,cursPos2);
      h1=setVal;
      //WRITING h1 TO EEPROM
   //----------------------------WRITING all h1 values to EEPROM-------------------------
 //updating h1 val in its EEPROM memory address 6
  EEPROM.update(6,val);
  //updating h1 btnPress in the EEPROM memory address 7
  EEPROM.update(7,btnPress);
  //updating the h1 new value set for the h1 address 8
  EEPROM.update(8,val*10+btnPress);
  //-------------------------------------------------------------------------------
 
    
      pos1=0;pos2=0;pos3=0;pos4=1;
      delay(100);
  }

  //@h2
  if (pos1==0 && pos2==0&& pos3==0 && pos4==1)//for H2
  {
     cursPos1=13;
    cursPos2=1;
    lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForH2,H
 //-------------------------READING h2's val,btnPress VALUES FROM EEPROM------------------------
val=EEPROM.read(9);//reading val from address 9
  
  btnPress=EEPROM.read(10);//reading btnPress from address 10
//----------------------------------------------------------------------------------------

      //PASSING THE VALUES TO FUNCTION
      setScreenAdjust(cursPos1,cursPos2);
      h2=setVal;
      //WRITING h2 TO EEPROM
      //----------------------------WRITING all h2 values to EEPROM-------------------------
 //updating h2 val in its EEPROM memory address 9
  EEPROM.update(9,val);
  //updating h2 btnPress in the EEPROM memory address 10
  EEPROM.update(10,btnPress);
  //updating the h2 new value set for the h2 address 11
  EEPROM.update(11,val*10+btnPress);
  //-------------------------------------------------------------------------------
 
  
      pos1=0,pos2=0;pos3=0;pos4=0;
     // homeScreen();
     delay(100);
      
  }

  //cursor blink off
  if (pos1==0 && pos2==0&& pos3==0 && pos4==0)//for cursor blink off
  {
      lcd.noBlink();
      //RETURN THE valForH2,H
      //PASSING THE VALUES TO FUNCTION
      //setScreenAdjust(cursPos1,cursPos2);
     // h2=setVal;
      //WRITING h2 TO EEPROM
  
     // pos1=0,pos2=0;pos3=0;pos4=0;
     
     //pos1=1,pos2=0;pos3=0;pos4=0;
     delay(100);
      abort();
     
      
  }

 
  //return cursPos;
  //************************************************************************************//
 
  //changing the values in the positions
  
  
}

int setScreenAdjust(int curspos1,int curspos2)
{
  

  
  
  
    while(1)//keep incrementing the values in the cursor position
      {
         //-----------------------------------------------------------------------------
       
      delay(100);
          
        if(digitalRead(nextbtn))//if nextbtn is pressed exit thesetScreenAdjust() and move to the next cursor position through posAdjust()
      {
        break;//get out of the loop and leave the function setScreenAdjust()
      }
       //---------------------------------------------------------------------------- 
      
      
      if(digitalRead(plusbtn))//TEMPERATURE RANGE -40 T0 80 DEGREE CELCIUS
      {
                   btnPress++;
                   lcd.setCursor(curspos1,curspos2);
if(btnPress==10)
{
  btnPress=0;
  val++;
}
if((val*10+btnPress<10)&&(val*10+btnPress>=0))// 0<=x<10
{
  lcd.print("0");
}

if(val*10+btnPress>=100)
{
  val=0;
  btnPress=0;
}
lcd.print(val*10+btnPress);
        
      }
      
    
      if(digitalRead(negbtn))
{
  lcd.setCursor(curspos1,curspos2);
btnPress--;
if(btnPress==0)
{
  if(val*10+btnPress==0)
  goto END;
  btnPress=9;
  val--;
}
END:
if((val*10+btnPress<10)&&(val*10+btnPress>=0))//0<=x<10
{
  lcd.print("0");
}

if(val*10+btnPress<=0)
{
  val=0;
  btnPress=0;
}
lcd.print(val*10+btnPress);
}


  setVal= val*10+btnPress;  
      
      } 
      
      
      }
 

