#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <thread>
#include "../ErrorHandler.h"
#include "../Message.h"
#include "TCP_Client.h"

namespace dcsl {

    class Client {
    public:
        Client(const std::string& user_name_, const std::string& ip, unsigned short port, short error_handler_mode = 0);

        Message getOutput();
        void sendMessage(const std::string& input, int command = 0);
        int recieveMessage();

    private:
        ErrorHandler error_handler;
        Message output;
        std::shared_ptr<TCP_Client> tcp_client;
        std::string user_name;
    };

}
