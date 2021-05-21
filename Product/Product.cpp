#include "Product.h"
#include <iostream>
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


Meat::Meat(string name, int weight_grams, int price_gr) noexcept
{
	if (weight_grams < 0 || price_gr < 0)
		throw invalid_argument("Received negative value.");
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Meat::get_weight() const noexcept
{
	return approximate_weight_grams;
}


Vegetable::Vegetable(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Vegetable::get_weight() const noexcept
{
	return approximate_weight_grams;
}


Fruit::Fruit(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Fruit::get_weight() const noexcept
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

int Drink::get_weight() const noexcept
{
	return volume_ml;
}


Herb::Herb(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Herb::get_weight() const noexcept
{
	return approximate_weight_grams;
}


Dairy::Dairy(string name, int weight_grams, int price_gr) noexcept
{
	this->name = name;
	approximate_weight_grams = weight_grams;
	this->price_gr = price_gr;
}

int Dairy::get_weight() const noexcept
{
	return approximate_weight_grams;
}


PreparedMeal::PreparedMeal(string name, int quantity, int price_gr, int weight_grams) noexcept
{
	this->name = name;
	this->quantity = quantity;
	this->price_gr = price_gr;
	approximate_weight_grams = weight_grams;
}

int PreparedMeal::get_weight() const noexcept
{
	return approximate_weight_grams;
}


Cosmetic::Cosmetic(string name, int quantity, int price_gr, int weight_grams) noexcept
{
	this->name = name;
	this->quantity = quantity;
	this->price_gr = price_gr;
	approximate_weight_grams = weight_grams;
}

int Cosmetic::get_weight() const noexcept
{
	return approximate_weight_grams;
}
