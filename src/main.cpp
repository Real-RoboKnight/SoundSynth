/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include "Chord Player.hpp"
#include <Arduino.h>
#include <EasyButton.h>

// Set LED_BUILTIN if it is not defined by the Arduino framework
// #define LED_BUILTIN 13

void setup() {
    Serial.begin(115200);
    Serial.println("Chord Player Test");
    Chord_Player<5> chordPlayer({ 15, 4, 18, 21, 23 });
    Chord_Player<5>::Chord chord{
        { Chord_Player<5>::Chord::Note{ PWMPin::Note::NONE, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::NONE, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::NONE, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::NONE, 5 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::NONE, 5 } },
        1000
    };
    Serial.println("Chord Player Test");

    EasyButton button(0); // GPIO 0
    button.begin();
    button.onPressed([]() {
        Serial.println("Button Pressed!");
        std::terminate();
    });

    while (true) {
        // turn the LED on (HIGH is the voltage level)
        chordPlayer.playChord(chord);
        Serial.println("Played chord");
        delay(1000); // wait for a second
        chordPlayer.stop();
        delay(1000); // wait for a second
    }
}

void loop() {}