#pragma once
#include <Arduino.h>

class Pin {
    uint8_t pinNumber_;

  protected:
    uint8_t pinNumber() const { return this->pinNumber_; }
    Pin(int pinNumber)
        : pinNumber_(pinNumber) {};

    void write(bool value) const {
        digitalWrite(pinNumber_, value ? HIGH : LOW);
    }
    bool read() const { return digitalRead(pinNumber_) == HIGH; }
};

class OutputPin : protected Pin {
  public:
    uint8_t pinNumber() const { return pinNumber(); }
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