#pragma once
#include <string>
#include <unordered_map>
#include "Product.h"

typedef unsigned int p_count;

class List
{
protected:
	std::string list_name;

	//int total_price_gr = 0;
	//int total_weight_grams = 0;
	std::unordered_map<Product*, p_count> products;
public:
	List(std::string list_name);
	std::string const& get_list_name() const noexcept;
	//std::unordered_map<Product*, int> get_list();
	int get_total_price() const noexcept;
	int get_total_weight() const noexcept;
	void add_product(Product* product_ptr, p_count quantity = 1);
	void delete_product(Product* product);
	void set_count(Product* product_ptr, p_count quantity);
	//@TODO delete_product
};
