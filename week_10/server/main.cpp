#include <iostream>
#include <boost/asio.hpp>

std::string read_data(boost::asio::ip::tcp::socket & socket)
{
    const std::size_t length = 10;
    char buffer[length];
    boost::asio::read(socket, boost::asio::buffer(buffer, length));
    return std::string(buffer, length);
}

void write_data(boost::asio::ip::tcp::socket & socket, std::string data)
{
    boost::asio::write(socket, boost::asio::buffer(data));
}

std::string read_data_until(boost::asio::ip::tcp::socket & socket)
{
    boost::asio::streambuf buffer;

    boost::asio::read_until(socket, buffer, '!');

    std::string message;

    // Because buffer 'buf' may contain some other data
    // after '\n' symbol, we have to parse the buffer and
    // extract only symbols before the delimiter.
    std::istream input_stream(&buffer);
    std::getline(input_stream, message, '!');

    return message;
}

int main(int argc, char ** argv)
{
    const std::size_t size = 30;

    auto port = 3333;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

    boost::asio::io_service io_service;

    try
    {
        boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

        acceptor.bind(endpoint);

        acceptor.listen(size);

        boost::asio::ip::tcp::socket socket(io_service);

        acceptor.accept(socket);

        std::thread thread_read ([&](){
            bool f = true;
            while (socket.is_open()) {
                std::string s = read_data_until(socket);
                if (s == "exit"){
                    socket.close();
                    std::cout << "+" << std::endl;
                }
                else {
                    char str[100];
                    strcpy(str, s.c_str());
                    std::string name = strtok (str,":");
                    std::string message = strtok (NULL, ":");
                    std::cout << "Message from " << name << ": " << message << std::endl;
                }
            }
        });

        std::thread thread_write ([&](){
            bool f = true;
            std::string data;
            while (socket.is_open()) {
                std::cin >> data;
                if (data == "exit!") {
                    socket.close();
                    std::cout << "+" << std::endl;
                }
                write_data(socket, data);
            }
        });

        thread_read.join();
        thread_write.join();
    }
    catch (boost::system::system_error & e)
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

        return e.code().value();
    }

    return EXIT_SUCCESS;
}