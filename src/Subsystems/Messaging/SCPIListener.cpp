#include <Subsystems/Messaging/SCPIListener.h>

SCPIListener::SCPIListener() {}

void SCPIListener::listenForCommand() {
    for (int i = 0; i < interfaceList.size(); i++) {
        scpiParser.ProcessInput(*interfaceList[i], "%");
    }
}

void SCPIListener::registerNewMessage(const __FlashStringHelper *command,
                                      SCPI_caller_t caller) {
    scpiParser.RegisterCommand(command, caller);
    systemLogger->logInfo(tag, "Registered Command");
}

void SCPIListener::addNewInterface(Stream *interface) {
    this->interfaceList.push_back(interface);
    systemLogger->logInfo(tag, "Added interface");
}