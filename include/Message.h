#include <string>

struct Message {
    int command = 0;
    std::string msg;
    std::string sender;

    bool operator==(const Message& other) const;
};
