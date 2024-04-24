#include "Client/TCP_Client.h"

TCP_Client::TCP_Client(const std::string& address, unsigned short port): resolver(io_context), socket(io_context) {
    socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(address), port));
}

std::vector<std::string> TCP_Client::recv() {
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

void TCP_Client::send(const std::vector<std::string>& message) {
    std::ostringstream oss;
    boost::archive::text_oarchive archive(oss);
    archive << message;
    std::string serializedData = oss.str();

    size_t size = serializedData.size();
    boost::asio::write(socket, boost::asio::buffer(&size, sizeof(size)));

    boost::asio::write(socket, boost::asio::buffer(serializedData));
}