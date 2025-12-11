#pragma once

/**
 * @file Chord Player.hpp
 * @author Dylan Shah (dylan.shah@outlook.com)
 * @brief
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

#include "PWMPin.hpp"

template<size_t NumberOfNotes>
class Chord_Player {
    std::array<PWMPin, NumberOfNotes> buzzers;

    friend std::ostream& operator<<(std::ostream& os,
                                    const Chord_Player<NumberOfNotes>& player) {
        os << "Chord_Player(NumberOfNotes=" << NumberOfNotes << "){\n";
        for (size_t i = 0; i < NumberOfNotes; ++i) {
            os << "  Buzzer " << i << ": " << player.buzzers[i] << "\n";
        }
        os << "}";
        return os;
    }

  public:
    struct Chord {
        struct Note {
            PWMPin::Note Note;
            uint8_t Octave;
        };

        std::array<Note, NumberOfNotes> notes;
        uint32_t durationMs;

      private:
        friend std::ostream& operator<<(std::ostream& os, const Note& note) {
            os << "Note(Note=" << static_cast<int>(note.Note)
               << ", Octave=" << static_cast<int>(note.Octave) << ")";
            return os;
        }
        friend std::ostream& operator<<(std::ostream& os, const Chord& chord) {
            os << "Chord(durationMs=" << chord.durationMs << "){\n";
            for (size_t i = 0; i < chord.notes.size(); ++i) {
                os << "  Note " << i << ": " << chord.notes[i] << "\n";
            }
            os << "}";
            return os;
        }
    };

    Chord_Player(std::array<PWMPin, NumberOfNotes>&& pins)
        : buzzers(std::move(pins)) {}

    void playChord(const Chord& chord) {
        std::cout << "Playing chord: " << chord << std::endl;
        for (size_t i = 0; i < NumberOfNotes; ++i) {
            buzzers[i].writeNote(chord.notes[i].Note, chord.notes[i].Octave);
        }
        delay(chord.durationMs);
        for (auto& buzzer : buzzers) {
            buzzer.write(0);
        }
    }
    void stop() {
        for (auto& buzzer : buzzers) {
            buzzer.write(0);
        }
    }
};