/**
 * @file main.cpp
 * @author Dylan Shah (dylan.shah@outlook.com)
 * @brief Use an ESP32 to play music
 * @version 0.1
 * @date 2025-12-10
 *
 * @copyright Copyright Ⓒ 2025
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "Chord Player.hpp"
#include <Arduino.h>
#include <EasyButton.h>

void setup() {
    Serial.begin(115200);
    Serial.println(
        "Copyright (C) 2025  Dylan Shah \n "
        "This program comes with ABSOLUTELY NO WARRANTY; see "
        "LICENSE for details.This is free software, and you are "
        "welcome to redistribute it under certain conditions. Please see the "
        "GNU General Public License 3.0 or later for details.");

    Chord_Player<5> chordPlayer({ 15, 4, 18, 21, 23 });
    Chord_Player<5>::Chord chord{
        { Chord_Player<5>::Chord::Note{ PWMPin::Note::C, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::E, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::G, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::B, 4 },
          Chord_Player<5>::Chord::Note{ PWMPin::Note::C, 5 } },
        1000
    };
    Serial.println("Chord Player Test");

    while (true) {
        // turn the LED on (HIGH is the voltage level)
        chordPlayer.playChord(chord);
        Serial.println("Played chord");
        delay(1000); // wait for a second
        chordPlayer.stop();
        delay(1000); // wait for a second
        if (digitalRead(0) == LOW) {
            Serial.println("Button Pushed, exiting loop.");
            break;
        }
    }
}

void loop() {}