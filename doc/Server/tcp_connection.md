# [tcp_connection](https://github.com/DangeL187/DCSL/blob/main/include/Server/TCP_Server.h)
## An auxiliary class for TCP_Server used to to conveniently interact with sockets

### Public Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| static boost::shared_ptr<tcp_connection> | `create(boost::asio::io_context& io_context)` | Return a smart pointer to the new tcp_connection object. |
| tcp::socket& | `getSocket()` | Return a reference to the tcp::socket object. |
| std::vector<std::string> | `recv()` | Return recieved vector of strings. |
| void | `send(const std::vector<std::string>& message)` | Send a message. |

### Private Member Functions
| Return type | Function name | Description |
| ----------- | ------------- | ----------- |
| | `tcp_connection(boost::asio::io_context& io_context): socket(io_context)` | Default constructor. |
