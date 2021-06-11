#include <exception>
#include <string>

class ListException: public std::exception {
protected:
    std::string message{};
public:
    const char* what() const noexcept;
};

class ListExistsException: public ListException
{
private:
    std::string listName;
public:
    ListExistsException(std::string const& name);
};

class NoListSelectedException: public ListException
{
public:
    NoListSelectedException();
};

class BadProductException: public ListException
{
private:
    std::string productName;
public:
    BadProductException(std::string const& name);
};

class ProductNotOnListException: public ListException
{
private:
    std::string productName;
    std::string listName;
public:
    ProductNotOnListException(std::string const& lName, std::string const& prodName);
};

class NotEnoughArgsException: public ListException
{
private:
    int provided;
    int needed;
public:
    NotEnoughArgsException(int takes, int got);
};