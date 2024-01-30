#include <iostream>

class ErrorHandler {
private:
    unsigned int mode = 0;
public:
    ErrorHandler() = default;

    void setMode(unsigned int error_handler_mode) {
        mode = error_handler_mode;
    }

    void log(std::string error_msg, unsigned int error_handler_mode = -1) {
        if (error_handler_mode == -1) error_handler_mode = mode;

        if (error_handler_mode == 1) {
            //
        } else if (error_handler_mode == 2) {
            //////
        } else {
            std::cout << error_msg << "\n";
        }
    }
};