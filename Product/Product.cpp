#include "Product.h"
#include <iostream>

using namespace std;


string Product::get_name() const noexcept
{
	return name;
}

int Product::get_price() const noexcept
{
	return price_gr;
}


Meat::Meat(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Meat::get_data() const noexcept
{
	return approximate_weight_grams;
}


Vegetable::Vegetable(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Vegetable::get_data() const noexcept
{
	return approximate_weight_grams;
}


Fruit::Fruit(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Fruit::get_data() const noexcept
{
	return approximate_weight_grams;
}


Drink::Drink(string name, int volume_ml, int price_gr) noexcept
{
	this->name = name;
	this->volume_ml = volume_ml;
	this->price_gr = price_gr;
	approximate_weight_grams = volume_ml;
}

int Drink::get_data() const noexcept
{
	return volume_ml;
}


Herb::Herb(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Herb::get_data() const noexcept
{
	return approximate_weight_grams;
}


Dairy::Dairy(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Dairy::get_data() const noexcept
{
	return approximate_weight_grams;
}


PreparedMeal::PreparedMeal(string name, int quantity, int price_gr) noexcept
{
	this->name = name;
	this->quantity = quantity;
	this->price_gr = price_gr;
}

int PreparedMeal::get_data() const noexcept
{
	return quantity;
}


Cosmetic::Cosmetic(string name, int quantity, int price_gr) noexcept
{
	this->name = name;
	this->quantity = quantity;
	this->price_gr = price_gr;
}

int Cosmetic::get_data() const noexcept
{
	return quantity;
}
