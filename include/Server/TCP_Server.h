#include <iostream>
#include <map>
#include <thread>

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#pragma comment(lib, "ws2_32")

using boost::asio::ip::tcp;

class tcp_connection;

class TCP_Server {
public:
    std::map<unsigned int, boost::shared_ptr<tcp_connection>> sockets;
    unsigned int counter = 0;

    explicit TCP_Server(const std::string& address, unsigned short port);

private:
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    bool next = true;

    [[noreturn]] void acceptHandler();

    void accept(boost::shared_ptr<tcp_connection>& connection, const boost::system::error_code& error);
};
