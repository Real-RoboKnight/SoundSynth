/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include "Chord Player.hpp"
#include <Arduino.h>

// Set LED_BUILTIN if it is not defined by the Arduino framework
// #define LED_BUILTIN 13

void setup() {
    Chord_Player<5> chordPlayer({ 15, 4, 18, 21, 23 });
    Chord_Player<5>::Chord chord{
        { Chord_Player<5>::Chord::Note{ PWMPin::Note::C, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::E, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::G, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::C, 5 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::E, 5 } },
        1000
    };

    while (true) {
        // turn the LED on (HIGH is the voltage level)
        chordPlayer.playChord(chord);
        delay(1000); // wait for a second
        chordPlayer.stop();
        delay(1000); // wait for a second
    }
}

void loop() {}