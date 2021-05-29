#include "Product.h"
#include <stdexcept>

using namespace std;


string Product::get_name() const noexcept
{
	return name;
}

int Product::get_price() const noexcept
{
	return price_gr;
}


Food::Food(string name, int price_gr, int weight, vector<double> nutrition) noexcept
{
	this->name = name;
	this->price_gr = price_gr;
	weight_grams = weight;
	this->nutrition = nutrition;
}

int Food::get_weight() const noexcept
{
	return weight_grams;
}

double Food::get_kcal_per_100g() const noexcept
{
	return nutrition[0];
}

double Food::get_fat_per_100g() const noexcept
{
	return nutrition[1];
}

double Food::get_carbohydrates_per_100g() const noexcept
{
	return nutrition[2];
}

double Food::get_fibre_per_100g() const noexcept
{
	return nutrition[3];
}

double Food::get_protein_per_100g() const noexcept
{
	return nutrition[4];
}

double Food::get_salt_per_100g() const noexcept
{
	return nutrition[5];
}

double Food::get_kcal() const noexcept
{
	return get_kcal_per_100g() * get_weight();
}

double Food::get_fat() const noexcept
{
	return get_fat_per_100g() * get_weight();
}

double Food::get_carbohydrates() const noexcept
{
	return get_carbohydrates_per_100g() * get_weight();
}

double Food::get_fibre() const noexcept
{
	return get_fibre_per_100g() * get_weight();
}

double Food::get_protein() const noexcept
{
	return get_protein_per_100g() * get_weight();
}

double Food::get_salt() const noexcept
{
	return get_salt_per_100g() * get_weight();
}


Item::Item(string name, int price_gr, int quantity) noexcept
{
	this->name = name;
	this->price_gr = price_gr;
	this->quantity = quantity;
}

int Item::get_quantity() const noexcept
{
	return quantity;
}
