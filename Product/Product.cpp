#include "Product.h"

using namespace std;

Product::Product(std::string const& name, int price, int weight) noexcept:
	name(name), price_gr(price), weight_grams(weight) {};

Product::Product(std::string&& name, int price, int weight) noexcept:
	name(std::move(name)), price_gr(price), weight_grams(weight) {};

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

Food::Food(string const& name, int price, int weight, array<double, 6> const& nutrition) noexcept:
	Product(name, price, weight), nutrition(nutrition) {};

Food::Food(string&& name, int price, int weight, array<double, 6> const& nutrition) noexcept:
	Product(std::move(name), price, weight), nutrition(nutrition) {};

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
	std::stringstream stream;
	stream << name << "\n";
	stream << "\t" << "Kcal:\t\t" << get_kcal() << "\n";
	stream << "\t" << "Fat:\t\t" << get_fat() << "g\n";
	stream << "\t" << "Carbohydrates:\t" << get_carbohydrates() << "g\n";
	stream << "\t" << "Fibre:\t\t" << get_fibre() << "g\n";
	stream << "\t" << "Protein:\t" << get_protein() << "g\n";
	stream << "\t" << "Salt:\t\t" << get_salt() << "g\n";
	return stream.str();
}

Item::Item(string const& name, int price, int weight, std::string info) noexcept:
	Product(name, price, weight), info(info) {};

Item::Item(string&& name, int price, int weight, std::string info) noexcept:
	Product(std::move(name), price, weight), info(info) {};

std::string Item::get_info() const noexcept
{
	std::stringstream stream;
	stream << name;
	stream << "\n\t" << info << "\n";
	return stream.str();
}