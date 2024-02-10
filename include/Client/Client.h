#include <iostream>
#include <vector>
#include <cstring>
#include <thread>
#include "../ErrorHandler.h"
#include "../Message.h"
#include "TCP_Client.h"

class Client {
private:
    ErrorHandler                error_handler;
    Message                     output;
    std::shared_ptr<TCP_Client> tcp_client;
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

            if (!vec[1].empty() && !vec[2].empty()) {
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
            error_handler.log("The server has been shut down");
            return -1;
        }
    }
public:
    Client(const std::string& user_name_, const std::string& ip, unsigned short port, short error_handler_mode = 0) {
        user_name = user_name_;
        error_handler.setMode(error_handler_mode);
        try {
            tcp_client = std::make_shared<TCP_Client>(ip, port);
            sendMessage(user_name, -1);
            std::thread thread(&Client::clientHandler, this);
            thread.detach();
        }
        catch (std::exception& e) {
            error_handler.log("Couldn't connect to the server");
        }
    }

    void sendMessage(const std::string& input, int command = 0) {
        try {
            std::vector<std::string> vec(3);
            vec[0] = std::to_string(command);
            vec[1] = input;
            vec[2] = user_name;
            tcp_client->send(vec);
        }
        catch (std::exception& e) {
            error_handler.log("Couldn't connect to the server");
        }
    }
    Message getOutput() {
        return output;
    }
};
