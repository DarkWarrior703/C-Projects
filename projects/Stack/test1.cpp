/* Basic testing of the stack */

#include "Stack1.hpp"
#include <iostream>

int main()
{
    Stack st(21);
    st.Push(4);
    st.Push(10);
    st.Push(20);
    int x = st.Top();
    std::cout << x << '\n';
    st.Pop();
    std::cout << st.Pop() << '\n';
    std::cout << st.Pop() << '\n';
    std::cout << st.Pop() << '\n';
    std::cout << st.Empty() << '\n';
    std::cout << st.Pop() << '\n';
}