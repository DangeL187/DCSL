# [TCP_Server](https://github.com/DangeL187/DCSL/blob/main/include/Server/TCP_Server.h)
## An auxiliary class for Server.h used to create convenient interaction with the <b>boost</b> library

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `TCP_Server(const std::string& address, unsigned short port)` | Construct a TCP_Server object, create a new thread for "acceptHandler". |

### Private Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| void | `acceptHandler()` | Continuously checks if a new user is connected and, if so, accepts connection using "accept". |
| void | `accept(tcp_connection::pointer& connection, const boost::system::error_code& error)` | Add new connection in the "sockets" list |

TCP_Server uses `std::map<unsigned int, tcp_connection::pointer> sockets` to store connections.
