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
		
		static const int width = 150;
		static const int height = 150;
		
		char plane[height][width];
		
	public:
		
		//This function operates from an origin in the center of the array instead of a corner
		void setPoint(int x, int y, char input)
		{
			x += width / 2;
			y += width / 2;
			
			x--;
			y--;
			
			plane[y][x] = input;
		}
		
		void emptyPoint(int x, int y)
		{
			plane[y][x] = ' ';
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
		
		Screen(char preset)
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
	for (int i = 0; i < scr -> getScreenWidth(); i++)
	{
		scr -> setPoint(i + 1 - (scr->getScreenHeight() / 2) , 0, gridX);
	}
	
	for (int i = 0; i < scr -> getScreenHeight(); i++)
	{
		scr -> setPoint(0, i + 1 - (scr -> getScreenWidth() / 2), gridY);
	}
	
	scr -> setPoint(0, 0, '+');
	return;
}

void mapParabolaOnScreen(Parabola parab, Screen* scr)
{
	double parabX = (0 - scr -> getScreenWidth())/ 2;
	double parabY;
	parabX++;
	
	for (int i = 0; i < scr -> getScreenWidth(); i++)
	{
		parabY = parab.calculateY(parabX);
		
		if (parab.a > 0 and parabY < (scr -> getScreenHeight() / 2))
		{
			scr -> setPoint(parabX, parabY, '*');
		}
		
		else if (parab.a < 0 and parabY > ((scr -> getScreenHeight() / 2) + 1))
		{
			scr -> setPoint(parabX, -parabY, '*');
		}
		
		parabX++;
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
	
	Screen scr;
	
	setGrid(&scr, '-', '|');
	
	double a, b, c;
	
	cout << "Enter a, b and c coefficients: " << endl;
	cin >> a >> b >> c;
	
	Parabola parab(a, b, c);
	
	mapParabolaOnScreen(parab, &scr);
	
	scr.printScreen();
	return main();
}
