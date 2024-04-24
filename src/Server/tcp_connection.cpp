#include "Server/tcp_connection.h"

tcp_connection::tcp_connection(boost::asio::io_context &io_context): socket(io_context) {}

tcp_connection::pointer tcp_connection::create(boost::asio::io_context& io_context) {
    return pointer(new tcp_connection(io_context));
}

tcp::socket& tcp_connection::getSocket() {
    return socket;
}

std::vector<std::string> tcp_connection::recv() {
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

void tcp_connection::send(const std::vector<std::string>& message) {
    std::ostringstream oss;
    boost::archive::text_oarchive archive(oss);
    archive << message;
    std::string serializedData = oss.str();

    size_t size = serializedData.size();
    boost::asio::write(socket, boost::asio::buffer(&size, sizeof(size)));

    boost::asio::write(socket, boost::asio::buffer(serializedData));
}