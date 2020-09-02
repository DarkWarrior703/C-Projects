/* A short test on Stack2.hpp */

#include "Stack2.hpp"
#include <iostream>

int main()
{
    Stack<std::string> st("World");
    st.Push("Hello");
    std::cout << st.Pop() << ", ";
    std::cout << st.Pop() << "!\n";
}
