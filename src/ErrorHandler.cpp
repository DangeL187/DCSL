#include "ErrorHandler.h"

ErrorHandler::ErrorHandler() = default;

void ErrorHandler::setMode(short error_handler_mode) {
    mode = error_handler_mode;
}

void ErrorHandler::log(const std::string& error_msg, short error_handler_mode) const {
    if (error_handler_mode == -1) error_handler_mode = mode;

    if (error_handler_mode == 1) {
        //write to file
    } else if (error_handler_mode == 2) {
        std::cerr << error_msg << "\n";
    } else {
        std::cout << error_msg << "\n";
    }
}