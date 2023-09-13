#include "Client.h"
#include <memory>

using namespace std;

class ClientWrapper {
private:
    shared_ptr<Client> client;
    Message old_output;
public:
    ClientWrapper(std::string login) {
        client = make_shared<Client>(login);
        thread thread(&getMessage, this);
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
            else if (input != "" && input != "\n") {
                client->sendMessage(input);
            }
        }
    }
    void getMessage() {
        while (true) {
            Message output = client->getOutput();
            if (!(output == old_output)) {
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

    ClientWrapper client_wrapper(input);

  return 0;
}
