#include "List.h"
#include<string>
#include<set>



std::string List::get_list_name() const noexcept
{
	return list_name;
}

int List::get_total_price() const noexcept
{
	return total_price_gr;
}

List::List(std::unordered_set<Food*> product_set, std::string list_name = "list") {

	this->list_name = list_name;
	this->products = product_set;

	int total_price = 0;
	int total_weight = 0;

	
	for (auto product : product_set) {
		total_price += product->get_price();
		total_weight += product->get_weight();
	}
	this->total_price_gr = total_price;
	this->total_weight_grams = total_weight;
}

void List::add_product(Food* product_ptr) {

	this->total_price_gr += product_ptr->get_price();
	this->total_weight_grams += product_ptr->get_weight();

	this->products.insert(product_ptr);
}