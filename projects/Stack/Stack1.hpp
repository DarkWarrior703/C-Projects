class Stack
{
private:
    int *arr;
    int capacity;
    int count;

public:
    Stack()
    {
        arr = new int[1];
        capacity = 1;
        count = 0;
    }
    Stack(int x)
    {
        arr = new int[1];
        arr[0] = x;
        count = 1;
        capacity = 1;
    }
    void Push(int x)
    {
        if (count == capacity)
        {
            int *temp = new int[4 * capacity];
            for (int i = 0; i < count; i++)
                temp[i] = arr[i];
            capacity *= 4;
            delete[] arr;
            arr = temp;
        }
        arr[count] = x;
        count++;
    }
    int Pop()
    {
        if (!Empty()){
            count--;
            return arr[count];
        }
        return -1;
    }
    int Top()
    {
        if (Empty())
            return -1;
        return arr[count - 1];
    }
    bool Empty() const
    {
        return count == 0;
    }
};