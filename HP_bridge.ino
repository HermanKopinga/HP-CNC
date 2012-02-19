const byte rA = 2; // One quadrature pin
const byte rB = A1; // the other quadrature pin
const byte lA = 3;
const byte lB = A2;
const byte rMotor1 = 7;    // H-bridge leg 1 (pin 2, 1A)
const byte rMotor2 = 8;    // H-bridge leg 2 (pin 7, 2A)
const byte rMotorEn = 5; 
const byte lMotor1 = A4;
const byte lMotor2 = A5;
const byte lMotorEn = 6;

volatile int Rotor = 0;
volatile int Linear = 0;
int ticks = 0;

void setup() 
{
  // set DIO pins
  pinMode(rA, INPUT);
  pinMode(rB, INPUT);
  pinMode(lA, INPUT);
  pinMode(lB, INPUT);

  // Attach interrupt to pin A
  attachInterrupt(0, UpdateRotation, FALLING);
  attachInterrupt(1, UpdateLinear, FALLING);
  
  // Use serial port to keep user informed of rotation
  Serial.begin(115200);
}

void loop() 
{
  ticks++;
  if (ticks == 500)
  {
    Serial.print(Rotor, DEC);
    Serial.print(" ");
    Serial.println(Linear, DEC);
    ticks = 0;
  }

  digitalWrite(rMotor1, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(rMotor2, HIGH);  // set leg 2 of the H-bridge high
  
  digitalWrite(lMotor1, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(lMotor2, HIGH);  // set leg 2 of the H-bridge high
  
  digitalWrite(rMotorEn, HIGH);
  analogWrite(lMotorEn, 50);

}

void UpdateRotation() 
{
  // This is the subroutine that runs every time pin 2
  // switches from high to low.

  if (digitalRead(rB)) 
  {
    Rotor++;
  } 
  else 
  {
    Rotor--;
  }
}


void UpdateLinear() 
{
  // This is the subroutine that runs every time pin 2
  // switches from high to low.

  if (digitalRead(lB)) 
  {
    Linear++;
  } 
  else 
  {
    Linear--;
  }
}


