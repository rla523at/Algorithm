#include <iostream>

#include "Exception.h"

using uint = unsigned int;

class Coordinate
{
public:
	Coordinate(void) = delete;
	Coordinate(const int x_coordinate, const int y_coordinate)
		: x_(x_coordinate), y_(y_coordinate) {};

public://Query
	uint quadrant(void) const
	{
		ms::require(!this->is_on_axis(), "Coordinates above the coordinate axis cannot define a quadrant.");

		if (this->x_ > 0)
		{
			if (this->y_ > 0)
			{
				return 1;
			}
			else
			{
				return 2;
			}
		}
		else
		{
			if (this->y_ > 0)
			{
				return 3;
			}
			else
			{
				return 4;
			}
		}
	}

private:
	bool is_on_axis(void) const
	{
		return x_ == 0 || y_ == 0;
	}

private:
	int x_ = 0;
	int y_ = 0;
};

int main(void)
{
	int x_coordinate, y_coordinate;
	std::cin >> x_coordinate >> y_coordinate;

	Coordinate coordinate = { x_coordinate, y_coordinate };

	try 
	{
		std::cout << coordinate.quadrant();
	}
	catch (const std::exception& except)
	{
		std::cout << except.what();
		std::cout << "Please re-enter coordinates. \n\n";

		main();
	}	

	return 0;
}