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
    TCP_Client(std::string address, unsigned short port):
        resolver(io_context),
        socket(io_context)
    {
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(address), port));
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

    void send(const std::vector<std::string> message) {
        std::ostringstream oss;
        boost::archive::text_oarchive archive(oss);
        archive << message;
        std::string serializedData = oss.str();

        size_t size = serializedData.size();
        boost::asio::write(socket, boost::asio::buffer(&size, sizeof(size)));

        boost::asio::write(socket, boost::asio::buffer(serializedData));
    }
private:
    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::socket socket;
};
