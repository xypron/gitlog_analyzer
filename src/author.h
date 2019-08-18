/* SPDX-License-Identifier: MIT */

#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Commit;

class Author {

public:
	Author();
	Author(std::string);
	~Author();
	void add_commit(Commit *commit);
	void add_patch(Commit *commit);
	bool less(const Author *rhs) const;

	long id;
	std::string email;
	long commits;
	long committer_hours[24];
	long committer_wdays[8];
	long patches;
	long author_hours[24];
	long author_wdays[8];
};

std::ostream& operator<<(std::ostream&, const Author&);

#endif
