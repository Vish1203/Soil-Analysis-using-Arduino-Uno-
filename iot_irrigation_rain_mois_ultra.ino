#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
#include <SoftwareSerial.h>
// replace with your channel's thingspeak API key
String apiKey = "34QPS1VTMDHJ88FL";
SoftwareSerial ser(5, 6); // RX, TX
int sensepin = A2;
int sensepin1 = A1;
char buf1[16];
char buf2[16];
char buf3[16];
char buf4[16];
char buf5[16];
char buf6[16];
String stri, strj, strk;
String stri1, strj1, strm;
int i,j;
int mois;
const int trigPin = 2;
const int echoPin = 3;


void setup()
{
// Initialize the IO and ISR
// enable software serial
Serial.begin(9600);
  ser.begin(115200);
  // reset ESP8266
  ser.println("AT+RST");
   delay(500);
  ser.println("AT+CWMODE=3");
   delay(500);
 
  ser.println("AT+CWJAP=\"akash\",\"akash1995\"");
  delay(500);
 pinMode(4, OUTPUT);        //motor
      digitalWrite(4, HIGH);
   pinMode(A5, OUTPUT);        //motor
      digitalWrite(A5, HIGH);
       analogReference(DEFAULT);
       lcd.begin(16,2);
        lcd.setCursor(0,0);
 lcd.print("SLIET,Punjab");
 lcd.setCursor(0,1);
 lcd.print("");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Made by:-");
 lcd.setCursor(0,1);
 lcd.print("Akash,Piyush");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Rahul & Sunil");
 lcd.setCursor(0,1);
 lcd.print(" ");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Supervisor:Dr.");
 lcd.setCursor(0,1);
 lcd.print("Charanjiv Gupta");
 delay(2000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Solar IOT ");
 lcd.setCursor(0,1);
 lcd.print("Irrigation ");
 delay(1000);
 lcd.clear();
 
}
void loop()
{
  long duration, inches, cm;
  i = analogRead(A1);
  j = analogRead(A2);
  Serial.print(i);
   Serial.print(" ");
   Serial.println(j);
   
       lcd.setCursor(0, 1);
    lcd.print("Mois: ");
 lcd.print(analogRead(A2));
  lcd.print("   ");
   // and the distance result in inches and centimeters:
 
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
    lcd.setCursor(0, 0);
      lcd.print("Distance: ");
    lcd.print(cm);
    lcd.print(" CM ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");
 
    if(analogRead(sensepin1)<500)    //rain
      {
          digitalWrite(4, HIGH); 
         //   lcd.setCursor(0,1);
    //  lcd.print("Motor Off       "); 
      }
        if(analogRead(sensepin1)>500)      //no rain
      {
          if(analogRead(sensepin)>500)    //no mois
          { 
      
      //   lcd.setCursor(0,1);
   //   lcd.print("Motor On "); 
        digitalWrite(4, LOW);
      
          }
          else if(analogRead(sensepin)<500)   //mois
          {
            digitalWrite(4, HIGH);
      //     lcd.setCursor(0,1);
     // lcd.print("Motor Off       "); 
          }    
      }
      
stri = dtostrf(i, 4, 1, buf1);
strk = dtostrf(cm, 3, 1, buf3);

strj = dtostrf(j, 4, 1, buf2);
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(stri);
  getStr += "\r\n\r\n";



  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

   

  if(ser.find(">")){
    ser.print(getStr);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  // thingspeak needs 15 sec delay between updates
  
  delay(6000);
   i = analogRead(A1);
  j = analogRead(A2);
  Serial.print(i);
   Serial.print(" ");
   Serial.println(j);
   
       lcd.setCursor(0, 1);
    lcd.print("Mois: ");
 lcd.print(analogRead(A2));
  lcd.print("   ");
   // and the distance result in inches and centimeters:
 
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
    lcd.setCursor(0, 0);
      lcd.print("Distance: ");
    lcd.print(cm);
    lcd.print(" CM ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");
 
    if(analogRead(sensepin1)<500)    //rain
      {
          digitalWrite(4, HIGH); 
         //   lcd.setCursor(0,1);
    //  lcd.print("Motor Off       "); 
      }
        if(analogRead(sensepin1)>500)      //no rain
      {
          if(analogRead(sensepin)>500)    //no mois
          { 
      
      //   lcd.setCursor(0,1);
   //   lcd.print("Motor On "); 
        digitalWrite(4, LOW);
      
          }
          else if(analogRead(sensepin)<500)   //mois
          {
            digitalWrite(4, HIGH);
      //     lcd.setCursor(0,1);
     // lcd.print("Motor Off       "); 
          }    
      }
      
stri = dtostrf(i, 4, 1, buf1);
strk = dtostrf(cm, 3, 1, buf3);

strj = dtostrf(j, 4, 1, buf2);
  // TCP connection
  String cmd1 = "AT+CIPSTART=\"TCP\",\"";
  cmd1 += "184.106.153.149"; // api.thingspeak.com
  cmd1 += "\",80";
  ser.println(cmd1);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr1 = "GET /update?api_key=";
  getStr1 += apiKey;
  getStr1 +="&field2=";
  getStr1 += String(strj);
  getStr1 += "\r\n\r\n";



  // send data length
  cmd1 = "AT+CIPSEND=";
  cmd1 += String(getStr1.length());
  ser.println(cmd1);
  if(ser.find(">")){
    ser.print(getStr1);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  // thingspeak needs 15 sec delay between updates
  delay(6000);
    i = analogRead(A1);
  j = analogRead(A2);
  Serial.print(i);
   Serial.print(" ");
   Serial.println(j);
   
       lcd.setCursor(0, 1);
    lcd.print("Mois: ");
 lcd.print(analogRead(A2));
  lcd.print("   ");
   // and the distance result in inches and centimeters:
 
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
    lcd.setCursor(0, 0);
      lcd.print("Distance: ");
    lcd.print(cm);
    lcd.print(" CM ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm, ");
 
    if(analogRead(sensepin1)<500)    //rain
      {
          digitalWrite(4, HIGH); 
         //   lcd.setCursor(0,1);
    //  lcd.print("Motor Off       "); 
      }
        if(analogRead(sensepin1)>500)      //no rain
      {
          if(analogRead(sensepin)>500)    //no mois
          { 
      
      //   lcd.setCursor(0,1);
   //   lcd.print("Motor On "); 
        digitalWrite(4, LOW);
      
          }
          else if(analogRead(sensepin)<500)   //mois
          {
            digitalWrite(4, HIGH);
      //     lcd.setCursor(0,1);
     // lcd.print("Motor Off       "); 
          }    
      }
      
stri = dtostrf(i, 4, 1, buf1);
strk = dtostrf(cm, 3, 1, buf3);

strj = dtostrf(j, 4, 1, buf2);
  // TCP connection
  String cmd2 = "AT+CIPSTART=\"TCP\",\"";
  cmd2 += "184.106.153.149"; // api.thingspeak.com
  cmd2 += "\",80";
  ser.println(cmd2);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  // prepare GET string
  String getStr2 = "GET /update?api_key=";
  getStr2 += apiKey;
  getStr2 +="&field3=";
  getStr2 += String(strk);
  getStr2 += "\r\n\r\n";



  // send data length
  cmd2 = "AT+CIPSEND=";
  cmd2 += String(getStr2.length());
  ser.println(cmd2);

   

  if(ser.find(">")){
    ser.print(getStr2);
  }
   else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  // thingspeak needs 15 sec delay between updates
  
  delay(6000);

 
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
