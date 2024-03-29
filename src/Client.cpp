#include "Client/Client.h"
#include <memory>

using namespace std;

// The ClientWrapper is used to asynchronously receive new messages from the server

class ClientWrapper {
private:
    shared_ptr<Client> client;
    Message old_output;
public:
    ClientWrapper(const std::string& login, const std::string& ip, int port) {
        client = make_shared<Client>(login, ip, port);
        thread thread(&ClientWrapper::getMessage, this);
        thread.detach();

        sendMessage();
    }
    void sendMessage() {
        std::string input;
        while (true) {
            cin >> input;
            if (input == "exit") {
                break;
            }
            else if (input == "/join") {
            	cout << "Room: ";
                cin >> input;
                client->sendMessage(input, 1);
            }
            else if (!input.empty() && input != "\n") {
                client->sendMessage(input);
            }
        }
    }

    [[noreturn]] void getMessage() {
        while (true) {
            Message output = client->getOutput();
            if (!(output == old_output) && !output.msg.empty()) {
                cout << output.sender << ": " << output.msg << endl;
            }
            old_output = output;
        }
    }
};

int main() {
    string input;

    cout << "Login: ";
    cin >> input;

    ClientWrapper client_wrapper(input, "127.0.0.1", 1234);

    return 0;
}
