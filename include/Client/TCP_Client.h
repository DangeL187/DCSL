#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#ifdef _WIN32
    #pragma comment(lib, "ws2_32")
#endif

using boost::asio::ip::tcp;

class TCP_Client {
public:
    TCP_Client(const std::string& address, unsigned short port);

    std::vector<std::string> recv();
    void send(const std::vector<std::string>& message);

private:
    boost::asio::io_context io_context;
    tcp::resolver           resolver;
    tcp::socket             socket;
};
