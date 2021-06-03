#pragma once
#include<string>
#include<vector>
#include "Product.h"
class List
{
protected:
	std::string list_name;

	int total_price_gr;
	int total_weight_grams;

	std::vector<Product*> products;
	

public:
	List(std::string list_name, std::vector<Product*> product_vector) noexcept;
	std::string get_list_name() const noexcept;
	int get_total_price() const noexcept;

};