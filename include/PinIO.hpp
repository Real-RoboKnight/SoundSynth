#pragma once

/**
 * @file PinIO.hpp
 * @author Dylan Shah (dylan.shah@outlook.com)
 * @brief Wraps arduino pin functions into C++ classes
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

#include <Arduino.h>

class Pin {
    uint8_t pinNumber_;

  protected:
    uint8_t pinNumber() const { return this->pinNumber_; }

    void write(bool value) const {
        digitalWrite(pinNumber_, value ? HIGH : LOW);
    }
    bool read() const { return digitalRead(pinNumber_) == HIGH; }

  public:
    Pin(int pinNumber)
        : pinNumber_(pinNumber) {}
    Pin& operator=(const Pin&) = delete;
    Pin(const Pin&) = delete;
    Pin(Pin&& other) noexcept
        : pinNumber_(other.pinNumber_) {
        other.pinNumber_ = 255;
    }
    Pin& operator=(Pin&& other) noexcept {
        if (this == &other) return *this;
        this->pinNumber_ = other.pinNumber_;
        other.pinNumber_ = 255;
        return *this;
    }
};

class OutputPin : protected Pin {
  public:
    uint8_t pinNumber() const { return Pin::pinNumber(); }
    OutputPin(int pinNumber)
        : Pin(pinNumber) {
        pinMode(pinNumber, OUTPUT);
    }
    void setHigh() const { write(true); }
    void setLow() const { write(false); }
    void write(bool value) const { Pin::write(value); }
};

class InputPin : Pin {
  public:
    uint8_t pinNumber() const { return pinNumber(); }

    InputPin(int pinNumber)
        : Pin(pinNumber) {
        pinMode(pinNumber, INPUT);
    }
    bool read() const { return Pin::read(); }
};