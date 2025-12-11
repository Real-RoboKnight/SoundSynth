#pragma once

#include "PinIO.hpp"
#include <bitset>
#include <esp32-hal-ledc.h>
#include <iostream>
#include <utility>

class PWMPin : OutputPin {
    static inline std::bitset<6> BuzzerUsageMask{
        0b000000
    }; // there are 6 hardware timers on ESP32
    uint8_t timerNumber;

    friend std::ostream& operator<<(std::ostream& os, const PWMPin& pin) {

        os << "PWMPin(pinNumber=" << static_cast<int>(pin.pinNumber())
           << ", timerNumber=" << static_cast<int>(pin.timerNumber)
           << "){UsageMask=" << getBuzzerUsageMask() << "}";
        return os;
    }

  public:
    static const std::bitset<6> getBuzzerUsageMask() { return BuzzerUsageMask; }

    PWMPin(int pinNumber)
        : OutputPin(pinNumber) {
        // Find an available timer
        for (uint8_t i = 0; i < 6; ++i) {
            if (!BuzzerUsageMask.test(i)) {
                timerNumber = i;
                BuzzerUsageMask.set(i);
                // Setup the LEDC channel for the buzzer
                ledcSetup(
                    timerNumber, 2000, 8); // 2kHz frequency, 8-bit resolution
                ledcAttachPin(pinNumber, timerNumber);
                return;
            }
        }
        // If no timers are available, throw an error
        throw std::runtime_error("No available hardware timers for Buzzer");
    }
    ~PWMPin() {
        std::cout << "PWMPin Destructor Called for timer "
                  << static_cast<int>(this->timerNumber)
                  << " Pin: " << static_cast<int>(this->pinNumber())
                  << std::endl;
        // Release the timer
        if (timerNumber < 6) BuzzerUsageMask.reset(timerNumber);
        if (pinNumber() != 255) { ledcDetachPin(pinNumber()); }
    }
    PWMPin(const PWMPin&) = delete;
    PWMPin& operator=(const PWMPin&) = delete;

    PWMPin(PWMPin&& other) noexcept
        : OutputPin(255)
        , timerNumber(255) {
        std::swap(this->timerNumber, other.timerNumber);
        OutputPin::operator=(std::move(other));
    }
    PWMPin& operator=(PWMPin&& other) noexcept {
        std::cout << "PWMPin Move Assignment Operator Called\n this timer: "
                  << static_cast<int>(this->timerNumber)
                  << " other timer: " << static_cast<int>(other.timerNumber)
                  << std::endl;
        if (this == &other) return *this;
        // Move-assign the base class
        OutputPin::operator=(std::move(other));
        std::swap(this->timerNumber, other.timerNumber);

        std::cout << "PWMPin Move Assignment Operator ending\n this timer: "
                  << static_cast<int>(this->timerNumber)
                  << " other timer: " << static_cast<int>(other.timerNumber)
                  << std::endl;
        return *this;
    }

    uint8_t getTimerNumber() const { return timerNumber; }

    enum class Note : uint8_t {
        C = NOTE_C,
        Cs = NOTE_Cs,
        D = NOTE_D,
        Eb = NOTE_Eb,
        E = NOTE_E,
        F = NOTE_F,
        Fs = NOTE_Fs,
        G = NOTE_G,
        Gs = NOTE_Gs,
        A = NOTE_A,
        Bb = NOTE_Bb,
        B = NOTE_B,
        MAX = NOTE_MAX,
        NONE
    };

    void write(uint32_t duty) { ::ledcWrite(timerNumber, duty); }
    uint32_t writeTone(uint32_t freq) {
        return ::ledcWriteTone(timerNumber, freq);
    }
    uint32_t writeNote(Note note, uint8_t octave) {
        return ::ledcWriteNote(timerNumber, static_cast<note_t>(note), octave);
    }
    uint32_t read() { return ::ledcRead(timerNumber); }
    uint32_t readFreq() { return ::ledcReadFreq(timerNumber); }
    uint32_t changeFrequency(uint32_t freq, uint8_t resolution_bits) {
        return ::ledcSetup(timerNumber, freq, resolution_bits);
    }
};