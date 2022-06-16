#include <iostream>
#include <thread>
#include <chrono>
#include "thread_pool.h"
using namespace std;

int main()
{

    threadPool pool;
    
    pool.start();

    std::this_thread::sleep_for(chrono::seconds(5));

    return 0;
}