# [Client.h](https://github.com/DangeL187/DCSL/blob/main/include/Client/Client.h)
## Main client header

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `Client(const std::string& user_name_, const std::string& ip, unsigned short port, short error_handler_mode = 0)` | Construct a Client object, initialize TCP_Client object, create a new thread for "clientHandler". | 
| Message | `getOutput()` | Get the last message received. |
| void | `sendMessage(const std::string& input, int command = 0)` | Send a message using the TCP_Client object. |

### Private Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| int | `clientHandler()` | Continuously calls "recieveMessage" until it returns -1. |
| int | `recieveMessage()` | <p>Recieves a message from the server using TCP_Client object.</p> <p>Received message is stored in the "output" variable.</p> <p>Returns -1 if the client was disconnected.</p> |
