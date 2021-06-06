#pragma once
#include <string>
#include <unordered_set>
#include "Product.h"

class List
{
protected:
	std::string list_name;

	//int total_price_gr = 0;
	//int total_weight_grams = 0;
	std::unordered_multiset<Product*> products;
public:
	List(std::string list_name = "list") noexcept;
	std::string const& get_list_name() const noexcept;
	int get_total_price() const noexcept;
	int get_total_weight() const noexcept;
	void add_product(Product* product) noexcept;
};