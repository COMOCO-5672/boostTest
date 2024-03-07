#include "boost/asio.hpp"
#include <iostream>
#include <thread>

using namespace boost::asio;

bool is_exit = false;

void start()
{
    io_service service;
    ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 8001);

    ip::tcp::acceptor accepter(service, ep, false);
    while (!is_exit)
    {
        boost::system::error_code ec;
        auto socket = new ip::tcp::socket(service);
        accepter.accept(*socket, ec);
    }
}

int main()
{
    std::thread th(start);
    system("pause");
    is_exit = true;
    if (th.joinable()) {
        th.join();
    }
    return 0;
}
