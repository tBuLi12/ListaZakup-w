#include "FileParser.h"
#include "application.h"
#include "appExceptions.h"
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>

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
		if (file.fail() || price < 0 || weight < 0) {
			std::cerr << "Invalid data in " << name << ".txt\n";
			file.close();
			return;
		}
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
		bool cond = !file.fail() && price > 0 && weight > 0 && *(std::min_element(arr.begin(), arr.end())) > 0;
		if (cond)
		{
			app.products.insert({ name, new Food(name, price, weight, arr) });
		}
		else
		{
			std::cerr << "Invalid data in " << name << ".txt\n";
		}
		file.close();
	}
}

void FileParser::loadLists()
{
	namespace fs = std::filesystem;
	auto currPath = basePath;
	currPath /= "Lists";

	Application::Command_add adder(app);

	for (auto& filePath : fs::directory_iterator(currPath))
	{
		auto name = filePath.path().stem().string();
		auto newList = new List(name);
		app.lists.insert({ name, newList });
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
			try {
				adder.exec(lineStrem);
			}
			catch (AppException const& e) {
				std::cerr << e.what() << std::endl;
			}
		}
		std::cout.clear();
		app.logs.clear();
		file.close();
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
		auto newPath = currPath / pair.first;
		newPath += ".txt";
		std::ofstream file(newPath.string(), std::ios_base::trunc);
		file << *(pair.second);
		file.close();
	}
}

bool FileParser::deleteListFile(List* list)
{
	auto filePath = basePath / ".." / "Data" / "Lists";
	filePath /= list->get_list_name();
	filePath += ".txt";
	return std::filesystem::remove(filePath);
}

void FileParser::saveLogs()
{
	auto filePath = basePath / ".." / "Data" / "logs";
	filePath += ".txt";
	std::ofstream file(filePath.string(), std::ios_base::trunc);
	app.logs.read(file);
	file.close();
}