#include "Server.h"
#include <iostream>

int main() {
    std::cout << "hi\n";

    Server server("127.0.0.1", 1234);

    server.createRoom("Room1");
    server.createRoom("Room2");
    server.createRoom("Room3");

    std::cout << "let's go!\n"; while (true) {}
}
