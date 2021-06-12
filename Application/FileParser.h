#pragma once

#include "../Product/List.h"
#include "../Product/Product.h"
#include <string>
#include <unordered_map>
#include <filesystem>

class FileParser
{
private:
	std::filesystem::path basePath;
	std::unordered_map<std::string, Product*>& products;
	std::unordered_map<std::string, List*>& lists;

	void loadItems();
	void loadProducts();
	void loadLists();

public:
	FileParser(
		std::unordered_map<std::string, Product*>& products,
		std::unordered_map<std::string, List*>& lists
	);
	void readFromFiles() {
		loadItems();
		loadProducts();
		loadLists();
	}
	void writeToFiles();
};