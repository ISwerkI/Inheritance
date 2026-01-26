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
		White = 0x00FFFFFF,
		Orange = 0x00006CFF
	};

#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color, Color fill_color = Color::Black
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color, fill_color

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
		Color fill_color;
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
		Shape(SHAPE_TAKE_PARAMETERS) :color(color),fill_color(fill_color)
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
		Color complimentary(Color color)const
		{
			if (color == Black) return White;
			if (color == Red) return Green;
			if (color == Green) return Red;
			if (color == Blue) return Orange;
			if (color == Yellow) return Violet;
			if (color == Violet) return Yellow;
			if (color == White) return Black;
			if (color == Orange) return Blue;

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
			HPEN hPen_complimentary = CreatePen(PS_SOLID, 5, complimentary(color));
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen_complimentary);
			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);
			/*
				hdc- это контекст устройства, на котором нужно нарисовать пр€моугольник.
				300, 300 - корды верхнего левого угла
				500, 50 - корды правого нижнего угла
				Ќачало координат всегда находитс€ в левом верхнем углу!
				Rectangle() €вл€етс€ частью библиотеки WinGDI - Windows Grafics Device Interface
			*/
			MoveToEx(hdc, start_x, start_y, NULL);
			LineTo(hdc, start_x + side, start_y + side);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hPen_complimentary);
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
			HPEN hPen_complimentary = CreatePen(PS_SOLID, 5, complimentary(color));
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen_complimentary);

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
			MoveToEx(hdc,start_x,start_y,NULL);
			LineTo(hdc, start_x + width, start_y + height);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hPen_complimentary);
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
		~Circle() {}
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
			HPEN hPen_complimentary = CreatePen(PS_SOLID, 5, complimentary(color));
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen_complimentary);

			Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);
			MoveToEx(hdc, start_x, start_y+radius, NULL);
			LineTo(hdc, start_x +radius, start_y+radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hPen_complimentary);
			ReleaseDC(hwnd, hdc);

		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}
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
		~EquilateralTriangle() {}
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
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HPEN hPen_complimentary = CreatePen(PS_SOLID, 5, complimentary(color));
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc,hPen_complimentary);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x + (int)side / 2, start_y},
				{start_x + side,start_y + get_height()},
				{start_x,start_y + get_height()},
			};
			Polygon(hdc,vertices,3); //vertices - массив углов фигуры, 3 - количество углов(количество элементов массива)
			MoveToEx(hdc, start_x + (int)side / 2, start_y, NULL);
			LineTo(hdc, start_x + side / 2, start_y + get_height());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hPen_complimentary);
			ReleaseDC(hwnd, hdc);

		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double base;
		double side;
	public:
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		IsoscelesTriangle(double base, double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle(){}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area()const override
		{
			return base / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return base + 2 * side;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HPEN hPen_complimentary = CreatePen(PS_SOLID, 5, complimentary(color));
			HBRUSH hBrush = CreateSolidBrush(fill_color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hPen_complimentary);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x + base / 2,start_y},
				{start_x + base,start_y + get_height()},
				{start_x,start_y + get_height()},
			};
			Polygon(hdc, vertices, 3);
			MoveToEx(hdc, start_x + base / 2, start_y,NULL);
			LineTo(hdc, start_x + base / 2, start_y + get_height());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			DeleteObject(hPen_complimentary);
			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(250, -300, -300, 1, Geometry::Color::Green);
	square.info();

	Geometry::Rectangle rect(200, 100, 400, 100, 5, Geometry::Color::Orange);
	rect.info();

	Geometry::Circle circle(150, 700, 300, 5, Geometry::Color::Violet);
	circle.info();

	Geometry::EquilateralTriangle e_triangle(180, 500, 250, 32, Geometry::Color::Yellow);
	e_triangle.info();

	Geometry::IsoscelesTriangle iso_triangle(100, 50, 850, 500, 32, Geometry::Color::Violet);
	iso_triangle.info();
	
	while (true)
	{
		square.draw();
		rect.draw();
		circle.draw();
		iso_triangle.draw();
		e_triangle.draw();
	}
}