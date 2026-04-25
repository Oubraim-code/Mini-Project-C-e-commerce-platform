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
	Customer cst;
	Cart mycart;
	Orders myorders;
	cout << "Welcome to Zara Store\n";
	cout << "Can you tell us your name: ";
	cin >> cst.name;
	cout << "Thank you "<< cst.name << endl;
	cout << "=============Home======================="<< endl;
	cout << "1. Products\n";
	cout << "1. Cart\n";
	cout << "1. History\n";

	return 0;
}
