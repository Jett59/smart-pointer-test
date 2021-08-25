#include <iostream>
#include <string>

template <class T>
class SmartPointer
{
private:
    template <class V>
    class Pointer
    {
    public:
        V *ptr;
        int refs = 1;
        Pointer(V *ptr)
        {
            this->ptr = ptr;
        }
        ~Pointer()
        {
            delete ptr;
            ptr = nullptr;
        }
        bool operator==(Pointer other)
        {
            if (this->ptr == other.ptr)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };
    Pointer<T> *ptr = new Pointer<T>(nullptr);

public:
    SmartPointer(T *ptr)
    {
        this->ptr->ptr = ptr;
    }
    SmartPointer(SmartPointer &other)
    {
        delete ptr;
        this->ptr = other.ptr;
        this->ptr->refs++;
    }
    SmartPointer operator=(SmartPointer &other)
    {
        if (this->ptr == other.ptr)
        {
            return *this;
        }
        delete ptr;
        this->ptr = other.ptr;
        this->ptr->refs++;
        return *this;
    }
    ~SmartPointer()
    {
        this->ptr->refs--;
        if (this->ptr->refs == 0)
        {
            std::cout << "Deleting pointer!" << std::endl;
            delete ptr;
            ptr = nullptr;
        }
    }
    T *operator->()
    {
        return this->ptr->ptr;
    }
    T &operator*()
    {
        return *(this->ptr->ptr);
    }
};

void doSomethingWithMyPointer(SmartPointer<int> pointer)
{
    (*pointer)++;
}

int main(int argc, char *argv[])
{
    std::cout << "You should see a message below that the pointer was deleted:" << std::endl;
    int *rawPointer = new int;
    SmartPointer<int> ptr(rawPointer);
    *ptr = 50;
    std::cout << *ptr << std::endl;
    ptr = ptr;
    doSomethingWithMyPointer(ptr);
    std::cout << *ptr << std::endl;
    return 0;
}
