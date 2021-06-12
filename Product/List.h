#ifndef LIST_HEADER
#define LIST_HEADER

#include <ostream>
#include <string>
#include <unordered_map>
#include "Product.h"

typedef unsigned int p_count;

class List
{
protected:
	std::string list_name;
	std::unordered_map<const Product*, p_count> products;
public:
	List(std::string list_name) noexcept;
	std::string const& get_list_name() const noexcept;
	//std::unordered_map<Product*, int> get_list();
	int get_total_price() const noexcept;
	int get_total_weight() const noexcept;
	void add_product(const Product* product_ptr, p_count quantity = 1);
	void delete_product(const Product* product);
	void set_count(const Product* product_ptr, p_count quantity);
	friend std::ostream& operator<<(std::ostream& stream, List& list);
	//@TODO delete_product
};

std::ostream& operator<<(std::ostream& stream, List& list);

#endif
