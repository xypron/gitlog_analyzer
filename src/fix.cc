/* SPDX-License-Identifier: MIT */

#include <regex>
#include "fix.h"

Fix::Fix(std::string line)
{
	std::smatch match;
	std::regex expression("Fixes:\\s+([a-f,0-9]{8,40})\\b.*");

	std::regex_match(line, match, expression, std::regex_constants::match_default);
	if (match.size() > 1)
		this->hash = match.str(1);
	else
		throw 0;
}

Fix::~Fix()
{
}

std::ostream& operator<<(std::ostream& os, const Fix& fix)
{
	os << "Fixes: " << fix.hash;
	return os;
}
