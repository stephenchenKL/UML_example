#pragma once

#include <iostream>
#include <vector>

class Product {
	std::string name;
	double price;
	double manHour;
public:
	Product(std::string name,  double price, double manHour);
	double getManHour() { return manHour; };
	std::string getName() { return name; };
};

class Employee {
	int id;
	std::string name;
public:
	Employee(int id, std::string n);
	virtual void workOn(Product product)=0;
	std::string getName() { return name; };
	int getId() { return id; };
	virtual double getPaid()=0;
};

class Sales: public Employee {
	int carSold;
public:
	Sales(int id, std::string n);
	void workOn(Product product);
	virtual double getPaid() {
		return carSold * 1000;
	};
};

class Technician : public Employee {
	double manHour;
public:
	Technician(int id, std::string n);
	void workOn(Product product);
	virtual double getPaid() {
		return manHour * 100;
	};
};


class Dpt {
	std::string name;
protected:
//employees is declared as protected because
//derived Dpts need to access employees.
	std::vector<Employee*> employees;
//vector of Employee pointer is needed.
//Employee is an abstract class. Can't
//instantiate abstract class
public:
	Dpt(std::string n);
	virtual void hire(Employee* e)=0;
	Employee* getEmployee(int id);
};

class SalesDpt : public Dpt {
	
public:
	SalesDpt();
	void hire(Employee* e);
};

class ServiceDpt : public Dpt {
public:
	ServiceDpt();
	void hire(Employee* e);
};



class Dealer {
	SalesDpt salesDpt;
	ServiceDpt serviceDpt;
	std::string name;
public:
	Dealer(std::string name);
	SalesDpt* getSalesDpt();
	ServiceDpt* getServiceDpt();
};