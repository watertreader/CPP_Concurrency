#include <thread>
#include <iostream>

/****  demonstrate that thread can take in a functor class object
       normally thread take in only value of an object

       if u wamt it to take in reference u have to use std::ref()
 */

class Functor{
    public: 
    void operator()(std::string& msg){
        for(int i =0; i< 10; i++)
        {
            std::cout << "from t1 " << msg << std::endl;
        }
    }
}


/* this */
void function_1()
{
    std::cout << "Printing function 1 " << "\n";
}

int main()
{
    std::cout << "Hardware Capability : "  << std::thread::hardware_concurrency() << "\n";


    Functor f1;
    // option 1 pass in a function
    // std::thread t1(function_1);   // thread t1 creation and start it running
    // option 2 pass in a functor
    // std::thread t1(f1()); 
    // option 3 passed in newly created object
    std::string s = "mr"
    std::thread t1(f1, std::ref(s)); 

   // if you decided to move t1 thread object into t2
    std::thread t2 = std::move(t1);

    try{
        for(int i =0; i < 100; i++)
        {
            std::cout << "printing from main " << "\n";
        }
    }catch (...) {
        t2.join();
        throw;
    }

    t1.join();   // main thread finish running

    t1.detach();  // thread run as separate process-- as a daemon

    if(t1.joinable()) // now t1 cannot be join asseparate process else it will crash
        t1.join();
        
    return 0;
}