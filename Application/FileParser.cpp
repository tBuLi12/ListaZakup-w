#include "FileParser.h"
#include <fstream>
#include <cstdio>

FileParser::FileParser(
	std::unordered_map<std::string, Product*>& products,
	std::unordered_map<std::string, List*>& lists
) : products(products), lists(lists)
{
	basePath = std::filesystem::current_path();
	basePath /= "Data";
}

void FileParser::loadItems()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath += "\\Products\\Items";
	for (auto& filePath : fs::directory_iterator(currPath))
	{
		auto name = filePath.path().stem().string();
		int price, weight;
		std::ifstream file(filePath.path());
		file >> price >> weight;
		std::string hazards;
		getline(file, hazards, '\n');
		hazards = hazards.erase(0, 1);
		products.insert({ name, new Item(name, price, weight, hazards) });
		file.close();
	}
}

void FileParser::loadProducts()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath += "\\Products\\Food";
	for (auto& filePath : fs::directory_iterator(currPath))
	{
		auto name = filePath.path().stem().string();
		int price, weight;
		std::ifstream file(filePath.path());
		file >> price >> weight;
		std::array<double, 6> arr;
		for (size_t i = 0; i < 6; ++i) {
			file >> arr[i];
		}
		products.insert({ name, new Food(name, price, weight, arr) });
		file.close();
	}
}

void FileParser::loadLists()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath += "\\Lists";
	for (auto& filePath : fs::directory_iterator(currPath))
	{
		auto name = filePath.path().stem().string();
		auto newList = new List(name);

		std::ifstream file(filePath.path());
		while (!file.eof())
		{
			std::string productName;
			std::getline(file, productName, ';');
			if (productName == std::string("")) {
				break;
			}
			int quantity;
			file >> quantity;
			file.get();
			newList->add_product(products[productName], quantity);
		}
		file.close();
		lists.insert({ name, newList });
	}
}

void FileParser::writeToFiles()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath += "\\Lists";

	for (auto& pair : lists)
	{
		auto newPath = currPath /= pair.first;
		newPath += ".txt";
		std::ofstream file(newPath.string(), std::ios_base::trunc);
		auto map = pair.second->get_list();
		for (auto& list_element : map)
		{
			file << list_element.first->get_name();
			file << ';';
			file << list_element.second;
			file << '\n';
		}
		file.close();
	}
}
