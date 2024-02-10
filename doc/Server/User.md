# [User](https://github.com/DangeL187/DCSL/blob/main/include/Server/User.h)
## A user class that describes user's name, socket and room

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `User(std::string name_, tcp_connection::pointer socket_)` | Set name and socket. |
| void | `setRoom(std::string room_name_)` | Set user's room |
| std::string | `getName()` | Get user's name |
| std::string | `getRoom()` | Get user's room |
| tcp_connection::pointer& | `getSocket()` | Get a reference to user's socket |
