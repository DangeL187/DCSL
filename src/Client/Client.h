#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "../Message.h"

class Client {
private:
    std::string user_name;
    int sock;
    bool full_stop = false;
    sockaddr_in server_addr;
    Message output;

    void clientHandler(int socket) {
        bool stop = false;
        while (true) {
            try {
                if (recieveMessage(socket) == -1) {
                    stop = true;
                }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            if (stop) { break; }
        }
    }

    int recieveMessage(int socket) {
        uint32_t size;
        if (recv(socket, &size, sizeof(size), 0) == -1) {
            throw std::runtime_error("Error receiving size");
        }
        size = ntohl(size);

        std::vector<std::string> vec(size);
        for (int i = 0; i < size; i++) {
            size_t value_len;
            auto recv_len = recv(socket, &value_len, sizeof(value_len), 0);
            if (recv_len == -1 || recv_len == 0) {
                std::cout << "Error Connecting to the Server\n";
                break;
                return -1;
            }
            char value[value_len];
            if (recv(socket, value, value_len, 0) == -1) {
                throw std::runtime_error("Error receiving value");
            }
            vec[i] = value;
        }

        output.command = std::stoi(vec[0]);
        output.msg = vec[1];
        output.sender = vec[2];

        if (vec[0] == "-2") {
            return -1;
        } else {
            return 0;
        }
    }
public:
    Client(std::string user_name_, std::string ip, int port) {
        user_name = user_name_;
        try {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == -1) {
                throw std::runtime_error("Error creating socket");
            }

            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port);
            if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
                throw std::runtime_error("Error converting address");
            }
            if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                throw std::runtime_error("Error connecting to the server");
            }

            sendMessage(user_name, -1);

            std::thread thread(&clientHandler, this, sock);
            thread.detach();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void sendMessage(std::string input, int command = 0) {
        std::vector<std::string> vec(3);
        vec[0] = std::to_string(command);
        vec[1] = input;
        vec[2] = user_name;

        uint32_t size = htonl(vec.size());
        if (send(sock, &size, sizeof(size), 0) == -1) {
            throw std::runtime_error("Error sending size");
        }

        for (auto& elem : vec) {
            char* value = new char[elem.length() + 1];
            strcpy(value, elem.c_str());

            size_t value_len = elem.length() + 1;
            auto recv_len = send(sock, &value_len, sizeof(value_len), 0);
            if (recv_len == -1 || recv_len == 0) {
                std::cout << "Error Connecting to the Server\n";
                break;
            }
            if (send(sock, value, value_len, 0) == -1) {
                throw std::runtime_error("Error sending value");
            }
        }
    }
    Message getOutput() {
        return output;
    }
};
