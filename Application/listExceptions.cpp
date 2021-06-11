#include "listExceptions.h"

const char* ListException::what() const noexcept {
    return message.c_str();
}

ListExistsException::ListExistsException(std::string const& name): listName(name) {
    message = "List named \"" + listName + "\" alreade exists";
}

NoListSelectedException::NoListSelectedException() {
    message = "No list selected";
}

BadProductException::BadProductException(std::string const& name): productName(name) {
    message = "Product named \"" + productName + "\" does not exists";
}

ProductNotOnListException::ProductNotOnListException(std::string const& lName, std::string const& prodName): listName(lName), productName(prodName) {
    message = productName + " is not on " + listName;
}

NotEnoughArgsException::NotEnoughArgsException(int takes, int got): provided(got), needed(takes) {
    message = "Not enough arguments - " + std::to_string(provided) + " were given, " + std::to_string(needed) + " are needed";
}

