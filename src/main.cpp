/* pinout
 * IN1 - D9
 * IN2 - D10
 * IN3 - D11
 * IN4 - D12
 *
 * use MIDI Note 0 and 1 for adjusting 0 position
 */
#include <MIDI.h>
#include <Arduino.h>
#include <Stepper.h>

#define MIDI_CHANNEL 1
MIDI_CREATE_DEFAULT_INSTANCE();
const int stepsPerRevolution = 50;  // change this to fit the number of steps per revolution

// initialize the stepper library 
Stepper stepper0(stepsPerRevolution, 9, 11, 10, 12);

void handleNoteOn(byte channel, byte note, byte velocity){
    if(note == 0){
        stepper0.step(stepsPerRevolution / 5);
    } else if(note == 1){
        stepper0.step(-stepsPerRevolution / 5);
    }else{
        // step one revolution  in one direction:
        stepper0.step(-stepsPerRevolution);
        // step one revolution in the other direction:
        stepper0.step(stepsPerRevolution);
    }
}
void setup() {
    pinMode(buttonPin, INPUT);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.begin(MIDI_CHANNEL);
    // set the speed at 60 rpm:
    stepper0.setSpeed(320);
    // initialize the serial port:
}

void loop() {
    MIDI.read(MIDI_CHANNEL);
}
