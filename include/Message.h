struct Message {
    int command = 0;
    std::string msg;
    std::string sender;

    bool operator==(const Message& other) const {
        return (this->command == other.command && this->msg == other.msg && this->sender == other.sender);
    }
};
