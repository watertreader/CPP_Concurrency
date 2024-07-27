#include <thread>
#include <iostream>
#include <stdio.h>
#include <ostream>
#include <string>

#include <mutex>

/* this is to demonstrate uses of mutex in printing*/


/* thread safe -  would operate in the manner as expected */

/* to prevent data race
1) use mutex to synchronise data access
2) never leak a handle of data to the outside
3) design appropriately to ensure thread safe 
    -- combine function or separate function accordingly
*/

#include "management_class.h"

std::mutex mu;




void function_1(LogFile& logger)
{
    for(int i = 0; i >= -100; i--)
        logger.shared_printing2(std::string("from t1"), i);
}

// int main()
// {
//     std::thread t1(function_1);   // thread t1 creation and start it running

//     for(int i = 0; i <= 100; i++)
//                shared_printing(std::string("from tmain"), i);

//     t1.join();   // main thread finish running

        
//     return 0;
// }

int main()
{
    std::string fn ="logfile.txt";
    LogFile log(const_cast<char*> (fn.c_str()));
    std::thread t1(function_1, std::ref(log));   // thread t1 creation and start it running

    for(int i = 0; i <= 100; i++)
               log.shared_printing2(std::string("from tmain"), i);

    t1.join();   // main thread finish running

        
    return 0;
}