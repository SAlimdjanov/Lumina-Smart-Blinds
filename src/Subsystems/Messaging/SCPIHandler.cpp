#include <Subsystems/Messaging/SCPIHandler.h>

std::string SCPIHandler::tag = "SCPI Handler";
SystemLogger *SCPIHandler::systemLogger = SystemLogger::getLogger();
StepMotor *SCPIHandler::stepperMotor = new StepMotor();

SCPIHandler::SCPIHandler(SCPIListener *listener) : scpiListener(listener) {
    listener->registerNewMessage(F("*IDN?"), &SCPIHandler::identifyCommand);
    listener->registerNewMessage(F(":MOTOr:STOP:"), &SCPIHandler::stopMotor);
    listener->registerNewMessage(F(":MOTOr:MCW:"),
                                 &SCPIHandler::moveMotorClockwise);
    listener->registerNewMessage(F(":MOTOr:MCCW:"),
                                 &SCPIHandler::moveMotorCounterclockwise);
}

void SCPIHandler::identifyCommand(SCPI_C messages, SCPI_P parameters,
                                  Stream &interface) {
    String identifier = "4A06 Automated Solar Blinds\n";
    interface.print(identifier);
}

void SCPIHandler::stopMotor(SCPI_C messages, SCPI_P parameters,
                            Stream &interface) {
    if (areParametersValid(parameters, 0, interface) == true) {
        stepperMotor->turn(0, 0);
        systemLogger->logInfo(tag, "Stopping Motor");
    }
}
void SCPIHandler::moveMotorClockwise(SCPI_C messages, SCPI_P parameters,
                                     Stream &interface) {
    if (areParametersValid(parameters, 1, interface) == true) {
        stepperMotor->turn(1, String(parameters[0]).toInt());
        systemLogger->logInfo(tag, "Turning Motor Clockwise");
    }
}

void SCPIHandler::moveMotorCounterclockwise(SCPI_C messages, SCPI_P parameters,
                                            Stream &interface) {
    if (areParametersValid(parameters, 1, interface) == true) {
        stepperMotor->turn(1, String(parameters[0]).toInt());
        systemLogger->logInfo(tag, "Turning Motor Counterclockwise");
    }
}

bool SCPIHandler::areParametersValid(SCPI_P parameters, int expectedNumber,
                                     Stream &interface) {
    if (parameters.Size() != expectedNumber) {
        interface.println("Invalid parameter input");
        return false;
    }
    return true;
}
