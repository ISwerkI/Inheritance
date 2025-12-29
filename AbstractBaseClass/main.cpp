#include<iostream>
using std::cout;
using std::cin;
using std::endl;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;
};
class GroundVehicle : public Vehicle {};

class car : public GroundVehicle
{
public:
	void move()override
	{
		cout << "Машинка едет на 2 колесах" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "AbstractBaseClass" << endl;
	//Vehicle v;
	//GroundVehicle gv;
	car bmw;
	bmw.move();
}

