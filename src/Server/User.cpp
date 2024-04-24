#include "Server/User.h"

User::User(const std::string& name_, const boost::shared_ptr<tcp_connection>& socket_) {
    name = name_;
    socket = socket_;
}

std::string User::getName() {
    return name;
}

std::string User::getRoom() {
    return room_name;
}

boost::shared_ptr<tcp_connection>& User::getSocket() {
    return socket;
}

void User::setRoom(const std::string& room_name_) {
    room_name = room_name_;
}