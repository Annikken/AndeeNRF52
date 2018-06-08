/************************************************************
  [ Andee ]
  ================
  Lesson 05
  Creating Your Time Input Button 

  Contact us at andee@annikken.com if there are 
  bugs in this sketch or if you need help with the 
  Annikken Andee
************************************************************/ 


// Always include these libraries. Annikken Andee needs them
// to work with the Arduino!
#include <bluefruit.h>
#include <AndeeNRF52.h>

// Every object that appears on your smartphone's screen
// needs to be declared like this:
AndeeHelper objectA;
AndeeHelper objectB;
int H, M, S;
char text[64];

// We're creating two objects

// The setup() function is meant to tell Arduino what to do
// only when it starts up.
void setup()
{
  Andee.begin();//Setup the board to start broadcasting as an Annikken Andee peripheral 
  Andee.clear();  // Clear the screen of any previous displays
  setInitialData();  // Define object types and their appearance
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData()
{
  memset(text, 0x00, 32);
  objectA.setId(0);  // Each object must have a unique ID number
  objectA.setType(DATA_OUT);  // This defines your object as a display box
  objectA.setCoord(0, 10, 100  , 20);
  /* setCoord (x-coord, y-coord, width, height)
     x-coord: From 0.0 (left-most) to 100.0 (right-most)
     y-coord: From 0.0 (top-most)  to 100.0 (bottom-most)
     width:   10.0 (10% of screen width) to 100.0 (100% of screen width)
     height:  10.0 (10% of screen height) to 100.0 (100% of screen height)
  */

  objectA.setTitle("Time Entered");
  objectA.setData(text);
  objectA.setUnit(" ");
  objectA.setTitleTextColor("FFFFFFFF");
  objectA.setTitleColor("50FFFFFF");
  objectA.setTextColor("FFFFFFFF");
  objectA.setColor("FFFF8000");

  //// Let's draw the Button
  objectB.setId(1);  // Each object must have a unique ID number
  objectB.setType(TIME_IN);  // This defines your object as a Time Input Button
  objectB.setCoord(35, 50, 30, 20);
  objectB.setTitle("Enter the Time");
  objectB.setColor(RED);

}

// Arduino will run instructions here repeatedly until you power it off.
void loop()
{
  Andee.poll();//required in every Andee sketch
  if (Andee.isConnected()  == true) {
    objectA.update(); // Call update() to refresh the display on your screen
    objectB.update(); // If you forgot to call update(), your object won't appear
    
    if (objectB.isPressed()) {
      objectB.ack();
      objectB.getTimeInput (&H, &M, &S);
      sprintf(text, "%i : %i : %i", H, M, S);
      objectA.setData(text);
    }
  }
  delay(100);//delay is needed or else board will be crash
}



