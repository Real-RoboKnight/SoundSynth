#include "PWMPin.hpp"
#include <unity.h>
using namespace std::string_literals;

void testBuzzerUsageMaskEmpty() {
    TEST_ASSERT_EQUAL(PWMPin::getBuzzerUsageMask().to_ulong(), 0b000000);
}

void testPWMPinCreation() {
    PWMPin pwmPin1(5);
    TEST_ASSERT_EQUAL(0, pwmPin1.getTimerNumber());

    PWMPin pwmPin2(18);
    TEST_ASSERT_EQUAL(1, pwmPin2.getTimerNumber());

    PWMPin pwmPin3(19);
    TEST_ASSERT_EQUAL(2, pwmPin3.getTimerNumber());
}

void testPWMPinMoveEqual() {
    PWMPin pwmPin1(21);
    uint8_t timer1 = pwmPin1.getTimerNumber();
    unsigned long maskBefore = PWMPin::getBuzzerUsageMask().to_ulong();
    std::cout << "Before move. this pin: " << pwmPin1
              << " other pin will be created" << std::endl;

    PWMPin pwmPin3 = std::move(pwmPin1);
    std::cout << "Move did not throw\n"
              << "pin 1: " << pwmPin1 << " pin 2: " << pwmPin3 << std::endl;

    TEST_ASSERT_EQUAL(timer1, pwmPin3.getTimerNumber());
    TEST_ASSERT_EQUAL(maskBefore, PWMPin::getBuzzerUsageMask().to_ulong());
}

void testPWMPinMoveEqualSemantics() {
    PWMPin pwmPin1(21);
    uint8_t timer1 = pwmPin1.getTimerNumber();
    unsigned long maskBefore = PWMPin::getBuzzerUsageMask().to_ulong();

    std::cout << "Before move. this pin: " << pwmPin1
              << " other pin will be created" << std::endl;

    PWMPin pwmPin3(22);
    pwmPin3 = std::move(pwmPin1);

    std::cout << "Move assignment did not throw\n"
              << "pin 1: " << pwmPin1 << " pin 2: " << pwmPin3 << std::endl;
    pwmPin1.~PWMPin(); // Manually call destructor to observe behavior
    std::cout << "\n After move assignment the bitmask is: "
              << PWMPin::getBuzzerUsageMask() << std::endl;

    TEST_ASSERT_EQUAL(timer1, pwmPin3.getTimerNumber());
    TEST_ASSERT_EQUAL(maskBefore, PWMPin::getBuzzerUsageMask().to_ulong());
}

void testMoveConstructor() {
    try {
        PWMPin pwmPin1(23);
    } catch (...) {
        // Dtors not working
        TEST_FAIL_MESSAGE("Failed to create PWMPin in move constructor test");
    }
    try {
        PWMPin pwmPin1(23);
        uint8_t timer1 = pwmPin1.getTimerNumber();
        PWMPin pwmPin2 = std::move(pwmPin1);
        TEST_ASSERT_EQUAL(timer1, pwmPin2.getTimerNumber());

    } catch (...) { TEST_FAIL_MESSAGE("move constructor failed"); }
}

void testPlayNote(int pinNumber) {
    PWMPin pwmPin1(pinNumber);
    pwmPin1.writeNote(PWMPin::Note::C, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::Cs, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::D, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::Eb, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::E, 4);
    delay(500);
    pwmPin1.write(0);
    pwmPin1.writeNote(PWMPin::Note::F, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::Fs, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::G, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::Gs, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::A, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::Bb, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
    pwmPin1.writeNote(PWMPin::Note::B, 4);
    delay(500);
    pwmPin1.write(0);
    delay(100);
}

void setUp(void) { std::cout << std::endl; }

void tearDown(void) { std::cout << std::endl; }

void setup() {
    UNITY_BEGIN();
    RUN_TEST(testBuzzerUsageMaskEmpty);
    RUN_TEST(testPWMPinCreation);
    RUN_TEST(testBuzzerUsageMaskEmpty);
    RUN_TEST(testPWMPinCreation);
    RUN_TEST(testPWMPinMoveEqualSemantics);
    RUN_TEST(testPWMPinMoveEqual);
    RUN_TEST(testMoveConstructor);
    RUN_TEST([]() { testPlayNote(18); });
    RUN_TEST([]() { testPlayNote(23); });
    RUN_TEST([]() { testPlayNote(4); });
    RUN_TEST([]() { testPlayNote(15); });
    RUN_TEST([]() { testPlayNote(21); });
    UNITY_END();
}

void loop() {}