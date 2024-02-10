# [Server.h](https://github.com/DangeL187/DCSL/blob/main/include/Server/Server.h)
## Main server header

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `Server(const std::string& ip, unsigned short port, unsigned int error_handler_mode = 0)` | Construct a Server object, initialize TCP_Server object, create a new thread for "acceptConnections". | 
| void | `createRoom(const std::string& room_name)` | Call room_manager's member function "createRoom" passing room's name as an argument. |
| User& | `getUser(const std::string& name)` | Return a reference to the User object in the server's list of users by provided username. |
| bool | `isUser(const std::string& name)` | Return true if the user is in the server's list of users, otherwise returns false. |

### Private Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| void | `acceptConnections()` | Continuously checks if a new user is connected and, if so, creates a new thread for "clientHandler". |
| void | `clientHandler(unsigned int const_index)` | <p>Continuously calls "recieveMessage" until it returns -1.</p> <p>Also continuously calls "defineCommand" until it returns -1.</p> |
| int | `receiveMessage(unsigned int index)` | <p>Recieve a message from the client using TCP_Server object.</p> <p>Received message is stored in the "output" variable.</p> <p>Handles an event when the client is disconnected.</p> |
| int | `defineCommand(const Message& message, tcp_connection::pointer& connection)` | Define the command received from the client and call the appropriate method. |
| int | `joinRoom(const Message& message)` | <p>Place the sender of the message in the room specified in the message.</p> <p>Returns -1 if the room does not exist.</p> <p>Returns -2 if the user is already in a room.</p> |
| void | `broadcast(const Message& message)` | Сall the "broadcast" method on the object of the room in which the sender is placed. |
| static void| `sendMessage(const std::string& msg, tcp_connection::pointer& connection, bool force_exit = false)` | Send a message from the server to the client. |
| void | `connect(const std::string& name, tcp_connection::pointer socket` | Add a user in the server's users list. |
