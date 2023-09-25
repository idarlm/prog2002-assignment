#include "logger.h"

void Log::Info(std::string msg)
{
    if(Log::instance->logLevel <= LogLevel::INFO)
        std::cout << Log::instance->PREFIX_INFO << msg << std::endl;
}

void Log::Warning(std::string msg)
{
    if(Log::instance->logLevel <= LogLevel::WARNING)
        std::cout << Log::instance->PREFIX_WARNING << msg << std::endl;
}

void Log::Error(std::string msg)
{
    if(Log::instance->logLevel <= LogLevel::ERROR)
        std::cout << Log::instance->PREFIX_ERROR << msg << std::endl;
}

void Log::Wait()
{
    if(Log::instance->logLevel <= LogLevel::INFO)
    {
        std::cout << "Press enter to continue...";
        std::cin.get();
    }
}

void Log::Init()
{
    Log* log = new Log();
    Log::instance = log;
}