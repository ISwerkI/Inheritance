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
class Car : public GroundVehicle
{
public:
	void move()override
	{
		cout << "Машинка едет на 4 колесах" << endl;
	}
};
class Bike :public GroundVehicle
{
public:
	void move()override
	{
		cout << "Велосипед едет на 2 колесах" << endl;
	}
};


class AirVehicle : public Vehicle {};
class Plane : public AirVehicle
{
public:
	void move()override
	{
		cout << "Самолет летит с помощью турбин и крыльев" << endl;
	}
};
class Helicopter : public AirVehicle
{
public:
	void move()override
	{
		cout << "Вертолет летит с помощью несущего винта" << endl;
	}
};


class WaterVehicle : public Vehicle{};
class SailingShip : public WaterVehicle
{
public:
	void move()override
	{
		cout << "Парусные корабли перемещаются c помощью парусов" << endl;
	}
};
class Submarine : public WaterVehicle
{
public:
	void move()override
	{
		cout << "Подводные лодки перемещаются c гребных винтов, водометов, электромоторов и тд" << endl;
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

