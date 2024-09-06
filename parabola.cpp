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
			double* discriminant = new double;
			*discriminant = pow(b, 2) - (4 * a * c);
			
			if (*discriminant < 0)
			{
				cout << "No x intersections." << endl;
				delete discriminant;
				return;
			}
			
			cout << "The parabola intersects with X axis at: " <<
			(0 - b - sqrt(*discriminant) ) / (2 * a) <<
			", " <<
			(0 - b + sqrt(*discriminant) ) / (2 * a) <<
			endl;
			
			delete discriminant;
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

class Screen
{
	private:
		
		static const int width = 100;
		static const int height = 100;
		
		char plane[height][width];
		
	public:
		
		void setPoint(int x, int y, char input)
		{
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
					setPoint(x, y, ' ');
				}
			}
		}
		
		Screen(char preset)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					setPoint(x, y, preset);
				}
			}
		}
};

void setGrid(Screen* scr, char gridX, char gridY)
{
	for (int i = 0; i < scr -> getScreenWidth(); i++)
	{
		scr -> setPoint(i, (scr -> getScreenHeight()) / 2, gridX);
	}
	
	for (int i = 0; i < scr -> getScreenHeight(); i++)
	{
		scr -> setPoint((scr -> getScreenWidth()) / 2, i, gridY);
	}
	
	scr -> setPoint((scr -> getScreenWidth()) / 2, (scr -> getScreenHeight()) / 2, '+');
	return;
}

int main()
{
	Screen scr;
	
	setGrid(&scr, '-', '|');
	
	double a, b, c;
	
	cout << "Enter a, b and c coefficients: " << endl;
	cin >> a >> b >> c;
	
	Parabola parab(a, b, c);
	
	int parabX = 0 - ( (scr.getScreenWidth()) / 2);
	int parabY;
	
	for (int i = 0; i < scr.getScreenWidth(); i++)
	{
		parabY = (int)parab.calculateY(parabX) + (scr.getScreenHeight() / 2);
		
		if (parabY < scr.getScreenHeight())
		{
			scr.setPoint(i, parabY, '*');
		}
		
		parabX++;
	}
	
	scr.printScreen();
}
