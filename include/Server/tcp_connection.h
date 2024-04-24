#ifndef DCSL_TCP_CONNECTION_H
#define DCSL_TCP_CONNECTION_H

#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <thread>
#pragma comment(lib, "ws2_32")

using boost::asio::ip::tcp;

class tcp_connection: public boost::enable_shared_from_this<tcp_connection> {
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context);
    tcp::socket& getSocket();
    std::vector<std::string> recv();
    void send(const std::vector<std::string>& message);

private:
    tcp::socket socket;

    explicit tcp_connection(boost::asio::io_context& io_context);
};

#endif //DCSL_TCP_CONNECTION_H
