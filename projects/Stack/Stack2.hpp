#include <iostream>

template <class T>
class Stack
{
    T *arr;
    int capacity;
    int count;

public:
    Stack()
    {
        arr = new T[1];
        capacity = 1;
        count = 0;
    }
    Stack(T x)
    {
        arr = new T[1];
        capacity = 1;
        count = 1;
        arr[0] = x;
    }
    void Push(T x)
    {
        if (count == capacity)
        {
            T *temp = new T[4 * capacity];
            for (int i = 0; i < count; i++)
                temp[i] = arr[i];
            capacity *= 4;
            delete[] arr;
            arr = temp;
        }
        arr[count] = x;
        count++;
    }
    T Pop()
    {
        if (Empty())
        {
            exit(EXIT_FAILURE);
        }
        count--;
        return arr[count];
    }
    T Top()
    {
        if (Empty())
            exit(EXIT_FAILURE);
        return arr[count - 1];
    }
    inline bool Empty() const
    {
        return count == 0;
    }
    friend std::ostream &operator<<(std::ostream &out, const Stack &st)
    {
        for (int i = 0; i < st.count; i++)
        {
            out << st.arr[i] << ' ';
        }
        return out;
    };
};