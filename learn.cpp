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
	
	
	


	return 0;
}