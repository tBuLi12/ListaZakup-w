#include "FileParser.h"
#include "application.h"
#include <fstream>
#include <cstdio>
#include <iostream>

FileParser::FileParser(Application& app) : app(app)
{
	basePath = std::filesystem::current_path();
	basePath /= "Data";
}

void FileParser::loadItems()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath /= "Products";
	currPath /= "Items";
	for (auto& filePath : fs::directory_iterator(currPath))
	{
		auto name = filePath.path().stem().string();
		int price, weight;
		std::ifstream file(filePath.path());
		file >> price >> weight;
		std::string hazards;
		getline(file, hazards, '\n');
		hazards = hazards.erase(0, 1);
		app.products.insert({ name, new Item(name, price, weight, hazards) });
		file.close();
	}
}

void FileParser::loadProducts()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath /= "Products";
	currPath /= "Food";
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
		app.products.insert({ name, new Food(name, price, weight, arr) });
		file.close();
	}
}

void FileParser::loadLists()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath /= "Lists";

	Application::Command_add adder(&app);

	for (auto& filePath : fs::directory_iterator(currPath))
	{
		auto name = filePath.path().stem().string();
		auto newList = new List(name);
		app.selected = newList;
		std::ifstream file(filePath.path());
		std::cout.setstate(std::ostream::failbit);
		while (!file.eof())
		{
			std::string line;
			std::stringstream lineStrem;
			getline(file, line);
			if (line == "") {
				break;
			}
			lineStrem.str(line);
			adder.exec(lineStrem);
		}
		std::cout.clear();
		file.close();
		app.lists.insert({ name, newList });
	}
	app.selected = nullptr;
}

void FileParser::writeToFiles()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath /= "Lists";

	for (auto& pair : app.lists)
	{
		auto newPath = currPath /= pair.first;
		newPath += ".txt";
		std::ofstream file(newPath.string(), std::ios_base::trunc);
		file << *(pair.second);
		file.close();
	}
}
