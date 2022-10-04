#include <Subsystems/StepperMotor/StepperMotor.h>

// Step Motor Driver Input Pins 1-4
static gpio_num_t MOTOR_PIN_1 = GPIO_NUM_4;
static gpio_num_t MOTOR_PIN_2 = GPIO_NUM_16;
static gpio_num_t MOTOR_PIN_3 = GPIO_NUM_17;
static gpio_num_t MOTOR_PIN_4 = GPIO_NUM_5;

// Steps per revolution
static const int STEPS_PER_REVOLUTION = 2048;

Stepper stepMotor(STEPS_PER_REVOLUTION, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3,
                  MOTOR_PIN_4);

StepMotor::StepMotor() {}

void StepMotor::initialize(void) {
    stepMotor.setSpeed(MOTOR_SPEED);
    systemLogger->logInfo(tag, "Initialized Stepper Motor to speed 10 RPM");
}

void StepMotor::turnCCW(int steps) {
    stepMotor.step(-steps);
    std::string message = "Turned motor Counterclockwise";
    systemLogger->logInfo(tag, message);
}

void StepMotor::turnCW(int steps) {
    stepMotor.step(steps);
    std::string message = "Turned motor Clockwise";
    systemLogger->logInfo(tag, message);
}

void StepMotor::stop() {
    stepMotor.step(0);
    std::string message = "Stopped Motor";
    systemLogger->logInfo(tag, message);
}