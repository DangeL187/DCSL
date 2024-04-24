#include "Server/TCP_Server.h"

#include "Server/tcp_connection.h"

TCP_Server::TCP_Server(const std::string& address, unsigned short port):
    acceptor(io_context, tcp::endpoint(boost::asio::ip::address::from_string(address), port))
{
    std::thread thread(&TCP_Server::acceptHandler, this);
    thread.detach();
}

void TCP_Server::acceptHandler() {
    while (true) {
        if (next) {
            next = false;
            tcp_connection::pointer new_connection = tcp_connection::create(io_context);
            acceptor.async_accept(new_connection->getSocket(),
                                  boost::bind(&TCP_Server::accept, this, new_connection,
                                              boost::asio::placeholders::error));
        }
        io_context.run();
    }
}

void TCP_Server::accept(tcp_connection::pointer& connection, const boost::system::error_code& error) {
    if (!error) {
        sockets.insert({counter, connection});
    }
    next = true;
}