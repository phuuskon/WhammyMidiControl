/*
 WhammyMidiControl.ino
 Very simple Whammy preset changer
 Copyright (C) 2018 Pekka Huuskonen
 
 This sketch is for changing Digitech Whammy IV guitar effect presets.
 It sends midi program change messages from 0-16 on midi channel 1.
 There's two buttons Up and Down. Up button increases program number by one and sends it.
 Down button decreases program number and sends it. 

 NOTE:
 Whammy manual says that program change numbers 1 through 17 controls presets in effect active.
 I noticed that actually they are from 0 to 16.
 */

#include "OneButton.h"
#include "MIDI.h"

// Setup a new OneButton on pin A1.  
OneButton buttonDown(A1, true);
// Setup a new OneButton on pin A2.  
OneButton buttonUp(A2, true);

// init MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

// set constants
const int midiChannel = 1;
const int highLimitPC = 16;
const int lowLimitPC = 0;

// current program change number
int currentPC;


// setup 
void setup() {
  // link the down button functions.
  buttonDown.attachClick(clickDown);
  
  // link the up button functions.
  buttonUp.attachClick(clickUp);

  // init current program change number
  currentPC = lowLimitPC;

  // start MIDI
  MIDI.begin(midiChannel);

  // send initial midi message
  MIDI.sendProgramChange(currentPC, midiChannel);
  
} // setup


// main code here, to run repeatedly: 
void loop() {
  // keep watching the push buttons:
  buttonDown.tick();
  buttonUp.tick();
} // loop


// ----- button Down callback functions

// Down button click callback
void clickDown() {
  // if current program number is at low limit then rotate to high limit
  if(currentPC == lowLimitPC)
  {
    currentPC = highLimitPC;
  }
  // otherwise decrease current program number
  else if(currentPC > lowLimitPC)
  {
    currentPC = currentPC - 1;
  }
  // send midi message
  MIDI.sendProgramChange(currentPC, midiChannel);
  
} // clickDown

// Up button click callback
void clickUp() {
  // if current program number is at high limit then rotate to low limit
  if(currentPC == highLimitPC)
  {
    currentPC = lowLimitPC;
  }
  // otherwise increase current program number 
  else if(currentPC < highLimitPC)
  {
    currentPC = currentPC + 1;
  }
  // send midi message
  MIDI.sendProgramChange(currentPC, midiChannel);
  
} // clickUp

// End

