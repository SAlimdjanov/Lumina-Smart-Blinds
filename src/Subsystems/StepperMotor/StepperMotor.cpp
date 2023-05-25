#include <Subsystems/StepperMotor/StepperMotor.h>

// Stepper Motor Init
static gpio_num_t DIR = GPIO_NUM_4;
static gpio_num_t STEP = GPIO_NUM_5;
const int INTERFACE_TYPE = 1;

// Limit switch pin init
static gpio_num_t LIMIT_SWITCH = GPIO_NUM_35;

// Test voltage reader
static gpio_num_t READ_VOLTAGE_PIN = GPIO_NUM_34;

// Instance of AccelStepper
AccelStepper myStepper(INTERFACE_TYPE, STEP, DIR);

StepMotor::StepMotor() {}

int period = 1000;
unsigned long time_now = 0;

void StepMotor::initialize(void) {
    pinMode(READ_VOLTAGE_PIN, INPUT);
    pinMode(LIMIT_SWITCH, INPUT);
    myStepper.setMaxSpeed(500);
    myStepper.setAcceleration(50);
    myStepper.setSpeed(40);
    systemLogger->logInfo(tag, "Initialized Stepper Motor");
}

void StepMotor::turnMotor(int steps) {
    int current_position = myStepper.currentPosition();  // test if current position is negative
                                                         // first so 50% should show up as -50
    int substep_size = 5;
    int substeps = (-steps - current_position) / substep_size;
    if (substeps < 0) {
        for (int i = 1; i >= substeps; i--) {
            if (!isAtNinetyDegrees()) {
                myStepper.moveTo(current_position + substep_size * i);

            } else {
                systemLogger->logError(tag, "Motor movement terminated");
                return;
            }
        }
    } else {
        for (int i = 1; i <= substeps; i++) {
            myStepper.moveTo(current_position + substep_size * i);
        }
    }
}

void StepMotor::turnCW(int steps) { myStepper.moveTo(steps); }

void StepMotor::stopMotor(void) { myStepper.disableOutputs(); }

/**
 * @brief Investigate why stop function doesn't work instead of loophole:
 *             - Moving back to zero does not work, continues motion in CW
 *               direction and crashes against lim switch.
 *             - Moving in both directions caused this issue.
 *             - Loophole does not permit additional movement once switch is
 *               triggered, but does not interrupt motion midway
 *
 */
void StepMotor::runStepper(void) { myStepper.run(); }

int StepMotor::calibrationSweep(void) {
    unsigned long timer = millis();
    int optimalAngle = 0;

    // to 90
    turnMotor(400);

    // delay motor movement
    for (int j = 0; j < 100000000; j++) {
        if (millis() - timer > 1000) {
            // measureVoltage();
            turnMotor(0);
            timer = millis();
            break;
        }
    }

    return optimalAngle;
}

bool StepMotor::inMotion(void) {
    remainingSteps = myStepper.distanceToGo();
    if (remainingSteps != 0) {
        systemLogger->logVerbose(tag, "The remaining steps are: " + remainingSteps);
        return true;
    }
    return false;
}

bool StepMotor::isAtNinetyDegrees(void) {
    if (gpio_get_level(LIMIT_SWITCH) == 1) {
        systemLogger->logDebug(tag, "TRIGGERED!!!");
        return true;
    } else {
        systemLogger->logDebug(tag, "NOT TRIGGERED!!!");
        return false;
    }
}

void StepMotor::measureVoltage(void) {
    uint16_t measuredVoltage = 0;
    unsigned long timer = millis();
    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < 100000000; j++) {
            if (millis() - timer > 40) {
                measuredVoltage = analogRead(READ_VOLTAGE_PIN);
                Serial.println(measuredVoltage);
                timer = millis();
                break;
            }
        }
    }
}

void StepMotor::reenableMotor(void) { myStepper.enableOutputs(); }