#ifndef PRODUCT_HEADER
#define PRODUCT_HEADER

#include <string>
#include <array>
#include <sstream>

/*
struct Nutrition
{
	//per 100g
	double kcal;
	double fat;
	double carbohydrates;
	double fibre;
	double salt;
};
*/

class Product
{
protected:
	std::string name;
	int price_gr;
	int weight_grams;
public:
	Product(std::string const& name, int price_gr, int weight) noexcept;
	Product(std::string&& name, int price_gr, int weight) noexcept;
	std::string const& get_name() const noexcept;
	int get_price() const noexcept;
	int get_weight() const noexcept;
	virtual std::string get_info() const noexcept = 0;
};


class Food :public Product
{
private:
	// Nutrition per 100g
	std::array<double, 6> nutrition;
public:
	Food(std::string const& name, int price_gr, int weight, std::array<double, 6> const& nutrition) noexcept;
	Food(std::string&& name, int price_gr, int weight, std::array<double, 6> const& nutrition) noexcept;
	//int get_weight() const noexcept;
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
	std::string get_info() const noexcept;
};


class Item :public Product
{
private:
	std::string hazards;
public:
	Item(std::string const& name, int price, int weight, std::string haz) noexcept;
	Item(std::string&& name, int price, int weight, std::string haz) noexcept;

	std::string get_info() const noexcept;
	//int get_quantity() const noexcept;
};

#endif