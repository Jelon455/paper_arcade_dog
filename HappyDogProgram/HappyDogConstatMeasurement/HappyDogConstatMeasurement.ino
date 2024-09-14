//DEFINE FOR MOTORS
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
bool measuringActive = false;

//DEFINE FOR LED
int LEDPin = 7;

void setup() 
{
//PINS FOR DISTANCE SENSOR
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
//Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
//Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
//Calculating the distance
  distance = duration * 0.034 / 2;
  delay(10);	
}

void stopMovement()
{
  analogWrite(speedEars, 0);
  analogWrite(speedTail, 0);

  digitalWrite(dogEarsPin1, LOW);
  digitalWrite(dogEarsPin2, LOW);
  digitalWrite(dogTailPin1, LOW);
  digitalWrite(dogTailPin2, LOW);
}

void earsAndTailMovement(int swing)
{
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
    delay(600);
  //Tail rotate in diffrent direction
    digitalWrite(dogTailPin1, LOW);
    digitalWrite(dogTailPin2, HIGH); 
  //Ears rotate in diffrent direction
    digitalWrite(dogEarsPin1, LOW);
    digitalWrite(dogEarsPin2, HIGH);    
    delay(600);
  }
  stopMovement();
}

void earsMovement(int swing)
{
  analogWrite(speedEars, 255);
  for(int i = 0; i < swing; i++)
  {
  //Ears rotate in one direction    
    digitalWrite(dogEarsPin1, HIGH);
    digitalWrite(dogEarsPin2, LOW);
    delay(600);
  //Ears rotate in diffrent direction
    digitalWrite(dogEarsPin1, LOW);
    digitalWrite(dogEarsPin2, HIGH);    
    delay(600);
  }
  stopMovement();
}

void checkDistanceAndReact()
{
  distanceMeasurement();

//FIRST CASE - ball is close to the dog, only ears move
  if (distance >= 9 && distance <= 30)
  {
    earsMovement(1);
  }
//SECOND CASE - ball is very close to the dog, ears and tail move
  else if (distance >= 0 && distance < 9)
  {
    earsAndTailMovement(2);
  }
//THIRD CASE - ball is too far, stop movement
  else if (distance > 40)
  {
    stopMovement();
  }
}

void loop() 
{
  buttonState = digitalRead(buttonPin);

//Check if the button was pressed
  if (buttonState != lastButtonState)
  {
  //Button pressed  
    if (buttonState == LOW)
    {
    //Toggle the measuring state
      measuringActive = !measuringActive; 

      if (measuringActive)
      {
        Serial.println("Measurement activated!");
      //Turn on LED to indicate active measurement  
        digitalWrite(LEDPin, HIGH); 
      }
      else
      {
        Serial.println("Measurement deactivated!");
      //Turn off LED to indicate inactive measurement  
        digitalWrite(LEDPin, LOW); 
        stopMovement(); 
      }
    }
    //Debounce
    delay(200); 
  }
  lastButtonState = buttonState;

//If measuring is active, continuously check the distance
  if (measuringActive)
  {
    checkDistanceAndReact();
  }
  else
  {
  //Ensure no movement when measuring is off  
    stopMovement(); 
  }
}
