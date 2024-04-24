#include "Client/Client.h"

using dcsl::Client;

Client::Client(const std::string& user_name_, const std::string& ip, unsigned short port, short error_handler_mode) {
    user_name = user_name_;
    error_handler.setMode(error_handler_mode);
    try {
        tcp_client = std::make_shared<TCP_Client>(ip, port);
        sendMessage(user_name, -1);
    }
    catch (std::exception& e) {
        error_handler.log("Couldn't connect to the server");
    }
}

Message Client::getOutput() {
    return output;
}

int Client::recieveMessage() {
    try {
        std::vector<std::string> vec = tcp_client->recv();

        if (vec[0] == "-2") {
            return -1;
        }

        if (!vec[1].empty() && !vec[2].empty()) {
            output.command = std::stoi(vec[0]);
            output.msg = vec[1];
            output.sender = vec[2];
            return 1;
        }

        return 0;
    } catch (std::exception& e) {
        error_handler.log("The server has been shut down");
        return -1;
    }
}

void Client::sendMessage(const std::string& input, int command) {
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
