#include <thread>
#include <iostream>

void function_1()
{
    std::cout << "Printing function 1 " << "\n";
}

int main()
{
    std::thread t1(function_1);   // thread t1 creation and start it running
    t1.join();   // main thread finish running

    t1.detach();  // thread run as separate process-- as a daemon

    if(t1.joinable()) // now t1 cannot be join asseparate process else it will crash
        t1.join();
        
    return 0;
}