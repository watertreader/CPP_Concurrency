#include <thread>
#include <iostream>
#include <stdio.h>
#include <ostream>
#include <string>

#include <mutex>

/* this is to demonstrate deadlock in printing*/
/* main thread is waiting for guard1 to be release while t1 is waiting for guard2 to be released*/
/* the way to unlocked this is to make sure mutex are locked in the same sequence*/


/* Avoiding deadlock 
1) Always  strive to use single mutex in one function
2) Avoid locking a mutex and then proceed to call other api function (like other library or some hardware related function)
-----this is to prevent after you lock and then calling other api which might contain another mutex and create deadlock
----- hardware might take long and unpredictable time and might have exception
3) if need to use more than one lock use std::lock to lock both function
4) if do not have standard library, always lock two or more locks in same sequence in all function

Locking Granularity
1) fine -grained lock:locks only a small amount of data
2) coarse-grained lock: locks large amount of data

*/

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