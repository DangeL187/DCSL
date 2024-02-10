class Room {
private:
    std::string room_name;
    std::vector<std::string> usernames_list;

    void sendMessage(Message message, tcp_connection::pointer connection) {
        std::vector<std::string> vec(3);
        vec[0] = std::to_string(message.command);
        vec[1] = message.msg;
        vec[2] = message.sender;

        connection->send(vec);
    }
public:
    Room(std::string room_name_ = "") {
        room_name = room_name_;
    }

    void broadcast(Message message, std::map<unsigned int, User>  users_list) {
        for (std::pair<const unsigned int, User>& value: users_list) {
            User& user = value.second;
            if (isUser(user.getName()) && user.getName() != message.sender) {
                sendMessage(message, user.getSocket());
            }
        }
    }

    void addUsername(std::string username) {
        usernames_list.push_back(username);
    }
    void removeUsername(std::string username) {
        for (int i = 0; i < usernames_list.size(); i++) {
            if (usernames_list[i] == username) {
                usernames_list.erase(usernames_list.begin() + i);
                break;
            }
        }
    }
    bool isUser(std::string username) {
        for (std::string& name: usernames_list) {
            if (name == username) {
                return true;
            }
        }
        return false;
    }
    std::vector<std::string> getUsernamesList() {
        return usernames_list;
    }

    std::string getName() {
        return room_name;
    }
};
