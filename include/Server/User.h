class User {
private:
    tcp_connection::pointer socket;
    std::string             name;
    std::string             room_name;
public:
    User(std::string name_, tcp_connection::pointer socket_) {
        name = name_;
        socket = socket_;
    }
    void setRoom(std::string room_name_) {
        room_name = room_name_;
    }
    std::string getName() {
        return name;
    }
    std::string getRoom() {
        return room_name;
    }
    tcp_connection::pointer& getSocket() {
        return socket;
    }
};
