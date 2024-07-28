#include <fstream>
#include <iostream>
#include <mutex>


/* Apply the lock in sequence */
class LogFile
{
private:
    std::mutex m_mutex1;
    std::ofstream out;
public:
    LogFile(char *file)
    {
        // need destructor to close the file
        out.open(file);
    }
    void shared_printing2(std::string msg, int id)
    {
        //std::lock_guard<std::mutex> guard (m_mutex);   
        std::unique_lock<std::mutex> guard(m_mutex1);    // use unique_lock instead of lock_guard
        out << msg << " " << id << std::endl;   // this will cause a lock forever if 
                                                    // std::cout for some reason throw an exception and dun finish execution
                                                    // so a lock guard is needed
        locker.unlock();
    }
    // never return out to the outside 
    std::ofstream& getStream(){return out;}
    // never pass out as an argument to user
    void processf(void fun(std::ofstream&)){ fun(out);}
};