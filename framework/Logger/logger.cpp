#include "logger.h"

void Log::info(std::string tag, std::string msg)
{
    printmsg(tag, "Info", msg);
}

void Log::warning(std::string tag, std::string msg)
{
    printmsg(tag, "Warning", msg);
}

void Log::error(std::string tag, std::string msg)
{
    printmsg(tag, "Error", msg);
}

void Log::pause()
{
    std::cin.get();
}

void Log::printmsg(std::string tag, std::string type, std::string msg) {
    std::string prefix = tag == "" ? "" : "[" + tag + "] ";
    std::cout << prefix << type << ": " << msg << "\n";
}