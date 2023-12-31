#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>
#include <thread>
#include "../Message.h"
#include "User.h"
#include "Room.h"
#include "RoomManager.h"


class Server {
private:
    RoomManager room_manager;
    std::vector<User> users_list;
    int server_sock;
    sockaddr_in server_addr;
    Message output;

    void clientHandler(int client_sock) {
        int user_index = -1;
        std::string user_room = "";
        while (true) {
            user_index = users_list.size() - 1;
            try {
                if (recieveMessage(client_sock, user_index, user_room) == -1) {
                    break;
                } else {
                    if (defineCommand(output, client_sock, user_room) == -1) {
                        break;
                    }
                }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    int recieveMessage(int& client_sock, int& user_index, std::string& user_room) {
        uint32_t size;
        if (recv(client_sock, &size, sizeof(size), 0) == -1) {
            throw std::runtime_error("Error receiving size");
        }
        size = ntohl(size);

        std::vector<std::string> vec(size);
        for (int i = 0; i < size; i++) {
            size_t value_len;
            auto recv_len = recv(client_sock, &value_len, sizeof(value_len), 0);
            if (recv_len == -1 || recv_len == 0) {
                std::cout << users_list[user_index].getName() << " disconnected!" << std::endl;
                if (user_index != -1) {
                    if (user_room != "") {
                        room_manager.getRoom(user_room).removeUser(users_list[user_index].getName());
                    }
                    users_list.erase(users_list.begin() + user_index);
                }
                return -1;
            }
            char value[value_len];
            if (recv(client_sock, value, value_len, 0) == -1) {
                throw std::runtime_error("Error receiving value");
            }
            vec[i] = value;
        }

        output.command = std::stoi(vec[0]);
        output.msg = vec[1];
        output.sender = vec[2];

        return 0;
    }

    int defineCommand(Message message, int& client_sock, std::string& user_room) {
        if (message.command == -1) {
            if (!isUser(message.sender)) {
                connect(message.sender, client_sock);
            } else {
                sendMessage("This User is Already Online!", client_sock, true);
                return -1;
            }
        }
        else if (message.command == 1) {
            auto t = joinRoom(message, user_room);
            if (t == -1) {
                sendMessage("This Room Does Not Exist!", client_sock);
            } else if (t == -2) {
                sendMessage("You Are Already In The Room!", client_sock);
            }
        }
        else {
            broadcast(message);
        }
        return 0;
    }

    int joinRoom(Message message, std::string& user_room) {
        bool is_user = false;
        for (auto& room: room_manager.getRooms()) {
            if (room.isUser(message.sender)) {
                is_user = true;
                break;
            }
        }
        if (!is_user) {
            for (auto& user: users_list) {
                if (user.getName() == message.sender) {
                    auto& get_room = room_manager.getRoom(message.msg);
                    std::string get_room_name = get_room.getName();
                    if (get_room_name != "") {
                        user.setRoom(get_room_name);
                        get_room.addUser(user);
                        user_room = get_room_name;
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
    void broadcast(Message message) {
        for (auto& room: room_manager.getRooms()) {
            if (room.isUser(message.sender)) {
                room.broadcast(message);
                break;
            }
        }
    }

    void sendMessage(std::string msg, int& client_socket, bool force_exit = false) {
        std::vector<std::string> vec(3);
        if (force_exit) {
            vec[0] = "-2";
        } else { vec[0] = "0"; }
        vec[1] = msg;
        vec[2] = "SERVER";

        uint32_t size = htonl(vec.size());
        if (send(client_socket, &size, sizeof(size), 0) == -1) {
            throw std::runtime_error("Error sending size");
        }

        for (auto& elem : vec) {
            char* value = new char[elem.length() + 1];
            strcpy(value, elem.c_str());

            size_t value_len = elem.length() + 1;
            if (send(client_socket, &value_len, sizeof(value_len), 0) == -1) {
                throw std::runtime_error("Error sending value");
            }
            if (send(client_socket, value, value_len, 0) == -1) {
                throw std::runtime_error("Error sending value");
            }
        }
    }

    void connect(std::string name, int socket) {
        User user(name, socket);
        users_list.push_back(user);
        std::cout << name << " connected" << '\n';
    }
public:
    Server(std::string ip, int port) {
        try {
            server_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (server_sock == -1) {
                throw std::runtime_error("Error creating server socket");
            }

            int yes = 1;
            if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
                perror("setsockopt");
            }

            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
            server_addr.sin_port = htons(port);
            if (bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                throw std::runtime_error("Error binding server socket");
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void waitForClient() {
        try {
            if (listen(server_sock, 1) == -1) {
                throw std::runtime_error("Error listening for connections");
            }
            sockaddr_in client_addr;
            memset(&client_addr, 0, sizeof(client_addr));
            socklen_t client_addr_len = sizeof(client_addr);
            int client_sock = accept(server_sock, (sockaddr*)&client_addr, &client_addr_len);
            if (client_sock == -1) {
                throw std::runtime_error("Error accepting client connection");
            }

            std::thread thread(&clientHandler, this, client_sock);
            thread.detach();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void createRoom(std::string room_name) {
        room_manager.createRoom(room_name);
    }

    bool isUser(std::string name) {
        for (auto& i: users_list) {
            if (i.getName() == name) {
                return true;
            }
        }
        return false;
    }
};
