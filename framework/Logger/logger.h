#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Log {

    /// @brief Print content of any type
    template<typename T>
    void printargs(T arg) {
        std::cout << arg << '\n';
    }

    /// @brief Print all supplied arguments
    template<typename T, typename... TArgs>
    void printargs(T head, TArgs... tail) {
        std::cout << head;
        printargs(tail...);
    }

    /// @brief Print an info message to std::cout
    /// @param tag Where the message was sent from (required)
    /// @param msg Message content (required)
    /// @param ...args Optional extra content
    template<typename T, typename... TArgs>
    void info(const char* tag, T msg, TArgs... args) {
        std::cout << "[" << tag << "] ";
        printargs(msg, args...);
    }

    /// @brief Print a warning message to std::cout
    /// @param tag Where the message was sent from (required)
    /// @param msg Message content (required)
    /// @param ...args Optional extra content
    template<typename T, typename... TArgs>
    void warning(const char* tag, T msg, TArgs... args) {
        std::cout << "[" << tag << "] WARNING: ";
        printargs(msg, args...);
    }

    /// @brief Print an error message to std::cerr
    /// @param tag Where the message was sent from (required)
    /// @param msg Message content (required)
    /// @param ...args Optional extra content
    template<typename T, typename... TArgs>
    void error(const char* tag, T msg, TArgs... args) {
        std::cerr << "[" << tag << "] ERROR: ";
        printargs(msg, args...);
    }
}

#endif