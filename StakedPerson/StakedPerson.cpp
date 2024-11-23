#include <iostream>

template <typename T>
struct StackElement
{
    T value;
    StackElement<T>* previous;
};

template <typename T>
class Stack
{
public:
    
    void push(T&& value)
    {
        StackElement<T>* newElemet = new StackElement<T>;
        newElemet->value = value;
        newElemet->previous = elemet;
        this->elemet = newElemet;
        size += 1;
    }
    void push(T& value)
    {
        StackElement<T>* newElemet = new StackElement<T>;
        newElemet->value = value;
        newElemet->previous = elemet;
        this->elemet = newElemet;
        size += 1;
    }
    template <typename ... Args>
    void push_emplace(Args&&... value)
    {
        for (auto element : { value... })
        {
            this->push(element);
        }
    }
    void pop()
    {
        this->prevElemet = this->elemet;
        this->elemet = elemet->previous;
        delete(this->prevElemet);
    }
    const T& head() const { return elemet->value; };
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            if (elemet != nullptr)
            {
                std::cout << elemet->value << std::endl;
            }
            this->prevElemet = this->elemet;
            this->elemet = elemet->previous;
            delete(this->prevElemet);
        }
    }
    ~Stack()
    {
        for (int i = 0; i < size; i++)
        {
            this->prevElemet = this->elemet;
            this->elemet = elemet->previous;
            delete(this->prevElemet);
            if (i == (size - 1))
            {
                delete(this->prevElemet);
                delete(this->elemet);
            }
        }

    }

    StackElement<T>* elemet;
    StackElement<T>* prevElemet;
    int size = 0;
};


int main()
{
    Stack<int> newStack;
    int a = 1;
    newStack.push(4);
    int b = 2;
    newStack.push(b);
    newStack.pop();
    newStack.push_emplace(11, 22, 33, 44, 555);
    std::cout << newStack.head() << std::endl;
    newStack.print();
}

