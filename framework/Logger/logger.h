#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Log {
    void info(std::string tag, std::string msg);
    void warning(std::string tag, std::string msg);
    void error(std::string tag, std::string msg);
    void pause();

    void printmsg(std::string, std::string, std::string);
}

#endif