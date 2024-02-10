# [TCP_Client.h](https://github.com/DangeL187/DCSL/blob/main/include/Client/TCP_Client.h)
## An auxiliary header file used to create convenient interaction with the <b>boost</b> library
### Public Member Functions

| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `TCP_Client(const std::string& address, unsigned short port)` | Construct a TCP_Client object and set up a client socket on specified address and port. | 
| std::vector<std::string> | `recv()` | Get a message using the client socket. |
| void | `send(const std::vector<std::string>& message)` | Send a message using the client socket. |
