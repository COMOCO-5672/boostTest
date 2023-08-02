#pragma once

#include <boost/fiber/all.hpp>
#include <boost/pool/pool.hpp>
#include <string>
#include <thread>
#include <cstdlib>

#include <iostream>


class AsyncWrapper {
public:
    void async_read(const std::string filename, std::function<void(const std::string &)> callback)
    {
        auto func = [=] {
            FILE *fp = fopen(filename.c_str(), "r");
            char buff[1024];
            std::string tmp;
            while (nullptr != fgets(buff, 1024, fp)) {
                tmp += buff;
            }
            fclose(fp);

            callback(tmp);
        };

        boost::asio::post(pool, func);
    }

    static void wait()
    {
        pool.join();
    }

protected:
    static boost::asio::thread_pool pool;

};

boost::asio::thread_pool AsyncWrapper::pool(2);

