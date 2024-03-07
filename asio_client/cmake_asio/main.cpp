#include "asio.hpp"

using namespace asio;

void start()
{
    io_service service;
    ip::tcp::socket socket(service);

    int32_t timeout = 1000;
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
    setsockopt(socket.native_handle(), SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(timeout));

    asio::error_code ec;
    ip::tcp::endpoint ep(ip::address_v4::from_string("::1"), 8001);

    socket_base::keep_alive opt(true);
    socket.set_option(opt);
    socket.connect(ep, ec);

    Sleep(-1);
}

int main()
{
    start();
    system("pause");
    return 0;
}