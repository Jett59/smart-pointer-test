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

    void deleteRef()
    {
        if (this->ptr != nullptr)
        {
            this->ptr->refs--;
            if (this->ptr->refs == 0)
            {
                std::cout << "Deleting pointer!" << std::endl;
                delete ptr;
                ptr = nullptr;
            }
        }
    }

public:
    SmartPointer(T *ptr)
    {
        this->ptr->ptr = ptr;
    }
    SmartPointer(SmartPointer &other)
    {
        this->ptr = other.ptr;
        this->ptr->refs++;
    }
    SmartPointer operator=(SmartPointer other)
    {
        if (this->ptr == other.ptr)
        {
            return *this;
        }
        deleteRef();
        this->ptr = other.ptr;
        this->ptr->refs++;
        return *this;
    }
    ~SmartPointer()
    {
        deleteRef();
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
    SmartPointer<int> ptr = new int;
    *ptr = 50;
    std::cout << *ptr << std::endl;
    doSomethingWithMyPointer(ptr);
    std::cout << *ptr << std::endl;
    ptr = new int;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "A new pointer:" << std::endl;
        SmartPointer<int> anotherPtr = new int;
        std::cout << "pointer about to go out of scope" << std::endl;
    }
    std::cout << "Exiting main function:" << std::endl;
    return 0;
}
