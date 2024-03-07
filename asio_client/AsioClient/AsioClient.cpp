// AsioClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "boost/asio.hpp"
#include <thread>
#include <iostream>

using namespace boost::asio;

static bool is_exit = false;

void start()
{
    io_service service;
    ip::tcp::socket socket(service);

    int32_t timeout = 1000;
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));

    boost::system::error_code ec;
    ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 8001);

    socket.connect(ep, ec);

    socket_base::keep_alive opt(true);
    socket.set_option(opt);

    if (ec.failed()) {
        std::cout << "connect failed" << std::endl;
    }
    while (!is_exit) {
        std::this_thread::sleep_for(std::chrono::milliseconds(0));
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