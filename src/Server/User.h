class User {
private:
    std::string name;
    std::string room_name;
    int socket;
public:
    User(std::string name_, int socket_) {
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
    int getSocket() {
        return socket;
    }
};
