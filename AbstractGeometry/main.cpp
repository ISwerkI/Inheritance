#include <iostream>
using namespace std;

enum Color
{
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Violet = 0x00800080

};

class Shape
{
	Color color;
public:
	Shape(Color color) :color(color) {}
	virtual ~Shape() {}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	Square(double side, Color color) :Shape(color)
	{
		this->side = side;
	}
	~Square() {}
	void set_side(double side)
	{
		this->side = side;
	}
	double get_side()const
	{
		return side;
	}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
	}
	void draw()const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}

	}
	void info()const override
	{
		cout << typeid(*this).name() + 6 << endl;
		cout << "Длина стороны: " << get_side() << endl;
		Shape::info();
	}

};
void main()
{
	setlocale(LC_ALL, "");
	Square square(5, Color::Red);
	square.info();
}