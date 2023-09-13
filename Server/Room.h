class Room {
private:
    std::string room_name;
    std::vector<User> users_list;
public:
    Room(std::string room_name_ = "") {
        room_name = room_name_;
    }

    void addUser(User user) {
        users_list.push_back(user);
    }
    void removeUser(std::string user_name) {
        for (int i = 0; i < users_list.size(); i++) {
            if (users_list[i].getName() == user_name) {
                users_list.erase(users_list.begin() + i);
                break;
            }
        }
    }

    void broadcast(Message message) {
        for (auto& user: users_list) {
            if (user.getName() != message.sender) {
                sendMessage(message, user.getSocket());
            }
        }
    }
    void sendMessage(Message message, int client_socket) {
        std::vector<std::string> vec(3);
        vec[0] = std::to_string(message.command);
        vec[1] = message.msg;
        vec[2] = message.sender;

        uint32_t size = htonl(vec.size());
        if (send(client_socket, &size, sizeof(size), 0) == -1) {
            throw std::runtime_error("Error sending size");
        }

        for (auto& elem : vec) {
            char* value = new char[elem.length() + 1];
            strcpy(value, elem.c_str());

            size_t value_len = elem.length() + 1;
            if (send(client_socket, &value_len, sizeof(value_len), 0) == -1) {
                throw std::runtime_error("Error sending value");
            }
            if (send(client_socket, value, value_len, 0) == -1) {
                throw std::runtime_error("Error sending value");
            }
        }
    }

    std::string getName() {
        return room_name;
    }
    bool isUser(std::string user_name) {
        for (auto& user: users_list) {
            if (user.getName() == user_name) {
                return true;
            }
        }
        return false;
    }
    std::vector<User> getUsersList() {
        return users_list;
    }
};
