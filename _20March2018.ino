//check test 2

#include <EEPROM.h>
//DHT22 TEMPERATURE RANGE: -40 TO 80 DEGREE CERCIUS
//DHT22 HUMIDITY RAGNE: 0 TO 100 %
#include <dht11.h>
#include <LiquidCrystal.h>

dht11 sensor;
LiquidCrystal lcd(2,3,4,5,6,7);//rs,e,d4,d5,d6,d7
#define dht11pin 8



#define tempActuator 9 //rel2()
#define humActuator 10 //rel1()
#define modebtn 11
#define plusbtn 12
#define negbtn 13
#define nextbtn 1

//function declaration
void  setScreen(int ,int ,int ,int );


//variable declarations
static int t1=0,t2=0,h1=0,h2=0,val=0,temp=0;//hold temperature and humidity value ranges
//static int checkState=0;
int state,state2;
static int test=0;//test the next press

static int valForT1,valForT2,btnPressT;
static int valForH1,valForH2,btnPressH;

int cursPos1,cursPos2;



void setup() {

    lcd.begin(16,2);
  lcd.clear();

   pinMode(tempActuator,OUTPUT);
  pinMode(humActuator,OUTPUT);
 
  
  //declaring the buttons
  pinMode(modebtn,INPUT_PULLUP);
  pinMode(nextbtn,INPUT_PULLUP);
  pinMode(plusbtn,INPUT_PULLUP);
  pinMode(negbtn,INPUT_PULLUP);
  


}

void loop() {
  int sens=sensor.read(dht11pin); //read dht values 
  int tempVal=sensor.temperature;//temperature value
  int humVal=sensor.humidity;//humidity value

  //HOME SCREEN
  homeScreen();
  
}

void homeScreen()
{
  lcd.clear();
  lcd.print("T :");
  lcd.print((int)sensor.temperature);
  lcd.print("C");
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.print((int)sensor.humidity);
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
  //delay for the home screen
  delay(100);

}


