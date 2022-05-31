#pragma once

#include <algorithm>
#include <bitset>
#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <exception>
#include <sstream>

namespace ms
{
	void require(const bool requirement, const std::string_view message)
	{
		if (!requirement)
		{
			std::ostringstream os;

			os << "==============================오류========================================\n\n";
			os << "메시지\t\t: " << message << "\n\n";
			os << "==========================================================================\n";

			throw std::runtime_error(os.str());
		}
	}

	void exception(const std::string_view message)
	{
		ms::require(false, message);
	}

	int char_to_number(const char c)
	{
		ms::require(std::isdigit(c), "examine character should be digit");

		return c - '0';
	}
}

class Hierarchical_Quadrant
{
public:
	Hierarchical_Quadrant(const std::string_view& quadrants)
	{
		ms::require(this->is_valid(quadrants), "initial quadrants should be valid");

		this->quadrants_.resize(quadrants.size());
		std::copy(quadrants.begin(), quadrants.end(), this->quadrants_.begin());
	}

public: //Command
	void move(const long long horizontal_movement, const long long vertical_movement)
	{
		const auto index_pos = static_cast<long long>(this->quadrants_.size() - 1);

		if (horizontal_movement > 0)
		{
			this->move_right(horizontal_movement);
		}
		else
		{
			const auto num_movement = std::abs(horizontal_movement);
			this->move_left(num_movement);
		}

		if (vertical_movement > 0)
		{
			this->move_up(vertical_movement);
		}
		else
		{
			const auto num_movement = std::abs(vertical_movement);
			this->move_down(num_movement);
		}
	}

public: //Query
	bool is_valid(const std::string_view quadrants) const
	{
		for (const auto c : quadrants)
		{
			const auto number = ms::char_to_number(c);

			if (0 == number || 4 < number)
			{
				return false;
			}
		}

		return true;
	}


	void print(void) const
	{
		for (const auto c : this->quadrants_)
		{
			std::cout << c;
		}

		std::cout << "\n";
	}

private:
	void move_right(const size_t num_movement)
	{		
		std::bitset<this->max_bit> binary(num_movement);

		for (size_t i = 0; i < this->max_bit; ++i)
		{
			if (binary[i])
			{
				bool is_end = false;
				auto pos = i;

				while (true)
				{
					ms::require(pos < this->quadrants_.size(), "pos can't exceed given ragne");

					auto& quadrant_at_pos = this->quadrant_at(pos);
					switch (quadrant_at_pos)
					{
					case '1':
						quadrant_at_pos = '2';
						pos++;
						break;
					case '2':
						quadrant_at_pos = '1';
						is_end = true;
						break;
					case '3':
						quadrant_at_pos = '4';
						is_end = true;
						break;
					case '4':
						quadrant_at_pos = '3';
						pos++;
						break;
					default:
						ms::exception("Error");
					}					

					if (is_end)
					{
						break;
					}
				}
			}
		}		
	}

	void move_left(const size_t num_movement)
	{
		std::bitset<this->max_bit> binary(num_movement);

		for (size_t i = 0; i < this->max_bit; ++i)
		{
			if (binary[i])
			{
				bool is_end = false;
				auto pos = i;

				while (true)
				{
					ms::require(pos < this->quadrants_.size(), "pos can't exceed given ragne");

					auto& quadrant_at_pos = this->quadrant_at(pos);
					switch (quadrant_at_pos)
					{
					case '1':
						quadrant_at_pos = '2';
						is_end = true;
						break;
					case '2':
						quadrant_at_pos = '1';
						pos++;
						break;
					case '3':
						quadrant_at_pos = '4';
						pos++;
						break;
					case '4':
						quadrant_at_pos = '3';
						pos++;
						is_end = true;
						break;
					default:
						ms::exception("Error");
					}

					if (is_end)
					{
						break;
					}
				}
			}
		}
	}

	void move_up(const size_t num_movement)
	{
		std::bitset<this->max_bit> binary(num_movement);

		for (size_t i = 0; i < this->max_bit; ++i)
		{
			if (binary[i])
			{
				bool is_end = false;
				auto pos = i;

				while (true)
				{
					ms::require(pos < this->quadrants_.size(), "pos can't exceed given ragne");

					auto& quadrant_at_pos = this->quadrant_at(pos);

					switch (quadrant_at_pos)
					{
					case '1':
						quadrant_at_pos = '4';
						pos++;
						break;
					case '2':
						quadrant_at_pos = '3';
						pos++;
						break;
					case '3':
						quadrant_at_pos = '2';
						is_end = true;
						break;
					case '4':
						quadrant_at_pos = '1';
						is_end = true;
						break;
					default:
						ms::exception("Error");
					}

					if (is_end)
					{
						break;
					}
				}
			}
		}
	}

	void move_down(const size_t num_movement)
	{
		std::bitset<this->max_bit> binary(num_movement);

		for (size_t i = 0; i < this->max_bit; ++i)
		{
			if (binary[i])
			{
				bool is_end = false;
				auto pos = i;

				while (true)
				{
					ms::require(pos < this->quadrants_.size(), "pos can't exceed given ragne");

					auto& quadrant_at_pos = this->quadrant_at(pos);

					switch (quadrant_at_pos)
					{
					case '1':
						quadrant_at_pos = '4';
						is_end = true;
						break;
					case '2':
						quadrant_at_pos = '3';
						is_end = true;
						break;
					case '3':
						quadrant_at_pos = '2';
						pos++;
						break;
					case '4':
						quadrant_at_pos = '1';
						pos++;
						break;
					default:
						ms::exception("Error");
					}

					if (is_end)
					{
						break;
					}
				}
			}
		}
	}

	char& quadrant_at(const size_t pos)
	{
		const auto index_pos = this->quadrants_.size() - 1 - pos;
		return this->quadrants_[index_pos];
	}

private:
	static constexpr unsigned short max_bit = 51;
	std::vector<char> quadrants_;
};

int main(void)
{
	int n;
	std::cin >> n;
	std::string start_quadrants;
	std::cin >> start_quadrants;

	long long horizontal_movement, vertical_movement;
	std::cin >> horizontal_movement >> vertical_movement;

	try
	{
		Hierarchical_Quadrant hierarchical_quadrant(start_quadrants);
		try
		{
			hierarchical_quadrant.move(horizontal_movement, vertical_movement);
			hierarchical_quadrant.print();
		}
		catch (...)
		{
			std::cout << "-1";
		}
	}
	catch (const std::exception& except)
	{
		std::cout << except.what();
		std::cout << "input position is wrong. Please re-enter. \n";
		main();
	}

	return 0;
}