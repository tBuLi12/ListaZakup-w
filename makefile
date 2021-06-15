shoppingList: appExceptions.o application.o interface.o FileParser.o Product.o List.o main.o
	g++ -std=c++17 appExceptions.o application.o interface.o FileParser.o Product.o List.o main.o -o shoppingList && rm *.o

appExceptions.o:
	g++ -std=c++17 -c ./Application/appExceptions.cpp

application.o:
	g++ -std=c++17 -c ./Application/application.cpp

interface.o:
	g++ -std=c++17 -c ./Application/interface.cpp

FileParser.o:
	g++ -std=c++17 -c ./Application/FileParser.cpp

Product.o:
	g++ -std=c++17 -c ./Product/Product.cpp

List.o:
	g++ -std=c++17 -c ./Product/List.cpp

main.o:
	g++ -std=c++17 -c main.cpp