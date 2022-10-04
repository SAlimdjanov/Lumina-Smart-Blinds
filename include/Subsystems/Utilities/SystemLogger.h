/**
 * @file SystemLogger.h
 * @author Sean Alimdjanov (alimdjas@mcmaster.ca)
 * @brief System Logger, captures all events within embedded system
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
    /**
     * @brief Enumerates log levels
     *
     */
    enum Level { LOG_VERBOSE, LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR };

    /**
     * @brief Get the Logger object
     *
     * @return SystemLogger*
     */
    static SystemLogger* getLogger();

    /**
     * @brief Set the log level
     *
     * @param logLevel
     */
    void setLoggerLevel(Level logLevel);

    /**
     * @brief Create a verbose log message
     *
     * @param tag Module identifier tag
     * @param message Information
     */
    void logVerbose(std::string tag, std::string message);

    /**
     * @brief Create a debug log message
     *
     * @param tag Module identifier tag
     * @param message Information
     */
    void logDebug(std::string tag, std::string message);

    /**
     * @brief Create a info log message
     *
     * @param tag Module identifier tag
     * @param message Information
     */
    void logInfo(std::string tag, std::string message);

    /**
     * @brief Create a warning log message
     *
     * @param tag Module identifier tag
     * @param message Information
     */
    void logWarning(std::string tag, std::string message);

    /**
     * @brief Create an error log message
     *
     * @param tag Module identifier tag
     * @param message Information
     */
    void logError(std::string tag, std::string message);

    /**
     * @brief Send message to the logger
     *
     * @param logLevel Logging level
     * @param tag Module identifier tag
     * @param message Information
     */
    void sendToLog(Level logLevel, std::string tag, std::string message);

   private:
    // Logger instance object
    static SystemLogger* logInstance;
    // Log level variable
    int logLevel;
    // Log level string array
    const std::string logLevelString[5] = {"VERBOSE", "DEBUG", "INFO",
                                           "WARNING", "ERROR"};

    /**
     * @brief Construct a new System Logger object
     *
     */
    SystemLogger();

    /**
     * @brief Create log message string
     *
     * @param logLevel Logging level
     * @return complete string message
     */
    std::string createMessage(int logLevel);

    /**
     * @brief Check if message should be pushed to logger based on selected
     * logging level
     *
     * @param logLevel Logging level
     * @return true
     * @return false
     */
    bool shouldLog(int logLevel);
};