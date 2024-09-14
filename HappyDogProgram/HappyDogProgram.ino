//DEFINE FOR MOTORS
//Double check please!
int dogTailPin1 = 4;
int dogTailPin2 = 5;

int dogEarsPin1 = 2;
int dogEarsPin2 = 3;

const int speedEars = 10;
const int speedTail = 9;

//DEFINE FOR DISTANCE SENSOR
const int trigPin = 11;
const int echoPin = 12;

long duration;
int distance;

//DEFINE FOR BUTTON
int buttonPin = 8;
int buttonPressed = 0;

int buttonState = 1;
int lastButtonState = 1;

//DEFINE FOR LED
int LEDPin = 7;

void setup() 
{
  //PINS FOR DISTANCE SENROS
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  //PINS FOR MOTORS
  pinMode(dogTailPin1, OUTPUT);
  pinMode(dogTailPin2, OUTPUT);
  pinMode(dogEarsPin1, OUTPUT);
  pinMode(dogEarsPin2, OUTPUT);

  pinMode(speedEars, OUTPUT); 
  pinMode(speedTail, OUTPUT);

  //PINS FOR BUTTON
  pinMode(buttonPin, INPUT);

  //PINS FOR LED
  pinMode(LEDPin, OUTPUT);
}

void distanceMeasurement()
{
//Clears the trigPin
  Serial.println("Measuring distance...");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
//Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
//Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
//Calculating the distance
  distance = duration * 0.034 / 2;

  Serial.println("Measured distance is: ");
  Serial.println(distance);
  
  delay(10);	
}

void stopMovement()
{
  analogWrite(speedEars, 0); //ENA   pin
  analogWrite(speedTail, 0); //ENB pin

  digitalWrite(dogEarsPin1, LOW);
  digitalWrite(dogEarsPin2, LOW);
  digitalWrite(dogTailPin1, LOW);
  digitalWrite(dogTailPin2, LOW);
}
void earsAndTailMovement(int swing)
{
  Serial.println("Moving ears and tail!");
//Setting a speed for the motors 0-min 255-max
  analogWrite(speedEars, 255);
  analogWrite(speedTail, 255);
  for(int i = 0; i < swing; i++)
  {
  //Ears rotate in one direction    
    digitalWrite(dogEarsPin1, HIGH);
    digitalWrite(dogEarsPin2, LOW);
  //Tail rotate in one direction
    digitalWrite(dogTailPin1, HIGH);
    digitalWrite(dogTailPin2, LOW);
  //***TO DO***
    delay(1000);
  //Tail rotate in diffrent direction
    digitalWrite(dogTailPin1, LOW);
    digitalWrite(dogTailPin2, HIGH); 
  //Ears rotate in diffrent direction
    digitalWrite(dogEarsPin1, LOW);
    digitalWrite(dogEarsPin2, HIGH);    
  //***TO DO***
    delay(1000);
  }
  Serial.println("End of ears and tail's movement");
  stopMovement();
}

void earsMovement(int swing)
{
  Serial.println("Moving ears!");
//Setting a speed for the motors 0-min 255-max
  analogWrite(speedEars, 255);
  for(int i = 0; i < swing; i++)
  {
  //Ears rotate in one direction    
    digitalWrite(dogEarsPin1, HIGH);
    digitalWrite(dogEarsPin2, LOW);
  //***TO DO***
    delay(1500);
  //Ears rotate in diffrent direction
    digitalWrite(dogEarsPin1, LOW);
    digitalWrite(dogEarsPin2, HIGH);    
  //***TO DO***
    delay(1500);
  }
  Serial.println("End of ears's movement");
  stopMovement();
}
//MAIN CODE
void loop() 
{
  stopMovement();

  buttonState = digitalRead(buttonPin);
//Delay for bouncing button
  delay(300);
//Checking if there was an edge on button
  if (buttonState != HIGH)
  {
      digitalWrite(LEDPin, HIGH);
      Serial.println("Button is pressed, start the program!");
      Serial.println("Waiting for the ball...");
    //Time to press the button and take ball to the sensor
      delay(3500);
      distanceMeasurement();
      digitalWrite(LEDPin, LOW);
    //FIRST CASE - ball is close to the dog so the tail is rotating ears are not
      if (distance >= 5 && distance <= 50)
      {
        earsMovement(4);
      }
    //SECOND CASE - ball is very close to the dog so the tail is rotating ears are rotating
      //***TO DO***
      else if (distance >= 0 && distance < 5)
      {
        Serial.println("Measure distance is the closest one!");
        earsAndTailMovement(3);
      }
    //THIRD CASE no ball so ears and tail are not moving
      else
      {
        stopMovement();
      }
    }
    else
    {
      delay(10);
    }
}