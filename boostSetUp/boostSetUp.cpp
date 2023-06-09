﻿// boostSetUp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "boost/thread/thread.hpp"
#include "boost/coroutine2/all.hpp"
#include "boost/fiber/all.hpp"
#include "../boostAsyncWrapper/AsyncWrapper.h"

#include <iostream>

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

int main()
{
    boost::coroutines2::coroutine<void>::push_type push(foo);

    std::cout << "1\n";
    push();
    std::cout << "2\n";
    push();
    std::cout << "3\n";
    push();

    boost::thread thread(&hello);
    thread.join();

    AsyncWrapper wrapper;
    std::string file = "./temp.txt";
    wrapper.async_read(file, [](const std::string &result) {
        printf("%s\n", result.c_str());
        });

    wrapper.wait();
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
