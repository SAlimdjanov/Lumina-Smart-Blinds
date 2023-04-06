#include <Subsystems/Messaging/SCPIHandler.h>

std::string SCPIHandler::tag = "SCPI Handler";
SystemLogger *SCPIHandler::systemLogger = SystemLogger::getLogger();
StepMotor *SCPIHandler::stepperMotor = new StepMotor();

SCPIHandler::SCPIHandler(SCPIListener *listener) : scpiListener(listener) {
    listener->registerNewMessage(F("*IDN?"), &SCPIHandler::identifyCommand);
    listener->registerNewMessage(F(":MOTOr:MCW:"), &SCPIHandler::moveMotorClockwise);
    listener->registerNewMessage(F(":MOTOr:MCCW:"), &SCPIHandler::moveMotorCounterclockwise);
    listener->registerNewMessage(F(":MOTOr:STOP:"), &SCPIHandler::stopMotor);
    listener->registerNewMessage(F(":UTILs:SETL:"), &SCPIHandler::changeLogLevel);
    listener->registerNewMessage(F(":CALIbrate:SWEEp:"), &SCPIHandler::calibrate);
}

void SCPIHandler::identifyCommand(SCPI_C messages, SCPI_P parameters, Stream &interface) {
    String identifier = "ENGPHYS 4A06: Automated Solar Blinds Capstone Project\n";
    interface.print(identifier);
}

void SCPIHandler::moveMotorClockwise(SCPI_C messages, SCPI_P parameters, Stream &interface) {
    if (areParametersValid(parameters, 1, interface) == true) {
        stepperMotor->turnCW(String(parameters[0]).toInt());
        systemLogger->logInfo(tag, "Received clockwise command");
    }
}

void SCPIHandler::moveMotorCounterclockwise(SCPI_C messages, SCPI_P parameters, Stream &interface) {
    if (areParametersValid(parameters, 1, interface) == true) {
        stepperMotor->turnMotor(String(parameters[0]).toInt());
        systemLogger->logInfo(tag, "Received counterclockwise command");
    }
}

void SCPIHandler::stopMotor(SCPI_C messages, SCPI_P parameters, Stream &interface) {
    stepperMotor->stopMotor();
    systemLogger->logInfo(tag, "Stopped Motor.");
}

// void SCPIHandler::currentPosition(SCPI_C messages, SCPI_P parameters,
//                             Stream &interface) {

//     // stepperMotor->currentPosition();
//     // systemLogger->logInfo(tag, "The current position is "+ );
// }

void SCPIHandler::changeLogLevel(SCPI_C messages, SCPI_P parameters, Stream &interface) {
    if (areParametersValid(parameters, 1, interface) == true) {
        int newLevelInt = String(parameters[0]).toInt();
        if (newLevelInt < 5) {
            SystemLogger::Level newLogLevel = SystemLogger::LOG_VERBOSE;
            switch (newLevelInt) {
                case 0:
                    newLogLevel = SystemLogger::LOG_VERBOSE;
                case 1:
                    newLogLevel = SystemLogger::LOG_DEBUG;
                case 2:
                    newLogLevel = SystemLogger::LOG_INFO;
                case 3:
                    newLogLevel = SystemLogger::LOG_WARNING;
                case 4:
                    newLogLevel = SystemLogger::LOG_ERROR;
            }
            systemLogger->setLoggerLevel(newLogLevel);
        } else {
            systemLogger->logError(tag, "New Log Level Invalid");
        }
    }
}

void SCPIHandler::calibrate(SCPI_C messages, SCPI_P parameters, Stream &interface) {
    stepperMotor->calibrationSweep();
}

bool SCPIHandler::areParametersValid(SCPI_P parameters, int expectedNumber, Stream &interface) {
    if (parameters.Size() != expectedNumber) {
        interface.println("Invalid parameter input");
        return false;
    }
    return true;
}
