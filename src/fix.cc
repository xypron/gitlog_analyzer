/* SPDX-License-Identifier: MIT */

#include <regex>
#include "fix.h"

/**
 * Fix::Fix() - construct a 'Fixes:' information
 *
 * @line:	'Fixes:' line from the commit message
 */
Fix::Fix(std::string line)
{
	std::smatch match;
	/*
	 * Select the hash of the fixed commit. This should be at least a 12
	 * character hexadecimal string but some committers use a shorter one.
	 */
	std::regex expression(".*[^a-f,0-9]([a-f,0-9]{8,40}).*");

	std::regex_match(line, match, expression, std::regex_constants::match_default);
	if (match.size() > 1) {
		this->hash = match.str(1);
	} else {
		throw 0;
	}
}

/**
 * Fix::~Fix() - destroy a 'Fixes:' information
 */
Fix::~Fix()
{
}

/**
 * operator<<() - write the commit hash to an output stream
 *
 * @os:		output stream
 * @fix:	Fix with the hash
 */
std::ostream& operator<<(std::ostream& os, const Fix& fix)
{
	os << "Fixes: " << fix.hash;
	return os;
}
