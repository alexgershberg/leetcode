//
// Created by alexgershberg on 02/02/23.
//

//https://leetcode.com/problems/print-foobar-alternately/

#include <atomic>
#include <functional>
#include <thread>
#include <iostream>
#include <mutex>

class FooBar
{
private:
    int n;

    std::mutex fooMutex;
    std::mutex barMutex;

public:
    FooBar(int n)
    {
        this->n = n;
        barMutex.lock();
    }

    void foo(std::function<void()> printFoo)
    {
        for (int i = 0; i < n; i++)
        {
            fooMutex.lock();
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            barMutex.unlock();
        }
    }

    void bar(std::function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {
            barMutex.lock();
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            fooMutex.unlock();
        }
    }
};

int main()
{
    int inp;
    std::cin >> inp;
    FooBar fb(inp);

    std::thread f(&FooBar::foo, &fb, []
    { std::cout << "foo"; });
    std::thread b(&FooBar::bar, &fb, []
    { std::cout << "bar"; });

    f.join();
    b.join();
}
