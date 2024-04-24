#include <boost/shared_ptr.hpp>

#pragma comment(lib, "ws2_32")

class tcp_connection;

class User {
public:
    User(const std::string& name_, const boost::shared_ptr<tcp_connection>& socket_);
    std::string getName();
    std::string getRoom();
    boost::shared_ptr<tcp_connection>& getSocket();
    void setRoom(const std::string& room_name_);

private:
    std::string                         name;
    std::string                         room_name;
    boost::shared_ptr<tcp_connection>   socket;
};
