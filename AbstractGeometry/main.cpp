#include <Windows.h>
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
		/*for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}*/
		
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, 5, Color::Red);
		HBRUSH hBrush = CreateSolidBrush(Color::Red);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		Rectangle(hdc, 300, 300, 500, 500);

		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);

	}
	void info()const override
	{
		cout << typeid(*this).name() + 6 << endl;
		cout << "Длина стороны: " << get_side() << endl;
		Shape::info();
	}

};
class Rectangle_class :public Shape
{
	double side_A;
	double side_B;
public:
	Rectangle_class(double side_A,double side_B, Color color) :Shape(color)
	{
		this->side_A = side_A;
		this->side_B = side_B;
	}
	~Rectangle_class()	{}
	void set_sides(double side_A,double side_B)
	{
		this->side_A = side_A;
		this->side_B = side_B;
	}
	double get_side_A()const
	{
		return side_A;
	}
	double get_side_B()const
	{
		return side_B;
	}
	double get_area()const override
	{
		return side_A * side_B;
	}
	double get_perimeter()const override
	{
		return (side_A+side_B)*2;
	}
	void draw()const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		HPEN hPen = CreatePen(PS_SOLID, 5, Color::Red);
		HBRUSH hBrush = CreateSolidBrush(Color::Red);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		Rectangle(hdc, 200, 600, 200, 600);
		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);

	}
	void info()const override
	{
		cout << typeid(*this).name() + 6 << endl;
		cout << "Длина стороны A: " << get_side_A() << endl;
		cout << "Длина стороны B: " << get_side_B() << endl;
		Shape::info();
	}

};
void main()
{
	setlocale(LC_ALL, "");
	Rectangle_class rectangle(3, 10, Red);
	rectangle.info();
}