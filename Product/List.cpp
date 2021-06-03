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

List::List(std::string list_name, std::vector<Product*> product_vector) {

	this->list_name = list_name;
	this->products = product_vector;

	int total_price;
	int total_weight;

	
	for (auto product : product_vector) {
		total_price += product->get_price();
		total_weight += product->get_weight();
	}
	this->total_price_gr = total_price;
	this->total_weight_grams = total_weight;
}