void setScreen(int t1,int t2,int h1,int h2) //the screen to make settings of your device
  {
  
    //checkState=1;
    while(1)
    {
  BLOCK:  
    lcd.clear();
    
    
    lcd.print("Tmin:");
    lcd.setCursor(5,0);

    //***************SETTING CURSOR POSITION*******************************
   // lcd.setCursor(5,0);
   // lcd.blink();
   // delay(1000);

    
    lcd.print(t1);//min temp

    lcd.setCursor(7,0);
    lcd.print("C");
    
    lcd.setCursor(10,0);
    lcd.print("Tmax:");
    
    lcd.setCursor(14,0);
    lcd.print(t2);//max temp

    
    
    lcd.setCursor(0,1);
    lcd.print("Hmin:");
    lcd.setCursor(5,1);
    lcd.print(h1);//min humidity

    lcd.setCursor(7,1);
    lcd.print("%");
    
    lcd.setCursor(10,1);
    lcd.print("Hmax:");
    lcd.setCursor(14,1);
    lcd.print(h2);//max humidity

    //////////////////////////////////////////////////////////////////////////////
    nextFunct();
    /////////////////////////////////////////////////////////////////////////////
    
    //READING THE MENU BUTTON
    
    delay(100);//delay 
    state=digitalRead(modebtn);//1,0
    
  if(state==1)
  {
    state=0;
    break;
  }
     
   /*/////////////////////////////////////////////////////////////////////////////////////
   
  //READING THE NEXT BUTTON
  state2=digitalRead(nextbtn);//1,0
    
  if(state2==1)
  {
  //lcd.setCursor(5,0);
     // lcd.blink();
  }
    
    
    */////////////////////////////////////////////////////////////////////////////////////// 

    goto BLOCK;
    }
  }

  void nextFunct()
  {
    //if the home screen button is pressed then move to it
   /*if(digitalRead(modebtn))
    {
      goto END;
    }
   */
    //while nextbtn is once pressed go to 5*0
    if(digitalRead(nextbtn)&&(test==0))
    {
      posAdjust(1,0,0,0);
     // delay(100);
       while(!digitalRead(nextbtn));
      test++;
 
    }
    //while nextbtn is twice pressed go to 14*0
    if(digitalRead(nextbtn)&&(test==1))
    {
      
      posAdjust(0,1,0,0);
     // delay(100);
       while(!digitalRead(nextbtn));
      test++;
    }
    
    //while nextbtn is thrice pressed go to 5*1
    if(digitalRead(nextbtn)&&(test==2))
    {
      posAdjust(0,0,1,0);

    //  delay(100);
       while(!digitalRead(nextbtn));
      test++;
    }
    //while nextbtn is pressed for the forth times go to 14*1
    if(digitalRead(nextbtn)&&(test==3))
    {
      
      posAdjust(0,0,0,1);
      
      
    //  delay(100);
      //adjustIt(h2);
      while(!digitalRead(nextbtn));
      test=0;
    }
    
  }

  //////// ADJUST THE VALUES//////////////////////////////
  /*
  void adjustIt(int plusneg)
{
   if(digitalRead(plusbtn))
{
  plusneg++;
  lcd.print(plusneg);
  delay(100);
}
if(digitalRead(negbtn))
{
  plusneg--;
  lcd.print(plusneg);
  delay(100);
}

}
*/
int posAdjust(int pos1,int pos2,int pos3,int pos4)
{
  //setting the cursor position 
  
  
   //CURSOR  POSITIONS
  //************************************************************************************//
  if (pos1==1 && pos2==0&& pos3==0 && pos4==0)//for T1
  {
    cursPos1=5;
    cursPos2=0;
    lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForT1,btnPressT
      //return(t1);
      //RETURNING CURSOR POSITIONS

      //PASSING THE VALUES TO FUNCTION
      t1=setScreenAdjust(cursPos1,cursPos2);//call and return its value to position 1
      //WRITING t1 value to EEPROM

      
      //lcd.print(t1);
      pos1=0;pos2=1;pos3=0;pos4=0;
      
  }
  if (pos1==0 && pos2==1&& pos3==0 && pos4==0)//for T2
  {
    cursPos1=14;
    cursPos2=0;
  lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForT2,btnPressT
      //PASSING THE VALUES TO FUNCTION
      t2=setScreenAdjust(cursPos1,cursPos2);
      //WRITING t2 to EEPROM
      
      pos1=0;pos2=0;pos3=1;pos4=0;
  }
  if (pos1==0 && pos2==0&& pos3==1 && pos4==0)//for H1
  {
     cursPos1=5;
    cursPos2=1;
    lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForH1,btnPressH
      //PASSING THE VALUES TO FUNCTION
      h1=setScreenAdjust(cursPos1,cursPos2);
      //WRITING h1 TO EEPROM
      
      pos1=0;pos2=0;pos3=0;pos4=1;
  }
  if (pos1==0 && pos2==0&& pos3==0 && pos4==1)//for H2
  {
     cursPos1=14;
    cursPos2=1;
    lcd.setCursor(cursPos1,cursPos2);
      lcd.blink();
      //RETURN THE valForH2,H
      //PASSING THE VALUES TO FUNCTION
      h2=setScreenAdjust(cursPos1,cursPos2);
      //WRITING h2 TO EEPROM
      
      //state=0;//set the menu button as zero
      pos1=1;pos2=0;pos3=0;pos4=0;
     // homeScreen();
      
  }
  //return cursPos;
  //************************************************************************************//
 
  //changing the values in the positions
  
  
}

int setScreenAdjust(int curspos1,int curspos2)
{
  

  
  int btnPress=0;
  
    while(1)
      {
         //-----------------------------------------------------------------------------
       
       delay(100);
        if(digitalRead(nextbtn))
      {
        break;//get out of the loop and leave the function
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

if(val*10+btnPress==80)
{
  ;//do nothing
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
lcd.print(val*10+btnPress);
}
    
      
      }      }
 

