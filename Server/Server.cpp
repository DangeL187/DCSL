#include "Server.h"

int main() {
    Server server("127.0.0.1", 1234);
    
    server.createRoom("Room1");
    server.createRoom("Room2");
    server.createRoom("Room3");

    while (true) {
        server.waitForClient();
    }

    return 0;
}
