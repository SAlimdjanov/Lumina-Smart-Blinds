/**
 * @file SystemLogger.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>

#include <string>

class SystemLogger {
   public:
    enum Level { LOG_VERBOSE, LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR };
    static SystemLogger* getLogger();
    void setLoggerLevel(Level logLevel);
    void logVerbose(std::string tag, std::string message);
    void logDebug(std::string tag, std::string message);
    void logInfo(std::string tag, std::string message);
    void logWarning(std::string tag, std::string message);
    void logError(std::string tag, std::string message);
    void sendToLog(Level logLevel, std::string tag, std::string message);

   private:
    SystemLogger();
    static SystemLogger* logInstance;
    int logLevel;
    const std::string logLevelString[5] = {"VERBOSE", "DEBUG", "INFO",
                                           "WARNING", "ERROR"};
    std::string createMessage(int logLevel);
    bool shouldLog(int logLevel);
};