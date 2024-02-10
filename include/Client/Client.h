#include <iostream>
#include <vector>
#include <cstring>
#include <thread>
#include "../ErrorHandler.h"
#include "../Message.h"
#include "TCP_Client.h"

class Client {
private:
    std::shared_ptr<TCP_Client> tcp_client;
    ErrorHandler                error_handler;
    Message                     output;
    std::string                 user_name;

    int clientHandler() {
        while (true) {
            if (recieveMessage() == -1) {
                return 1;
            }
        }
    }

    int recieveMessage() {
        try {
            std::vector<std::string> vec = tcp_client->recv();

            if (vec[1] != "" && vec[2] != "") {
                output.command = std::stoi(vec[0]);
                output.msg = vec[1];
                output.sender = vec[2];
            }
            if (vec[0] == "-2") {
                return -1;
            } else {
                return 0;
            }
        } catch (std::exception& e) {
            std::cout << "The server has been shut down" << std::endl;
            return -1;
        }
    }
public:
    Client(std::string user_name_, std::string ip, unsigned short port, unsigned int error_handler_mode = 0) {
        user_name = user_name_;
        error_handler.setMode(error_handler_mode);
        try {
            tcp_client = std::make_shared<TCP_Client>(ip, port);
            sendMessage(user_name, -1);
            std::thread thread(&Client::clientHandler, this);
            thread.detach();
        }
        catch (std::exception& e) {
            std::cout << "Couldn't connect to the server\n";
        }
    }

    void sendMessage(std::string input, int command = 0) {
        try {
            std::vector<std::string> vec(3);
            vec[0] = std::to_string(command);
            vec[1] = input;
            vec[2] = user_name;
            tcp_client->send(vec);
        }
        catch (std::exception& e) {
            std::cout << "Couldn't connect to the server\n";
        }
    }
    Message getOutput() {
        return output;
    }
};
