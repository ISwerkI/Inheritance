#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
using namespace std;

namespace Geometry
{
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
		static const int MIN_SIZE = 20;
		static const int MAX_SIZE = 500;

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
			//if (start_x > MAX_START_X)start_x = MAX_START_X;
			//if (start_x < MIN_START_X)start_x = MIN_START_X;
			//this->start_x = start_x;
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			//if (start_y < MIN_START_Y)start_y = MIN_START_Y;
			//if (MAX_START_Y > 1000)start_y = MAX_START_Y;
			//this->start_y = start_y;
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			//if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			//if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			//this->line_width = line_width;
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width < MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;

		}
		double filter_size(double size)
		{
			return
				size<MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
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
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(start_x, start_y, line_width, color)
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

			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);
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
		Rectangle_class(double side_A, double side_B, Color color) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			this->side_A = side_A;
			this->side_B = side_B;
		}
		~Rectangle_class() {}
		void set_sides(double side_A, double side_B)
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
			return (side_A + side_B) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, Color::Violet);
			HBRUSH hBrush = CreateSolidBrush(Color::Violet);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, 400, 100, 500, 400);
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

	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double width)
		{
			this->height = filter_size(height);
		}
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}

		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle(){}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS){}
		~Triangle(){}
		virtual double get_height()const = 0;
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle(){}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return 3 * side;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID,line_width,color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc,hPen);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	//setlocale(LC_ALL, "");
	//Geometry::Square square(-300, -300, 300, 1, Geometry::Color::White);
	//square.info();

	//Geometry::Rectangle rect(200, 100, 500, 100, 5, Geometry::Color::Red);
	//rect.info();

	Geometry::Circle circle(50, 700, 300, 5, Geometry::Color::Yellow);
	circle.info();

	Geometry::EquilateralTriangle e_triangle(80, 500, 500, 32, Geometry::Color::Green);
	e_triangle.info();
}