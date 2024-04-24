#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "../ErrorHandler.h"
#include "../Message.h"

#pragma comment(lib, "ws2_32")

class Room;
class RoomManager;
class tcp_connection;
class TCP_Server;
class User;

class Server {
public:
    Server(const std::string& ip, unsigned short port, short error_handler_mode = 0);

    void createRoom(const std::string& room_name);
    bool isUser(const std::string& name);
    User& getUser(const std::string& name);

private:
    ErrorHandler                                    error_handler;
    Message                                         output;
    std::shared_ptr<RoomManager>                    room_manager;
    int                                             sockets_size = 0;
    std::shared_ptr<TCP_Server>                     tcp_server;
    std::shared_ptr<std::map<unsigned int, User>>   users_list;

    [[noreturn]] void acceptConnections();
    void broadcast(const Message& message);
    void clientHandler(unsigned int const_index);
    void connect(const std::string& name, const boost::shared_ptr<tcp_connection>& socket);
    int defineCommand(const Message& message, boost::shared_ptr<tcp_connection>& connection);
    int joinRoom(const Message& message);
    int receiveMessage(unsigned int index);
    void sendMessage(const std::string& msg, boost::shared_ptr<tcp_connection>& connection, int command = 0);
};
