#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "../Product/List.h"
#include "../Product/Product.h"
#include <string>
#include <unordered_map>
#include <filesystem>

class Application;
class FileParser
{
private:
	std::filesystem::path basePath;
	Application& app;
	void loadItems();
	void loadProducts();
	void loadLists();

public:
	FileParser(Application&);
	void readFromFiles() {
		loadItems();
		loadProducts();
		loadLists();
	}
	void writeToFiles();
	bool deleteListFile(List*);
};

#endif