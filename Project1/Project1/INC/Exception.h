#pragma once
#include <exception>
#include <string_view>
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
};