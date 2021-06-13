#include "List.h"


std::string const& List::get_list_name() const noexcept
{
	return list_name;
}


std::unordered_map<const Product*, p_count> List::get_list() {
 	return this->products;
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

	//this->total_price_gr += product_ptr->get_price();
	//this->total_weight_grams += product_ptr->get_weight();
	this->products.insert({product_ptr, quantity});
}

void List::delete_product(const Product* product_ptr) {
	this->products.erase(product_ptr);
}
void List::set_count(const Product* product_ptr, p_count quantity) {
	if (products.find(product_ptr) == products.end()) {
		return;
	} else {
		this->products[product_ptr] = quantity;
	}
}

std::ostream& operator<<(std::ostream& stream, List& list)
{
	for (auto& list_element : list.products)
	{
		if (list_element.second != 0) {
			stream << std::to_string(list_element.second) << ' ';
		}
		stream << list_element.first->get_name() << std::endl;
	}
	return stream;
}