#pragma once
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