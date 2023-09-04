#include "Client.h"

using namespace std;

int main() {
    string input;
    Message output;

    cout << "Login: ";
    cin >> input;

    Client client(input);

    while (true) {
        cin >> input;
        if (input == "exit") {
            break;
        }
        else if (input == "/join") {
        	cout << "Room: ";
            cin >> input;
            client.sendMessage(input, 1);
        }
        else if (input != "" && input != "\n") {
            client.sendMessage(input);
        }
    }

  return 0;
}
