#include <iostream>
#include <vector>
using namespace std;
class Product {
public:
	int id;
	string name;
	float price;
	int amount;

};
class Cart {
public:
	vector<Product> items;
};
class Customer {
public:
	string name;
	Cart mycart;
	vector<Orders> history;
}
class Orders {
public:
	vector<Product> items;
	float totalPrice;
	string date;
}

int main() {
	// Create a vector called cars that will store strings
	vector<string> cars = {"Volvo", "BMW", "Ford", "Mazda"};

// Print vector elements
	for (string car : cars) {
  	cout << car << "\n";
	};
	Product obj1;
	obj1.name = "brahim";
	
	


	return 0;
}