#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#pragma comment(lib, "ws2_32")

class Message;
class tcp_connection;
class User;

class Room {
public:
    explicit Room(const std::string& room_name_ = "");

    void addUsername(const std::string& username);
    void broadcast(const Message& message, const std::map<unsigned int, User>& users_list);
    bool isUser(const std::string& username);
    std::string getName();
    std::vector<std::string> getUsernamesList();
    void removeUsername(const std::string& username);

private:
    std::string room_name;
    std::vector<std::string> usernames_list;

    void sendMessage(const Message& message, boost::shared_ptr<tcp_connection>& connection);
};
