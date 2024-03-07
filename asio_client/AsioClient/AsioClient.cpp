// AsioClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include "boost/asio.hpp"

using namespace boost::asio;

void start()
{
    io_service service;
    ip::tcp::socket socket(service);

    int32_t timeout = 1000;
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));

    boost::system::error_code ec;
    ip::tcp::endpoint ep(ip::address_v4::from_string("::1"), 8001);

    socket_base::keep_alive opt(true);
    socket.set_option(opt);
    socket.connect(ep, ec);

    if (ec.failed()) {
        std::cout << "connect failed" << std::endl;
    }

    Sleep(-1);
}

int main()
{
    std::thread th(start);
    Sleep(10000);
    th.join();
    return 0;
}