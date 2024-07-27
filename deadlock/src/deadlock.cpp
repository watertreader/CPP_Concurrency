#include <thread>
#include <iostream>
#include <stdio.h>
#include <ostream>
#include <string>

#include <mutex>

/* this is to demonstrate deadlock in printing*/
/* main thread is waiting for guard1 to be release while t1 is waiting for guard2 to be released*/


#include "management_class.h"

std::mutex mu;




void function_1(LogFile& logger)
{
    for(int i = 0; i >= -100; i--)
        logger.shared_printing2(std::string("from t1"), i);
}


int main()
{
    std::string fn ="logfile.txt";
    LogFile log(const_cast<char*> (fn.c_str()));
    std::thread t1(function_1, std::ref(log));   // thread t1 creation and start it running

    for(int i = 0; i <= 100; i++)
               log.shared_printing3(std::string("from tmain"), i);

    t1.join();   // main thread finish running

        
    return 0;
}