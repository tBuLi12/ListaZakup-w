#pragma once
#include <iostream>

using namespace std;


class Product
{
protected:
	string name;
	int price_gr, approximate_weight_grams;
public:
	string get_name() const noexcept;
	int get_price() const noexcept;
	virtual int get_data() const noexcept = 0;
};


class Meat :public Product
{
public:
	Meat(string name, int weight_grams, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class Vegetable :public Product
{
public:
	Vegetable(string name, int weight_grams, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class Fruit :public Product
{
public:
	Fruit(string name, int weight_grams, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class Drink :public Product
{
private:
	int volume_ml;
public:
	Drink(string name, int volume_ml, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class Herb :public Product
{
public:
	Herb(string name, int weight_grams, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class Dairy :public Product
{
public:
	Dairy(string name, int weight_grams, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class PreparedMeal :public Product
{
private:
	int quantity;
public:
	PreparedMeal(string name, int quantity, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};


class Cosmetic : public Product
{
private:
	int quantity;
public:
	Cosmetic(string name, int quantity, int price_gr) noexcept;
	virtual int get_data() const noexcept;
};
