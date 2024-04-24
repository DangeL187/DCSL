#include <iostream>

class ErrorHandler {
public:
    ErrorHandler();

    void setMode(short error_handler_mode);
    void log(const std::string& error_msg, short error_handler_mode = -1) const;

private:
    short mode = 0;
};