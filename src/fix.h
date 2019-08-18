/* SPDX-License-Identifier: MIT */

#ifndef FIX_H
#define FIX_H

class Fix
{

public:
	Fix(std::string line);
	~Fix();

	std::string hash;
};

std::ostream& operator<<(std::ostream&, const Fix&);

#endif
