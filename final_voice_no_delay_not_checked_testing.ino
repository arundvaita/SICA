//   final+voice+no delay                                                                        <<< no caliberation done>> nee marakanda
//      ellla hardware vach nokitilya  ,so test properly with different cases of clashhhhh
int ms = A0; //ms=moisture sensor value
int msv =100;  
int msll = 1200; //msll=moisture sensor limit low                                                   << calibte 
int mslm = 600;    //                                                                                << calibte  
int mslh = 300;     //                                                                                 << calibte 
unsigned long endtime = 0;
String voice;
int m1 = 3; // pump1                                                                              << appil mso0 varanath check cheyy
int m2 = 5; //pump2
int l1 = 9; //laser
int l3 = 11; // just a light
int l2 = 10; // power indication
int ldr = A1; // ldr pin
int senv = 0; // ldr value
unsigned long time;
#include <dht.h>
dht DHT;
#define DHT11_PIN 7  // humidity sensor
int buz = 6;
int k = 3000;      //                                                                                << calibte 
void setup()
{

  Serial.begin(9600);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(ms, INPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(buz, OUTPUT);
  digitalWrite(l2, HIGH);    // power
  digitalWrite(l1, HIGH);  // laser
  digitalWrite(buz, HIGH); // to sound when it starts
  delay(3000);
  digitalWrite(buz, LOW);
  digitalWrite(m1, LOW); // to pump water for 3min
  delay(1800);                                         //                            333333################(180000)
  digitalWrite(m1, HIGH);
  delay(1000);
}

void vos()
{

  while (Serial.available())
  {
    delay(10);                       //Delay for get calmmmmm
    char c = Serial.read();
    if (c == '#')
    {
      break;
    }
    voice = voice + c;
  }
  if (voice.length() > 0)
  {
    Serial.println(voice);
    if (voice == "light on")
    {
      digitalWrite(l3, HIGH);
    }
    else if (voice == "light off")
    {
      digitalWrite(l3, LOW);
    }
    else if (voice == "pump on")
    {
      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 30;      //                             off automaticali if there is no off instructin(not only that)
    }
    else if (voice == "pump off")
    {
      digitalWrite(m1, HIGH);
    }
    else if (voice == "pump on for one minut")
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 1;

    }
   else if (voice == "pump on for two minut")
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 2;

    }
    else if (voice == "pump on for three minut")
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 3;

    }
    else if (voice == "pump on for four minut")
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 4;

    }
     else if (voice == "pump valam")  //                english ready akuka
    {

      digitalWrite(m2, LOW);   // npk                              

    }
    else if (voice == "stop valam")     //                    english redy akuka
    {
      digitalWrite(m2, HIGH);    //  npk                       
    }
   voice = "";
  }
}


void loop()
{

  int t = endtime - (millis() / 60000);   //     pakaram time ennu koduthalum mathi
  if (t <= 0)
  {
    digitalWrite(m1, HIGH);
    Serial.println("ms0");
  }
  Serial.println("tmn");  // app
  time = millis() / 60000;
  Serial.println(time);


  if (k == 0)                         //    no need but for test thazheyulla ellam work avum so everytime probably ms2 occur ,done this to avoid it
  {
    int msv = analogRead(ms);
    if (msv > msll)
    {
      Serial.println("ms1");   //  app
      digitalWrite(m1, LOW); // to pump water for 3min
      endtime = (millis() / 60000) + 3;
      int msv = analogRead(ms);

    }
    else if (msv > mslm)
    {
      Serial.println("ms2");   //  app
      digitalWrite(m1, LOW); // to pump water for 2min
      endtime = (millis() / 60000) + 2;
      int msv = analogRead(ms);
    }
    else if (msv > mslh)

    {
      Serial.println("ms3");   //    app
      digitalWrite(m1, LOW); // to pump water for 1min
      endtime = (millis() / 60000) + 1;
      int msv = analogRead(ms);
    }
    k = 3000;    //                                    << caliberate
  }
  else
  {
    k--;
  }

 
  senv = analogRead(ldr);
  if (senv > 1000)      //                                          << calibte 
  {
    Serial.println("tdd"); // app

    int x = 0;
    do
    {

      digitalWrite(buz, HIGH);
      delay(500);
      digitalWrite(buz, LOW);
      delay(500);
      x++;

    }
    while (x < 25);
  }

  int chk = DHT.read11(DHT11_PIN);    // humidity temp variable
  Serial.println("tmp");               //  app
  Serial.println((int)DHT.temperature);
  Serial.println("hmt");           //  app
  Serial.println((int)DHT.humidity);

  if (Serial.available() > 0)
  {
    char in = Serial.read();
    if(in == '*')
    {
      vos();
      
    }
    if (in == 49)
    {
      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 1;
    }

    else if (in == 50)
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 2;

    }
    else if (in == 51)
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 3;
    }
    else if (in == 52)
    {

      digitalWrite(m1, LOW);
      endtime = (millis() / 60000) + 4;
    }

    else if (in == 53)
    {

      digitalWrite(l3, HIGH);   // just led

    }
    else if (in == 54)
    {
      digitalWrite(l3, LOW);    //  just  led
    }
      else if (in == 55)
    {

      digitalWrite(m2, LOW);   // npk                                         << appil include cheyy

    }
    else if (in == 56)
    {
      digitalWrite(m2, HIGH);    //  npk                                      << appil include
    }


  }
  delay(250);    //   <DO NOT CHANGE>    ie: calibereted to app
}


