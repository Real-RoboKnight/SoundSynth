#pragma once

#include "PWMPin.hpp"

template<size_t NumberOfNotes>
class Chord_Player {
    std::array<PWMPin, NumberOfNotes> buzzers;

  public:
    struct Chord {
        struct Note {
            PWMPin::Note Note;
            uint8_t Octave;
        };

        std::array<Note, NumberOfNotes> notes;
        uint32_t durationMs;
    };

    Chord_Player(std::array<PWMPin, NumberOfNotes>&& pins)
        : buzzers(std::move(pins)) {}

    void playChord(const Chord& chord) {
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