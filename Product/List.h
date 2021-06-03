#pragma once
#include<string>
#include<array>

class Product
{
protected:
	std::string list_name;
	int total_price_gr;

public:
	std::string get_list_name() const noexcept;
	int get_total_price() const noexcept;
};