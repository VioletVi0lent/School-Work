//GEN_RUSH
//Made by Maximilian Throgmorton
//Licenses go to the respective libaries used in this code.
//Believe it or not, 90% of this code is handmade.
//The 10% goes to my other code files for reminding me how statements work.

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_5s;

int Difficulty = 5; //The B button is the difficulty selector.
int Interact = 4; //The A button is the main tool for the game.

int IniZone = 0;
int MinusZone = 0;
int PlusZone = 0;

volatile bool SkillCheck = false;
volatile bool SpeedUp = false;

bool AVal = 0;
int BVal = 0;
bool GameTimeVal = 0;
bool Victory = 0;
int Charge = 0;
int i = 10;
int Speed = 200;
int Goal = 1000;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  delay_5s.start(5000, AsyncDelay::MILLIS);
  randomSeed(analogRead(0));

  pinMode(Difficulty,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Difficulty), Changer, RISING);

  pinMode(Interact, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Interact), DidItWork, FALLING);

}

void loop() {
  if(Charge < Goal){ //If the goal is yet to be reached, the game will continue.

  if(SpeedUp == true)
  {
    BVal++;
    if(BVal > 1)
    {
      BVal = 0;
    }
    SpeedUp = false;
    Serial.println(BVal);
  }

  switch(BVal) //This selects the difficulty, changing the speed of the game and the goal.
  {
    case 0:
      Speed = 200;
      Goal = 1000;
      break;
    case 1:
      Speed = 100;
      Goal = 1500;
      break;
    default: //Is this how it works? I just needed something to fill that second input slot.
      break;
  }

  if(GameTimeVal == false)
  {
    if(delay_5s.isExpired()) //The bread and butter of this code.
    {
      CircuitPlayground.playTone(1480.0 , 300);
      StartEngine(); // This presets the LEDs that the zones will take place.
      if(BVal == 1)
      {
        CircuitPlayground.setPixelColor(IniZone, 128, 0, 0);
        CircuitPlayground.setPixelColor(MinusZone, 128, 0, 0);
        CircuitPlayground.setPixelColor(PlusZone, 128, 0, 0);
      }
      else
      {
        CircuitPlayground.setPixelColor(IniZone, 0, 128, 0);
        CircuitPlayground.setPixelColor(MinusZone, 0, 128, 0);
        CircuitPlayground.setPixelColor(PlusZone, 0, 128, 0);
      }
      GameTimeVal = true;
      delay_5s.repeat();
    }
    if(Charge < 0) // This prevents Underflow.
    {
      Charge = 0;
    }
    if(Charge > Goal) // This prevents Overflow.
    {
      Charge = Goal;
    }
  }
  while(GameTimeVal == true) //This prevents the game from playing over itself
  {
    if(SkillCheck == true) //Checks if the A button was pressed at the right time
   {
     if(i == IniZone) //Middle Zone
     {
       CircuitPlayground.playTone(440.00, 200);
       Charge += 100;
       for(int l = 0; l < 10; l++)
       {
         CircuitPlayground.setPixelColor(l, 0, 255, 0);
       }
       delay(100);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
       Serial.println(Charge);
     }
     else if(i == MinusZone) //Back Zone
     {
       CircuitPlayground.playTone(440.00, 200);
       Charge += 100;
       for(int l = 0; l < 10; l++)
       {
         CircuitPlayground.setPixelColor(l, 0, 255, 0);
       }
       delay(100);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
       Serial.println(Charge);
     }
     else if(i == PlusZone) //Front Zone
     {
       CircuitPlayground.playTone(440.00, 200);
       Charge += 100;
       for(int l = 0; l < 10; l++)
       {
         CircuitPlayground.setPixelColor(l, 0, 255, 0);
       }
       delay(100);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
       Serial.println(Charge);
     }
     else //Fail
     {
       CircuitPlayground.playTone(92.499, 200);
       Charge -= 300;
       for(int j = 0; j < 10; j++)
       {
         CircuitPlayground.setPixelColor(j, 255, 0, 0);
       }
       delay(50);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
       Serial.println(Charge);
     }
     SkillCheck = false;
   } //This concludes the A button code
    CircuitPlayground.setPixelColor(i, 0, 0, 255);
    delay(Speed);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    i--;
    if (i < 0 && GameTimeVal == true) //This checks if you missed the zones entirely
    {
      CircuitPlayground.playTone(92.499, 200);
      Charge -= 300;
      for(int j = 0; j < 10; j++)
      {
        CircuitPlayground.setPixelColor(j, 255, 0, 0);
      }
      delay(50);
      CircuitPlayground.clearPixels();
      GameTimeVal = false;
      Serial.println(Charge);
    } //There's a strange bug where it counts a miss if you hit a dot on the very edge of the board. My way of fixing this is literally getting better at the game.
    else if(GameTimeVal == false)
    {
      break;
    }
  }
}
else //This is what happens when you reach your goal.
{
  for(int g = 0; g < 10; g++)
  {
    CircuitPlayground.setPixelColor(g, 255, 255, 255);
  }
  if(Victory == false)
  {
    CircuitPlayground.playTone(587.33, 500);
    Victory = true; //This prevents it from playing more than once.
  }
}
}

void DidItWork()
{
  SkillCheck = true;
}

void Changer()
{
  SpeedUp = 1;
}

void StartEngine()
{
  IniZone = random(1, 4);
  MinusZone = IniZone - 1;
  PlusZone = IniZone + 1; //So far, this works. Not sure how, but it does.
  i = 10; //This is to reset your position after every round.
}