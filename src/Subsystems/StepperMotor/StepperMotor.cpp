#include <Subsystems/StepperMotor/StepperMotor.h>

// Stepper Motor Init
static gpio_num_t DIR = GPIO_NUM_4;
static gpio_num_t STEP = GPIO_NUM_5;
const int INTERFACE_TYPE = 1;

// Limit switch pin init
static gpio_num_t LIMIT_SWITCH = GPIO_NUM_35;

// Test voltage reader
static gpio_num_t READ_VOLTAGE_PIN = GPIO_NUM_34;

// // Steps per revolution
// static const int STEPS_PER_REVOLUTION = 200;

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
    // if (current_position < 0) {
    //     systemLogger->logInfo(tag, "Negative position value");
    // } else if (current_position > 0) {
    //     systemLogger->logInfo(tag, "Positive position value");
    // }
    int substep_size = 5;
    int substeps = (-steps - current_position) / substep_size;
    if (substeps < 0) {
        for (int i = 1; i >= substeps; i--) {
            if (!isAtNinetyDegrees()) {
                myStepper.moveTo(current_position + substep_size * i);
            } else {
                systemLogger->logInfo(tag, "Motor movement terminated");
                return;
            }
        }
    } else {
        for (int i = 1; i <= substeps; i++) {
            myStepper.moveTo(current_position + substep_size * i);
        }
    }

    // myStepper.moveTo(-steps);
    //  if (!(isAtNinetyDegrees())) {   }
}

void StepMotor::turnCW(int steps) { myStepper.moveTo(steps); }

void StepMotor::stopMotor(void) { myStepper.stop(); }

/**
 * @brief Investigate why stop function doesn't work instead of loophole:
 *             - Moving back to zero does not work, continues motion in CW
 *               direction and crashes against lim switch.
 *             - Moving in both directions caused this issue.
 *             - Loophole does not permit additional movement once switch is
 *               triggered, but does not interrupt motion midway
 *
 */
void StepMotor::runStepper(void) {
    // remainingSteps = myStepper.distanceToGo();
    // if (!isAtNinetyDegrees() || remainingSteps > 0) {
    myStepper.run();
    //} else {
    //    // stopMotor();
    //    currentPosition = myStepper.currentPosition();
    //    myStepper.runToNewPosition(currentPosition);  // add for delay
    // }
}

int StepMotor::calibrationSweep(void) {
    int angleVoltage[90];
    int optimalAngle = 0;
    int maxVoltage = 0;
    int voltage = 0;

    turnMotor(round((90 * 1600 / 360)));
    // move to 90 degrees

    delay(5200);

    for (int i = 90; i > 0; i--) {
        delay(5000 / 90);
        voltage = analogRead(READ_VOLTAGE_PIN);
        angleVoltage[i] = voltage;
        turnCW(round((i)*1600 / 360));
    }
    // perform sweep from 90 to 0 degrees

    for (int m = 0; m < 91; m++) {
        if (angleVoltage[m] > maxVoltage) {
            optimalAngle = m;
            maxVoltage = angleVoltage[m];
        }
    }
    // determine max angle

    systemLogger->logVerbose(tag, "Optimal angle is: " + optimalAngle);

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
        systemLogger->logVerbose(tag, "TRIGGERED!!!");
        return true;
    } else {
        systemLogger->logVerbose(tag, "NOT TRIGGERED!");
        return false;
    }
}