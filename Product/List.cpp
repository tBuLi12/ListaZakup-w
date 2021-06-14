#include "List.h"
#include "../Application/appExceptions.h"


std::string const& List::get_list_name() const noexcept
{
	return list_name;
}

int List::get_total_price() const noexcept
{
	int total = 0;
	for (auto item: products) {
		total += item.second*item.first->get_price();
	}
	return total;
}

int List::get_total_weight() const noexcept
{
	int total = 0;
	for (auto item: products) {
		total += item.second*item.first->get_weight();
	}
	return total;
}

List::List(std::string const& list_name) noexcept: list_name(list_name) {};

List::List(std::string&& list_name) noexcept: list_name(std::move(list_name)) {};

void List::add_product(const Product* product_ptr, p_count quantity) {
	auto product = products.find(product_ptr);
	if (product == products.end()) {
		this->products.insert({product_ptr, quantity});
	} else {
		product->second += quantity;
	}	
}

void List::delete_product(const Product* product_ptr) {
	auto product = products.find(product_ptr);
	if (product == products.end()) {
		throw ProductNotOnListException(list_name, product_ptr->get_name());
	}
	this->products.erase(product_ptr);
}

void List::set_count(const Product* product_ptr, p_count quantity) {
	if (quantity == 0) {
		delete_product(product_ptr);
		return;
	}
	if (products.find(product_ptr) == products.end()) {
		throw ProductNotOnListException(list_name, product_ptr->get_name());
	} else {
		this->products[product_ptr] = quantity;
	}
}

std::ostream& operator<<(std::ostream& stream, List& list)
{
	for (auto& list_element : list.products)
	{
		if (list_element.second != 1) {
			stream << std::to_string(list_element.second) << ' ';
		}
		stream << list_element.first->get_name() << std::endl;
	}
	std::string totalWeight(std::to_string(list.get_total_weight()));
	std::string totalPrice(std::to_string(list.get_total_price()));
	totalWeight.insert(totalWeight.end() - 2, '.');
	totalPrice.insert(totalPrice.end() - 2, '.');
	stream << std::endl << "Total price is " << totalPrice << " zl" << std::endl;
	stream << "Total weight is " << totalWeight << " kg" << std::endl;
	return stream;
}