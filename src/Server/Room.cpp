#include "Message.h"
#include "Server/Room.h"
#include "Server/User.h"
#include "Server/tcp_connection.h"

Room::Room(const std::string& room_name_) {
    room_name = room_name_;
}

void Room::addUsername(const std::string& username) {
    usernames_list.push_back(username);
}

void Room::broadcast(const Message& message, const std::map<unsigned int, User>& users_list) {
    for (std::pair<const unsigned int, User> value: users_list) {
        User& user = value.second;
        if (isUser(user.getName()) && user.getName() != message.sender) {
            sendMessage(message, user.getSocket());
        }
    }
}

std::string Room::getName() {
    return room_name;
}

std::vector<std::string> Room::getUsernamesList() {
    return usernames_list;
}

bool Room::isUser(const std::string& username) {
    for (std::string& name: usernames_list) {
        if (name == username) {
            return true;
        }
    }
    return false;
}

void Room::removeUsername(const std::string& username) {
    for (int i = 0; i < usernames_list.size(); i++) {
        if (usernames_list[i] == username) {
            usernames_list.erase(usernames_list.begin() + i);
            break;
        }
    }
}

void Room::sendMessage(const Message& message, tcp_connection::pointer& connection) {
    std::vector<std::string> vec(3);
    vec[0] = std::to_string(message.command);
    vec[1] = message.msg;
    vec[2] = message.sender;

    connection->send(vec);
}