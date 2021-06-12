#include "Product.h"

using namespace std;

Product::Product(std::string name, int price, int weight) noexcept:
	name(name), price_gr(price), weight_grams(weight) {};

string const& Product::get_name() const noexcept
{
	return name;
}

int Product::get_price() const noexcept
{
	return price_gr;
}

int Product::get_weight() const noexcept
{
	return weight_grams;
}

Food::Food(string name, int price, int weight, array<double, 6> nutrition) noexcept:
	Product(name, price, weight), nutrition(nutrition) {};

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
	return get_kcal_per_100g() * weight_grams / 100.0;
}

double Food::get_fat() const noexcept
{
	return get_fat_per_100g() * weight_grams / 100.0;
}

double Food::get_carbohydrates() const noexcept
{
	return get_carbohydrates_per_100g() * weight_grams / 100.0;
}

double Food::get_fibre() const noexcept
{
	return get_fibre_per_100g() * weight_grams / 100.0;
}

double Food::get_protein() const noexcept
{
	return get_protein_per_100g() * weight_grams / 100.0;
}

double Food::get_salt() const noexcept
{
	return get_salt_per_100g() * weight_grams / 100.0;
}

std::string Food::get_info() const noexcept
{
	return "info";
}

Item::Item(string name, int price, int weight, std::string hazards) noexcept:
	Product(name, price, weight), hazards(hazards) {};

std::string Item::get_info() const noexcept
{
	return hazards;
}


