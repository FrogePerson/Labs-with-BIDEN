#include <iostream>
#include <thread>
#include <chrono>
#include <C:\Users\GF\source\repos\StreamHeH\StreamHeH\picosha2.h>
#include <regex>
#include <conio.h>
#include <windows.h>
#include <mutex>
//#include <boost/log/trivial.hpp>

std::mutex mtx;

void Log(std::string hash, std::vector<unsigned char> vek)
{
    mtx.lock();

    std::cout<< "hash :" << hash << std::endl;
    std::cout << "vector :" << hash << std::endl;
    std::cout << std::endl;

    mtx.unlock();
}

std::vector<unsigned char> GetVector(int phase)
{
    std::vector<unsigned char> vec;
    int size = 9;
    for (int i = 0; i < size; i++)
    {
        vec.push_back(std::rand()+phase);
    }
    return vec;
}

void GetHash(int phase)
{
    std::vector<unsigned char> vek { GetVector(phase)};
    const std::vector<unsigned char> data_vector{ vek }; // вектор
    const std::string hash = picosha2::hash256_hex_string(data_vector);
    std::string pattern = ".{60}0000$";
    std::regex regex(pattern);
    if (std::regex_match(hash, regex))
    {
        Log(hash,vek);
    }
}

void FindHesh(int phase)
{

    for (int i = 0; true; i++)
    {
        GetHash(phase);
    }
}

int main()
{

    std::thread th1(FindHesh,0);
    std::thread th2(FindHesh,1000);
    std::thread th3(FindHesh,100000);
    th1.detach();
    th2.detach();
    th3.detach();
    

    while (true)
    {
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
        {
            if (_kbhit())
            {
                char key = _getch();
                if (key == 'c' || key == 'C')
                {
                    break;
                }
            }
        }
    }
    
    
}

