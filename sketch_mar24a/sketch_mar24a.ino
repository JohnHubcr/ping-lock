#include <ThingSpeak.h>

const int trigPin = 9;
const int echoPin = 10;
//unsigned long myChannelNumber = 458658;
//const char *myWriteAPIKey = "XXXXXXXXXXXXXY";
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
  
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");

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
            break;
            go = 0;
          }
        }
      //  if(!go)delay(16000);  
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
          go = 0;
          break;
        }
      }
    //if(!go)delay(16000);
    }
  }
  delay(160);
}
