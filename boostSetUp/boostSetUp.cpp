// boostSetUp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "boost/asio.hpp"
#include "boost/thread/thread.hpp"
#include "boost/coroutine2/all.hpp"
#include "boost/fiber/all.hpp"
#include "../boostAsyncWrapper/AsyncWrapper.h"
#include "../boostLog/boostLog.h"

#include <iostream>
#include <atomic>

#include <future>

#pragma comment(lib, "libboost_thread-vc143-mt-gd-x64-1_81.lib")
#pragma comment(lib, "libboost_coroutine-vc143-mt-gd-x64-1_81.lib")
#pragma comment(lib, "libboost_fiber-vc143-mt-gd-x64-1_81.lib")

void hello()
{
    std::cout << "hello world" << std::endl;
}

class X {
public:
    X()
    {
        std::cout << "x()\n";
    }

    ~X()
    {
        std::cout << "~x()\n";
        system("pause");
    }
};

void foo(boost::coroutines2::coroutine<void>::pull_type &pull)
{
    X x;
    std::cout << "a\n";
    pull();
    std::cout << "b\n";
    pull();
    std::cout << "c\n";
}

int fun(int x, std::promise<int> &p)
{
    x++;
    x *= 10;
    p.set_value(x);
    std::cout << "thread_id:" << std::this_thread::get_id() << std::endl;
    return x;
}

int main()
{
   /* boost::coroutines2::coroutine<void>::push_type push(foo);

    std::cout << "1\n";
    push();
    std::cout << "2\n";
    push();
    std::cout << "3\n";
    push();*/

    /*std::cout << "main thread" << std::this_thread::get_id() << "\r\n" << std::endl;
    AsyncWrapper wrapper;
    std::string file = "./temp.txt";
    wrapper.async_read(file, [](const std::string &result) {
        std::cout << "thread_id" << std::this_thread::get_id() << "\r\n" << std::endl;
        printf("%s\n", result.c_str());
        });

    wrapper.wait();

    boost::thread thread(&hello);
    thread.join();*/

    std::promise<int> p;
    auto fu = p.get_future();
    std::thread t(fun, 1, std::ref(p));
    int id = fu.get();
    std::cout << "get value:" << id << "\r\n" << std::endl;
    std::cout << "main_thread:" << std::this_thread::get_id() << std::endl;

    std::atomic<int> fo(1);
    fo.store(10, std::memory_order_seq_cst);

    std::system("pause");

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
