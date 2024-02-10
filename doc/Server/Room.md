# [Room](https://github.com/DangeL187/DCSL/blob/main/include/Server/Room.h)
## A room class that describes the name of the room and the list of user's names inside it

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | Room(std::string room_name_ = "") | Set room's name |
| void | addUsername(std::string username) | Add new username in the usernames list. |
| void | broadcast(Message message, std::map<unsigned int, User>  users_list) | Send message using "sendMessage" to everyone in the room except the sender. |
| std::string | getName() | Get room's name. |
| std::vector<std::string> | getUsernamesList() | Get a vector containing the names of the users in this room. |
| bool | isUser(std::string username) | Return true if the user is in this room otherwise return false. |
| void | removeUsername(std::string username) | Remove the username from the usernames list. |

### Private Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| void | `sendMessage(Message message, tcp_connection::pointer connection)` | Send a message to socket. |
