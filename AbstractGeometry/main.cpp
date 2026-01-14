#include <Windows.h>
#include <iostream>
using namespace std;

enum Color
{
	Black = 0x000000,
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Violet = 0x00800080,
	White = 0x00FFFFFF
};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

class Shape
{
	static const int MIN_START_X = 100;
	static const int MIN_START_Y = 100;
	static const int MAX_START_X = 1000;
	static const int MAX_START_Y = 700;
	static const int MIN_LINE_WIDTH = 1;
	static const int MAX_LINE_WIDTH = 32;
protected:
	Color color;
	int start_x;
	int start_y;
	int line_width;
public:
	int get_start_x()const
	{
		return start_x;
	}
	int get_start_y()const
	{
		return start_y;
	}	
	int get_line_width()const
	{
		return line_width;
	}
	void set_start_x(int start_x)
	{
		if (start_x < MIN_START_X)start_x = MIN_START_X;
		if (start_x > MAX_START_X)start_x = MAX_START_X;
		this->start_x = start_x;
	}
	void set_start_y(int start_y)
	{
		if (start_y < MIN_START_Y)start_y = MIN_START_Y;
		if (MAX_START_Y > 1000)start_y = MAX_START_Y;
		this->start_y = start_y;
	}
	void set_line_width(int line_width)
	{
		if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
		if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
		this->line_width = line_width;
	}
	Shape(SHAPE_TAKE_PARAMETERS) :color(color)
	{
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
	virtual ~Shape() {}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "ѕлощадь фигуры: " << get_area() << endl;
		cout << "ѕериметр фигуры: " << get_perimeter() << endl;
		draw();
	}

};

class Square :public Shape
{
	double side;
public:
	Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(start_x, start_y, line_width,color)
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
		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		Rectangle(hdc, start_x, start_y, start_x+side, start_y+side);
		/*
			hdc- это контекст устройства, на котором нужно нарисовать пр€моугольник.
			300, 300 - корды верхнего левого угла
			500, 50 - корды правого нижнего угла
			Ќачало координат всегда находитс€ в левом верхнем углу!
			Rectangle() €вл€етс€ частью библиотеки WinGDI - Windows Grafics Device Interface
		*/
		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);

	}
	void info()const override
	{
		cout << typeid(*this).name() + 6 << endl;
		cout << "ƒлина стороны: " << get_side() << endl;
		Shape::info();
	}

};
class Rectangle_class :public Shape
{
	double side_A;
	double side_B;
public:
	Rectangle_class(double side_A,double side_B, Color color) :Shape(SHAPE_GIVE_PARAMETERS)
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
		HPEN hPen = CreatePen(PS_SOLID, 5, Color::Violet);
		HBRUSH hBrush = CreateSolidBrush(Color::Violet);
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		Rectangle(hdc, 400, 100, 500, 400);
		DeleteObject(hBrush);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);

	}
	void info()const override
	{
		cout << typeid(*this).name() + 6 << endl;
		cout << "ƒлина стороны A: " << get_side_A() << endl;
		cout << "ƒлина стороны B: " << get_side_B() << endl;
		Shape::info();
	}

};
void main()
{
	setlocale(LC_ALL, "");
	Square square(-300, -300, 300, 1, White);
	square.info();
}