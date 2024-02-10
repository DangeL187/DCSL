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
#include "../ErrorHandler.h"
#include "../Message.h"
#include "TCP_Server.h"
#include "User.h"
#include "Room.h"
#include "RoomManager.h"

class Server {
private:
    ErrorHandler                         error_handler;
    Message                              output;
    RoomManager                          room_manager;
    std::shared_ptr<TCP_Server>          tcp_server;
    std::map<unsigned int, User>         users_list;
    int                                  sockets_size = 0;

    [[noreturn]] void acceptConnections() {
        while (true) {
            if (tcp_server->sockets.size() > sockets_size && !tcp_server->sockets.empty()) {
                std::thread thread(&Server::clientHandler, this, tcp_server->counter);
                thread.detach();
                sockets_size++;
            }
        }
    }

    void clientHandler(unsigned int const_index) {
        error_handler.log("New Thread #" + std::to_string(const_index));
        while (true) {
            try {
                if (receiveMessage(const_index) == -1) break;
                else if (defineCommand(output, tcp_server->sockets[const_index]) == -1) break;
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
                break;
            }
        }
    }

    int receiveMessage(unsigned int index) {
        try {
            std::vector<std::string> vec = tcp_server->sockets[index]->recv();

            output.command = std::stoi(vec[0]);
            output.msg = vec[1];
            output.sender = vec[2];

            error_handler.log("Index: " + std::to_string(index) + " [" + vec[0] + "] msg: " + vec[1] + " from " + vec[2]);
        } catch (std::exception& e) {
            User& user = users_list.find(index)->second;
            error_handler.log(user.getName() + " disconnected!");
            if (!user.getRoom().empty()) {
                room_manager.getRoom(user.getRoom()).removeUsername(user.getName());
            }
            users_list.erase(index);
            tcp_server->sockets.erase(index);
            sockets_size--;
            return -1;
        }

        return 0;
    }

    int defineCommand(const Message& message, tcp_connection::pointer& connection) {
        if (message.command == -1) {
            if (!isUser(message.sender)) {
                connect(message.sender, connection);
            } else {
                sendMessage("This User is Already Online!", connection, true);
                return -1;
            }
        }
        else if (message.command == 1) {
            int t = joinRoom(message);
            if (t == -1) {
                sendMessage("This Room Does Not Exist!", connection);
            } else if (t == -2) {
                sendMessage("You Are Already In The Room!", connection);
            }
        }
        else {
            broadcast(message);
        }
        return 0;
    }

    int joinRoom(const Message& message) {
        bool is_user = false;
        for (Room& room: room_manager.getRooms()) {
            if (room.isUser(message.sender)) {
                is_user = true;
                break;
            }
        }
        if (!is_user) {
            for (std::pair<const unsigned int, User>& value: users_list) {
                User& user = value.second;
                if (user.getName() == message.sender) {
                    Room& get_room = room_manager.getRoom(message.msg);
                    std::string get_room_name = get_room.getName();
                    if (!get_room_name.empty()) {
                        user.setRoom(get_room_name);
                        get_room.addUsername(user.getName());
                        user.setRoom(get_room_name);
                    } else {
                        return -1;
                    }
                }
            }
        } else {
            return -2;
        }
        return 0;
    }

    void broadcast(const Message& message) {
        for (Room& room: room_manager.getRooms()) {
            if (room.isUser(message.sender)) {
                room.broadcast(message, users_list);
                break;
            }
        }
    }

    static void sendMessage(const std::string& msg, tcp_connection::pointer& connection, bool force_exit = false) {
        std::vector<std::string> vec(3);
        if (force_exit) {
            vec[0] = "-2";
        } else {
            vec[0] = "0";
        }
        vec[1] = msg;
        vec[2] = "SERVER";

        connection->send(vec);
    }

    void connect(const std::string& name, tcp_connection::pointer socket) {
        User user(name, socket);
        users_list.insert({tcp_server->counter, user});
        error_handler.log(name + " connected");
        tcp_server->counter++;
    }
public:
    Server(const std::string& ip, unsigned short port, unsigned int error_handler_mode = 0) {
        error_handler.setMode(error_handler_mode);
        try {
            tcp_server = std::make_shared<TCP_Server>(ip, port);
            std::thread thread(&Server::acceptConnections, this);
            thread.detach();
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::exit(1);
        }
    }

    void createRoom(const std::string& room_name) {
        room_manager.createRoom(room_name);
    }

    bool isUser(const std::string& name) {
        for (std::pair<const unsigned int, User>& value: users_list) {
            if (value.second.getName() == name) {
                return true;
            }
        }
        return false;
    }

    User& getUser(const std::string& name) {
        for (std::pair<const unsigned int, User>& value: users_list) {
            if (value.second.getName() == name) {
                return value.second;
            }
        }
    }
};
