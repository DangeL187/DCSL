# [ErrorHandler](https://github.com/DangeL187/DCSL/blob/main/include/ErrorHandler.h)
## The class that is used to process output of errors

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `ErrorHandler()` | Default constructor. |
| void | `setMode(short error_handler_mode)` | <p>Set error handling mode:</p> <p>0 - std::cout</p> <p>1 - write to file(unrealized yet)</p> <p>2 - std::cerr</p> |
| void | `log(const std::string& error_msg, short error_handler_mode = -1) const` | Log an error using one of the error handling modes, the default mode is set. Alternatively, you can specify how to log the error manually using the second argument. |
