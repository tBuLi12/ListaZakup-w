#include "List.h"
#include<string>
#include<vector>



std::string List::get_list_name() const noexcept
{
	return list_name;
}

int List::get_total_price() const noexcept
{
	return total_price_gr;
}

List::List(std::vector<Food*> product_vector, std::string list_name = "list") {

	this->list_name = list_name;
	this->products = product_vector;

	int total_price = 0;
	int total_weight = 0;

	
	for (auto product : product_vector) {
		total_price += product->get_price();
		total_weight += product->get_weight();
	}
	this->total_price_gr = total_price;
	this->total_weight_grams = total_weight;
}

void List::add_product(Food* product_ptr) {

	this->total_price_gr += product_ptr->get_price();
	this->total_weight_grams += product_ptr->get_weight();

	this->products.push_back(product_ptr);
}