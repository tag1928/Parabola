#include <iostream>
#include <math.h>

using namespace std;

class Point
{
	public:
		
		double x;
		double y;
		
		Point(){};
		
		Point(int x, int y)
		{
			this -> x = x;
			this -> y = y;
		}
		
		void printPoint()
		{
			cout << "X : " << x << endl;
			cout << "Y : " << y << endl;
			return;
		}
};

////

class Parabola
{
	public:
		
		double a;
		double b;
		double c;
		
		Parabola(){};
		
		double calculateY(double x)
		{
			return (a * x * x) + (b * x) + (c);
		}
		
		void printXIntersections()
		{	
			double discriminant = (b * b) - (4 * a * c);
			
			if (discriminant < 0)
			{
				cout << "No x intersections." << endl;
				return;
			}
			
			cout << "The parabola intersects with X axis at: " <<
			(0 - b - sqrt(discriminant) ) / (2 * a) <<
			", " <<
			(0 - b + sqrt(discriminant) ) / (2 * a) <<
			endl;
			
			return;
		}
		
		Point calculateVertex()
		{
			Point answer;
			
			answer.x = 0 - (b / (2 * a));
			answer.y = calculateY(answer.x);
			
			return answer;
		}
		
		Parabola(double a, double b, double c)
		{
			this -> a = a;
			this -> b = b;
			this -> c = c;
		}
};

////

class Screen
{
	private:
		
		static const int width = 144;
		static const int height = 144;
		
		char plane[height][width];
		
	public:
		
		//This function operates from an origin in the center of the array instead of a corner
		void setPoint(int x, int y, char input)
		{
			x += width / 2;
			y += height / 2;
			
			x--;
			y--;
			
			plane[y][x] = input;
		}
		
		void printScreen()
		{
			for (int y = height - 1; y >= 0; y--)
			{
				for (int x = 0; x < width; x++)
				{
					cout << plane[y][x];
				}
				
				cout << "\n";
			}
			return;
		}
		
		int getScreenWidth(){return width;}
		int getScreenHeight(){return height;}
		
		int getPositiveXInputBound()
		{
			return width / 2;
		}
		
		int getNegativeXInputBound()
		{
			return 1 - (width / 2);
		}
		
		int getPositiveYInputBound()
		{
			return height / 2;
		}
		
		int getNegativeYInputBound()
		{
			return 1 - (height / 2);
		}
		
		Screen()
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					plane[y][x] = ' ';
				}
			}
		}
		
		Screen(char preset)//This constructor will set every single element in the plane array to the char of the argument
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					plane[y][x] = preset;
				}
			}
		}
};

////

void setGrid(Screen* scr, char gridX, char gridY)
{	
	for (int i = scr -> getNegativeXInputBound(); i <= scr -> getPositiveXInputBound(); i++) //This loop first draws the X axis on the screen
	{
		scr -> setPoint(i , 0, gridX);
	}
	
	for (int i = scr -> getNegativeYInputBound(); i <= scr -> getPositiveYInputBound(); i++) //Does the same but for the Y axis
	{
		scr -> setPoint(0, i, gridY);
	}
	
	scr -> setPoint(0, 0, '+');
	return;
}

void mapParabolaOnScreen(Parabola parab, Screen* scr)
{
	for (int i = scr -> getNegativeXInputBound(); i <= scr -> getPositiveXInputBound(); i++)
	{
		if (parab.a > 0)
		{
			if (parab.calculateY(i) <= scr -> getPositiveYInputBound())
			{
				scr -> setPoint(i, parab.calculateY(i), '*');
			}
		}
		
		if (parab.a < 0)
		{
			if (parab.calculateY(i) >= scr -> getNegativeYInputBound())
			{
				scr -> setPoint(i, parab.calculateY(i), '*');
			}
		}
	}
	
	return;
}

int main()
{
	short int input;
	
	cout << "\nType the number of an action\n";
	cout << "1. Display a parabola\n";
	cout << "2. Exit" << endl;
	
	cin >> input;
	
	if (input == 2) return 0;
	
	////
	
	cout << "Enter a, b and c coefficients: " << endl;
	
	Screen scr;
	setGrid(&scr, '-', '|');
	double a, b, c;
	
	cin >> a >> b >> c;
	
	Parabola parab(a, b, c);
	
	mapParabolaOnScreen(parab, &scr);
	
	scr.printScreen();
	
	return main();
}
