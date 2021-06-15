#ifndef STACK_HEADER
#define STACK_HEADER

#include <vector>
#include <ostream>

template<typename Type>
class Stack
{
private:
    std::vector<Type> content;
public:
    Type pull();
    void push(Type const&);
    void push(Type&&);
    void read(std::ostream& stream);    
};

template<typename Type>
Type Stack<Type>::pull() {
    Type elem = std::move(content.back());
    content.pop_back();
    return elem;
}

template<typename Type>
void Stack<Type>::push(Type const& elem) {
    content.push_back(elem);
}

template<typename Type>
void Stack<Type>::push(Type&& elem) {
    content.push_back(std::move(elem));
}

template<typename Type>
void Stack<Type>::read(std::ostream& stream) {
    for (auto iter = content.rbegin(); iter != content.rend(); ++iter) {
        stream << *iter << std::endl;
    }
}
#endif