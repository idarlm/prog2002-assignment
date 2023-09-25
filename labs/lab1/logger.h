#include <iostream>

#ifndef LOGGER_H
#define LOGGER_H

enum LogLevel
{
    INFO = 0,
    WARNING = 1,
    ERROR = 2,
};

class Log
{
private:
    Log() {}             // Hide constructor, should call init at start of application
    inline static Log* instance;
    const std::string PREFIX_INFO    = "[INFO] ";
    const std::string PREFIX_WARNING = "[WARNING] ";
    const std::string PREFIX_ERROR   = "[ERROR] ";
public:
    LogLevel logLevel = INFO;
    static void Info(std::string);
    static void Warning(std::string);
    static void Error(std::string);
    static void Wait();
    static void Init();
};

#endif