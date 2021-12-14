#include <iostream>
#include <vector>
#include <typeinfo>
#include "Header.h"


Dpt::Dpt(std::string n) {
	name = n;
}

Employee* Dpt::getEmployee(int id) {
	for (Employee* employee : employees) {
		if (employee->getId() == id) {
			return employee;
		}
	}
	return nullptr;
}

SalesDpt::SalesDpt():Dpt("Sales Department") {
}

ServiceDpt::ServiceDpt() : Dpt("Service Department") {
}


void SalesDpt::hire(Employee* e) {
	employees.push_back(e);
}


void ServiceDpt::hire(Employee* e) {
	employees.push_back(e);
}



Employee::Employee(int id, std::string n) {
	this->id = id;
	name = n;
}


Sales::Sales(int id, std::string n):Employee(id, n) {
	carSold = 0;
}
void Sales::workOn(Product product) {
	std::cout << this->getName() << " sells " << product.getName() << std::endl;
	this->carSold++;
}

Technician::Technician(int id, std::string n) : Employee(id, n) {
	manHour = 0;
}
void Technician::workOn(Product product) {
	std::cout << this->getName() << " changes " << product.getName() << std::endl;
	this->manHour += product.getManHour();
}



Dealer::Dealer(std::string name) {
	this->name = name;
};

SalesDpt* Dealer::getSalesDpt() {
	return &salesDpt;
}
ServiceDpt* Dealer::getServiceDpt() {
	return &serviceDpt;
}



Product::Product(std::string name, double price, double manHour) {
	this->name = name;
	this->price = price;
	this->manHour = manHour;
}

int main()
{
	Dealer gilroyToyota("Gilroy Toyota");

	Sales Sam = Sales(1, "Sam");
	Sales Sean = Sales(2, "Sean");
	Technician Tom = Technician(3, "Tom");
	gilroyToyota.getSalesDpt()->hire(&Sam);
	gilroyToyota.getSalesDpt()->hire(&Sean);
	gilroyToyota.getServiceDpt()->hire(&Tom);

	gilroyToyota.getSalesDpt()->getEmployee(1)->workOn(Product("Tundra", 49999.99, 0));
	gilroyToyota.getSalesDpt()->getEmployee(2)->workOn(Product("Tundra", 49999.99, 0));
	gilroyToyota.getSalesDpt()->getEmployee(2)->workOn(Product("Tundra", 49999.99, 0));
	gilroyToyota.getServiceDpt()->getEmployee(3)->workOn(Product("Wheel Bearing", 450.00, 8));
	gilroyToyota.getServiceDpt()->getEmployee(3)->workOn(Product("Brake System", 900.00, 8.5));
	gilroyToyota.getServiceDpt()->getEmployee(3)->workOn(Product("Engine Oil", 90.00, 1.5));

	std::cout << "Sam's salary: " << Sam.getPaid() << std::endl;
	std::cout << "Sean's salary: " << Sean.getPaid() << std::endl;
	std::cout << "Tom's salary: " << Tom.getPaid() << std::endl;

	Sales s = Sales(4, "Sandra");
	Employee& e1 = s;
	e1.workOn(Product("Engine Oil", 90.00, 1.5));
	std::cout << typeid(e1).name() << std::endl;
	Employee* e2 = &s;
	e2->workOn(Product("Brake System", 900.00, 8.5));


	// Object Slicing
	// if Employee class is not abstract class, can not use vector<Employee> employees to store Sales and Technician
	// Derived class Sales/Technician specific members of the object being stored in class Employee get sliced off
	//Employee e3 = s;
	//dynamic_cast<Sales*>(&e3)->workOn(Product("Brake System", 900.00, 8.5)); // Error!
	//dynamic_cast<Sales&>(e3).workOn(Product("Brake System", 900.00, 8.5));	 // Error!

	

	return 0;
}