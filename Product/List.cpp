#include "List.h"

using namespace std;


string Product::get_list_name() const noexcept
{
	return list_name;
}

int Product::get_total_price() const noexcept
{
	return total_price_gr;
}