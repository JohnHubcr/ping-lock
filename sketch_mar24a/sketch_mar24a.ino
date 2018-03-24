#include <ThingSpeak.h>


const int trigPin = 9;
const int echoPin = 10;
unsigned long myChannelNumber = 458658;
//const char *myWriteAPIKey = "IX3YMMI4IUBRA9RY";

String writeAPIKey = "IX3YMMI4IUBRA9RY";
String channelID = "458658";

// TCP socket initialize
//TCPClient client;


const int echoPin2 = 3;
const int trigPin2 = 2;

// defines variables
long duration;
int distance;
int distance2;
int ct = 0;
int usual_distance = 0;
int ok = 1;
int cur = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  //ThingSpeak.begin(client);
}
void loop() {
  digitalWrite(trigPin, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2; // Calculating the distance

  digitalWrite(trigPin2, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance2= duration*0.034/2; // Calculating the distance

  // Count number of iterations to calibrate
  if(ok)ct++;

  // After 200 iterations, define standard distance
  if(ok && ct==2) {ok=0;Serial.print("Ready\n");}
  
  //Serial.print("USUAL DISTANCE: ");
  //Serial.print(usual_distance);
  //Serial.print("\n");
  
  // If distance has reduced
  if( !ok && ((distance/35) == 0 || (distance2/35) == 0) ){
      /*if(distance/50 == 0 && cur == 2){
        Serial.print("Leaving\n");
        cur = 0;
      }
      else if(distance/50 == 0 && cur == 0 )cur=1;
      else if(distance2/50 == 0 && cur == 1){
        Serial.print("Entering\n");
        cur = 2;
      }*/
    
      if(distance/35 == 0){
        int go = 1;
        for(int i=0;i<250;i++){
          if(!go)break;
          digitalWrite(trigPin2, LOW); // Clears the trigPin
          delayMicroseconds(2);
          digitalWrite(trigPin2, HIGH);
          delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
          digitalWrite(trigPin2, LOW);
          duration = pulseIn(echoPin2, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
          distance2= duration*0.034/2; // Calculating the distance
          if(distance2/35 == 0 && go){
            Serial.print("Entering\n");
            int x = 100;
            int y = 0;
            //ThingSpeakUpdate("field1="+String(x)+"&field2="+String(y));
            
            go = 0;
            //delay(15000);
            break;
          }
        }
        //if(!go)delay(16000);  
      }
      else if(distance2/35 == 0){
        int go = 1;
        for(int i=0;i<250;i++){
          if(!go)break;
        digitalWrite(trigPin, LOW); // Clears the trigPin
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
        distance= duration*0.034/2; // Calculating the distance       
        if(distance/35 == 0 && go){
          Serial.print("Leaving\n");
          int x = 50;
          int y = 0;
          //ThingSpeakUpdate("field1="+String(x)+"&field2="+String(y));
          go = 0;
          //delay(15000);
          break;
        }
      }
    //if(!go)delay(16000);
    }
  }
  delay(160);
}


/*
void ThingSpeakUpdate(String tsData)
{
    Serial.println("Date string: " + tsData);
    
    Serial.println("...Connecting to Thingspeak");
    
    // Connecting and sending data to Thingspeak
    if(client.connect("api.thingspeak.com", 80))
    {
        Serial.println("...Connection succesful, updating datastreams");
        
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(tsData.length());
        client.print("\n\n");
        
        client.println(tsData); //the ""ln" is important here.
    
        // This delay is pivitol without it the TCP client will often close before the data is fully sent
        delay(200);
        
        Serial.println("Thingspeak update sent.");
    }
    else{
        // Failed to connect to Thingspeak
        Serial.println("Unable to connect to Thingspeak.");
    }
    
    if(!client.connected()){
        client.stop();
    }
    client.flush();
    client.stop();
}*/
