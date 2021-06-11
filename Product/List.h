#pragma once
#include <string>
#include <unordered_map>
#include "Product.h"

class List
{
protected:
	std::string list_name;

	//int total_price_gr = 0;
	//int total_weight_grams = 0;
	std::unordered_map<Product*, int> products;
public:
	List(std::string list_name = "list") noexcept;
	std::string const& get_list_name() const noexcept;
	std::unordered_map<Product*, int> get_list();
	int get_total_price() const noexcept;
	int get_total_weight() const noexcept;
	void add_product(Product* product_ptr, int quantity) noexcept;
	void delete_product(Product* product) noexcept;
	//@TODO delete_product
};