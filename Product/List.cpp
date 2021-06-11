#include "List.h"
#include<string>
#include<set>



std::string const& List::get_list_name() const noexcept
{
	return list_name;
}


std::unordered_map<Product*, int> List::get_list() {
	return this->products;
}

int List::get_total_price() const noexcept
{
	int total = 0;
	for (auto item: products) {
		total += item->get_price();
	}
	return total;
}

int List::get_total_weight() const noexcept
{
	int total = 0;
	for (auto item: products) {
		total += item->get_price();
	}
	return total;
}

List::List(std::string list_name = "list") {

	this->list_name = list_name;
	this->products.clear();

	//int total_price = 0;
	//int total_weight = 0;

	/*
	for (auto product : product_set) {
		total_price += product->get_price();
		total_weight += product->get_weight();
	}
	this->total_price_gr = total_price;
	this->total_weight_grams = total_weight;
	*/
}

void List::add_product(Product* product_ptr, int quantity) {

	//this->total_price_gr += product_ptr->get_price();
	//this->total_weight_grams += product_ptr->get_weight();
	this->products.insert(std::make_pair<Product*, int>(product_ptr, quantity));
}

void List::delete_product(Product* product_ptr) {
	this->products.erase(product_ptr);
}