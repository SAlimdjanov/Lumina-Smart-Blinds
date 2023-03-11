#include <Subsystems/Utilities/SystemLogger.h>

SystemLogger* SystemLogger::logInstance = NULL;

SystemLogger::SystemLogger() : logLevel(Level::LOG_INFO) {}

SystemLogger* SystemLogger::getLogger() {
    if (SystemLogger::logInstance == NULL) {
        SystemLogger::logInstance = new SystemLogger();
    }
    return SystemLogger::logInstance;
}

void SystemLogger::setLoggerLevel(Level logLevel) { this->logLevel = logLevel; }

void SystemLogger::logVerbose(std::string tag, std::string message) {
    sendToLog(Level::LOG_VERBOSE, tag, message);
}

void SystemLogger::logDebug(std::string tag, std::string message) {
    sendToLog(Level::LOG_DEBUG, tag, message);
}

void SystemLogger::logInfo(std::string tag, std::string message) {
    sendToLog(Level::LOG_INFO, tag, message);
}

void SystemLogger::logWarning(std::string tag, std::string message) {
    sendToLog(Level::LOG_WARNING, tag, message);
}

void SystemLogger::logError(std::string tag, std::string message) {
    sendToLog(Level::LOG_ERROR, tag, message);
}

bool SystemLogger::shouldLog(int logLevel) {
    if (this->logLevel > logLevel) {
        return false;
    }
    return true;
}

void SystemLogger::sendToLog(Level logLevel, std::string tag,
                             std::string message) {
    if (shouldLog(logLevel)) {
        std::string logMessage =
            logLevelString[logLevel] + ": " + tag + ": " + message;
        Serial.println(logMessage.c_str());
    }
}
