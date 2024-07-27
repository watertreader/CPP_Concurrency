#include <fstream>
#include <iostream>

class Stack
{
private:
    int* _data;
    std::mutex _mu;
public:
        void pop();
        int &top();
};



class LogFile
{
private:
    std::mutex m_mutex1;
    std::mutex m_mutex2;
    std::ofstream out;
public:
    LogFile(char *file)
    {
        // need destructor to close the file
        out.open(file);
    }
    void shared_printing2(std::string msg, int id)
    {
        std::lock_guard<std::mutex> guard1(m_mutex1);   
        std::lock_guard<std::mutex> guard2 (m_mutex2);   
        out << msg << " " << id << std::endl;   // this will cause a lock forever if 
                                                    // std::cout for some reason throw an exception and dun finish execution
                                                    // so a lock guard is needed
        
    }

    void shared_printing3(std::string msg, int id)
    {
        std::lock_guard<std::mutex> guard2 (m_mutex1);   
        std::lock_guard<std::mutex> guard1 (m_mutex2);   

        out << msg << " " << id << std::endl;   // this will cause a lock forever if 
                                                    // std::cout for some reason throw an exception and dun finish execution
                                                    // so a lock guard is needed
        
    }
    // never return out to the outside 
    std::ofstream& getStream(){return out;}
    // never pass out as an argument to user
    void processf(void fun(std::ofstream&)){ fun(out);}
};