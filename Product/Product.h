#pragma once
#include <iostream>
#include <vector>


class Product
{
protected:
	std::string name;
	int price_gr;
public:
	std::string get_name() const noexcept;
	int get_price() const noexcept;
};


class Food :public Product
{
private:
	int weight_grams;
	// Nutrition per 100g
	std::vector<double> nutrition;
	double kcal, fat, carbohydrates, fibre, protein, salt;
public:
	Food(std::string name, int price_gr, int weight, std::vector<double> nutrition) noexcept;
	int get_weight() const noexcept;
	double get_kcal_per_100g() const noexcept;
	double get_fat_per_100g() const noexcept;
	double get_carbohydrates_per_100g() const noexcept;
	double get_fibre_per_100g() const noexcept;
	double get_protein_per_100g() const noexcept;
	double get_salt_per_100g() const noexcept;
	double get_kcal() const noexcept;
	double get_fat() const noexcept;
	double get_carbohydrates() const noexcept;
	double get_fibre() const noexcept;
	double get_protein() const noexcept;
	double get_salt() const noexcept;
};


class Item :public Product
{
private:
	int quantity;
public:
	Item(std::string name, int price_gr, int quantity) noexcept;
	int get_quantity() const noexcept;
};
