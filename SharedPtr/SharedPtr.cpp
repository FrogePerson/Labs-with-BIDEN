#include <iostream>

template<typename T>
class SharedPtr
{
public:
    SharedPtr(T *ptr)
    {
        this->ptr = ptr;
        this->count = new std::atomic_uint(1);
        std::cout << "create new pointer number of links: ";
        std::cout << *count << std::endl;
    }

    SharedPtr(const SharedPtr *r)
    {
        std::cout << "create pointer number of links: ";
        this->ptr = r->ptr;
        this->count = r->count;
        *count +=1;
        std::cout << *count << std::endl;
    }

    SharedPtr(SharedPtr&& r)
    {
        
        ptr = move(r.ptr);
        
        count = count = move(r.count);
        std::cout << "create new pointer number of links: ";
        std::cout << *count << std::endl;
    }

    ~SharedPtr()
    {
        *count -= 1;
        std::cout << "print number of links: ";
        std::cout << *count << std::endl;
        if (*count <= 0)
        {
            delete ptr;
            delete count;
            std::cout << "delete pointer" << std::endl;
        }
        else
        {
            std::cout << "Cant delete, link number: " << *count << std::endl;
        }
    }

    T& operator*()
    {
        return *ptr;
    }

    auto operator=(const SharedPtr *r)
    {
        std::cout << "Called overloaded = pointer operator" << std::endl;

        *count -= 1;
        this->count = nullptr;
        this->ptr = nullptr;

        this->ptr = r->ptr;
        this->count = r->count;
        *count +=1;
    }

    auto operator=(SharedPtr&& r)
    {
        if (ptr != r.ptr)
        {
            std::cout << "Called overloaded = pointer operator (rValue link)" << std::endl;

            ptr = move(r.ptr);
            count = move(r.count);
        }
        
    }

    void reset()
    {
        *count -= 1;
        std::cout << "reset pointer" << std::endl;
        this->count = new std::atomic_uint(1);
        this->ptr = nullptr;
    }

    void reset(T* ptr)
    {
        *count -= 1;
        std::cout << "reset pointer with T *ptr" << std::endl;
        this->count = new std::atomic_uint(1);
        this->ptr = ptr;
    }

    std::atomic_uint *count;
    T* ptr;
   
};

int main()
{
    SharedPtr<int> pointer1(new int(5));
    *pointer1 = 1654567;
    std::cout << "print pointer 1: ";
    std::cout << *pointer1 << std::endl;

    std::cout << " " << std::endl;

    SharedPtr<int> pointer2(&pointer1);
    std::cout << "print pointer 2: ";
    std::cout << *pointer2 << std::endl;

    std::cout << " " << std::endl;

    pointer2.reset();
    std::cout << "print number of links by pointer1: ";
    std::cout << *pointer1.count << std::endl;

    std::cout << " " << std::endl;

    pointer2.reset(new int(5));
    std::cout << "print number of links by pointer1: ";
    std::cout << *pointer1.count << std::endl;
    std::cout << "print pointer2: ";
    std::cout << *pointer2 << std::endl;

    std::cout << " " << std::endl;

    SharedPtr<int> pointer3(&pointer1);
    std::cout << "print pointer 3: ";
    std::cout << *pointer3 << std::endl;
    std::cout << "print number of links by pointer1: ";
    std::cout << *pointer1.count << std::endl;

    std::cout << " " << std::endl;

    pointer3 = &pointer2;
    std::cout << "print pointer 3: ";
    std::cout << *pointer3 << std::endl;
    std::cout << "print number of links by pointer1: ";
    std::cout << *pointer1.count << std::endl;
    std::cout << "print number of links by pointer2: ";
    std::cout << *pointer2.count << std::endl;

    std::cout << " " << std::endl;
    std::cout << "Calls destructurs: " << std::endl;
    std::cout << " " << std::endl;

    return 0;
}
