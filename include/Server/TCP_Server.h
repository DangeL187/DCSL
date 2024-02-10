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

    static pointer create(boost::asio::io_context& io_context) {
        return pointer(new tcp_connection(io_context));
    }

    tcp::socket& getSocket() {
        return socket;
    }

    std::vector<std::string> recv() {
        size_t size;
        boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));

        std::vector<char> serializedData(size);
        boost::asio::read(socket, boost::asio::buffer(serializedData));

        std::istringstream iss(std::string(serializedData.begin(), serializedData.end()));
        boost::archive::text_iarchive archive(iss);
        std::vector<std::string> lines;
        archive >> lines;

        return lines;
    }

    void send(const std::vector<std::string>& message) {
        std::ostringstream oss;
        boost::archive::text_oarchive archive(oss);
        archive << message;
        std::string serializedData = oss.str();

        size_t size = serializedData.size();
        boost::asio::write(socket, boost::asio::buffer(&size, sizeof(size)));

        boost::asio::write(socket, boost::asio::buffer(serializedData));
    }

private:
    explicit tcp_connection(boost::asio::io_context& io_context): socket(io_context) {}

    tcp::socket socket;
};

class TCP_Server {
public:
    std::map<unsigned int, tcp_connection::pointer> sockets;
    unsigned int counter = 0;

    explicit TCP_Server(const std::string& address, unsigned short port):
        acceptor(io_context, tcp::endpoint(boost::asio::ip::address::from_string(address), port))
    {
        std::thread thread(&TCP_Server::acceptHandler, this);
        thread.detach();
    }
private:
    boost::asio::io_context io_context;
    tcp::acceptor acceptor;
    bool next = true;

    [[noreturn]] void acceptHandler() {
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

    void accept(tcp_connection::pointer& connection, const boost::system::error_code& error) {
        if (!error) {
            connection->send({"0", "WELCOME!", "SERVER"});
            sockets.insert({counter, connection});
        }
        next = true;
    }
};
