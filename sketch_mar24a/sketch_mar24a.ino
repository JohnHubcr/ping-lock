const int trigPin = 9;
const int echoPin = 10;

const int echoPin2 = 3;
const int trigPin2 = 2;

// variables
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
}
void loop() {
  digitalWrite(trigPin, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration*0.034/2; // Calculating the distance

  digitalWrite(trigPin2, LOW); // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance2= duration*0.034/2; // Calculating the distance

  // Count number of iterations to calibrate
  if(ok)ct++;
  if(ok && ct==20) {ok=0;Serial.print("Ready\n");}
  
  // If distance has reduced
  if( !ok && ((distance/35) == 0 || (distance2/35) == 0) ){
      if(distance/35 == 0){
        for(int i=0;i<250;i++){
          digitalWrite(trigPin2, LOW); // Clears the trigPin
          delayMicroseconds(2);
          digitalWrite(trigPin2, HIGH);
          delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
          digitalWrite(trigPin2, LOW);
          duration = pulseIn(echoPin2, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
          distance2= duration*0.034/2; // Calculating the distance
          if(distance2/35 == 0){
            Serial.print("Entering\n");
            break;
          }
        }
      }
      else if(distance2/35 == 0){   
        for(int i=0;i<250;i++){
        digitalWrite(trigPin, LOW); // Clears the trigPin
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
        distance= duration*0.034/2; // Calculating the distance       
        if(distance/35 == 0){
          Serial.print("Leaving\n");
          break;
        }
      }
    }
  }
  delay(150);
}
