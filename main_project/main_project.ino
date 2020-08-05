/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 07 Dec 2018 15:52:10 GMT
 */
#include "Arduino.h"
#include <LWiFi.h>
#include "MCS.h"
#include "LTimer.h"
#include <Wire.h>
#include <adxl345_blockly.h>


float Acc,temp_Acc,Force,P,v; 
float Pressure_data=0;
float t=1e-2;
char _lwifi_ssid[] = " "; //Enter your wifi id
char _lwifi_pass[] = " ";  //Enter your wifi password
MCSDevice mcs("DFyCgmSG", "gPqOk9as8VnShE9E");

MCSDisplayFloat Pressure("Pressure");
MCSDisplayFloat Acceleration("Acceleration");
MCSDisplayFloat Calorie("Calorie");
//MCSDisplayFloat xx("xx");
//MCSDisplayFloat yy("yy");
//MCSDisplayFloat zz("zz");
ADXL345Block adxl345;
LTimer timer0(LTIMER_0);
//LTimer timer1(LTIMER_1);
void getdata(void *usr_data)
{
  /*if(analogRead(A0)>5)
  {
    Pressure_data+=(float)analogRead(A0);
    v+=sqrt(pow(adxl345.getX(),2)+pow(adxl345.getY(),2)+pow(adxl345.getZ(),2))*t*9.8;
  }*/
  Acc=sqrt(pow(adxl345.getX(),2)+pow(adxl345.getY(),2)+pow(adxl345.getZ(),2));
}

/*void transform(void *usr_data)
{
  F=0.0245*Pressure_data+0.1;
  P=F*v;
  calories=0.24*P;
  Serial.println(calories);
  Serial.println(F);
  F=F+1;
}*/
void setup()
{
  Serial.begin(9600);

  mcs.addChannel(Pressure);
  mcs.addChannel(Acceleration);
  mcs.addChannel(Calorie);
 // mcs.addChannel(xx);
 // mcs.addChannel(yy);
  //mcs.addChannel(zz);
  Serial.println("開始連線");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("WiFi連線成功");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS連線成功");

  adxl345.begin();

  timer0.begin();
  

  timer0.start(10, LTIMER_REPEAT_MODE,getdata,NULL);
 
  
}


void loop()
{
 while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS Reconnected."); }
  }
  mcs.process(100);

/*  Calorie.set(calories);
  Serial.println(calories);*/

  if (analogRead(A0)> 5) {
    float data=(float) analogRead(A0);
    P+=data;
    temp_Acc+=Acc;
     Pressure.set(data);
    }
 
  else{
    Force=0.0245*P+0.1;
    v=temp_Acc*t*9.8;
    P=Force*v;
    Calorie.set(P);
    Serial.print(P);}
}




