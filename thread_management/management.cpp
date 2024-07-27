#include <thread>
#include <iostream>


/* this example is used to demonstrate the management of a thread 
 --- how to pass function into a thread
 --- once a thread is detached from main process, you cannot call a join to end it
 */

void function_1()
{
    std::cout << "Printing function 1 " << "\n";
}

int main()
{
    std::thread t1(function_1);   // thread t1 creation and start it running

    try{
        for(int i =0; i < 100; i++)
        {
            std::cout << "printing from main " << "\n";
        }
    }catch (...) {
        t1.join();
        throw;
    }

    t1.join();   // main thread finish running

    t1.detach();  // thread run as separate process-- as a daemon

    if(t1.joinable()) // now t1 cannot be join asseparate process else it will crash
        t1.join();
        
    return 0;
}