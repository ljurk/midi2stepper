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

bool hitMode = false;
#define MIDI_CHANNEL 1
MIDI_CREATE_DEFAULT_INSTANCE();
const int stepsPerRevolution = 50;  // change this to fit the number of steps per revolution


// initialize the stepper library
Stepper stepper0(stepsPerRevolution, 9, 11, 10, 12);
Stepper stepper1(stepsPerRevolution, 5, 7, 6, 8);

void hit(byte note) {
    switch(note) {
        case 32:
            stepper0.step(-stepsPerRevolution);
            stepper0.step(stepsPerRevolution);
            break;
        case 33:
            stepper1.step(-stepsPerRevolution);
            stepper1.step(stepsPerRevolution);
            break;
        default:
            break;
    }
}

void handleNoteOff(byte channel, byte note, byte velocity){
    if(!hitMode) {
        switch(note) {
            case 32:
                //hit(note)
                stepper0.step(stepsPerRevolution);
                break;
            case 33:
                //hit(note);
                stepper1.step(stepsPerRevolution);
                break;
            default:
                break;
        }
    }
}
void handleNoteOn(byte channel, byte note, byte velocity){
    switch(note) {
        case 0:
            stepper0.step(stepsPerRevolution / 5);
            break;
        case 1:
            stepper0.step(-stepsPerRevolution / 5);
            break;
        case 2:
            stepper1.step(stepsPerRevolution / 5);
            break;
        case 3:
            stepper1.step(-stepsPerRevolution / 5);
            break;
        case 4:
            hitMode = !hitMode;
            break;
        case 32:
            if(hitMode) {
                hit(note);
            } else {
                stepper0.step(-stepsPerRevolution);
            }
            break;
        case 33:
            if(hitMode){
                hit(note);
            } else {
                stepper1.step(-stepsPerRevolution);
            }
            break;
        default:
            break;
    }
}
void setup() {
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.begin(MIDI_CHANNEL);
    // set the speed at 60 rpm:
    stepper0.setSpeed(300);
    stepper1.setSpeed(300);
    // initialize the serial port:
}

void loop() {
    MIDI.read(MIDI_CHANNEL);
}
