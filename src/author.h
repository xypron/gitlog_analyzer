/* SPDX-License-Identifier: MIT */

#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Commit;

/**
 * class Author - author or committer of a patch
 */
class Author {

public:
	Author();
	Author(std::string);
	~Author();
	void add_commit(Commit *commit);
	void add_patch(Commit *commit);
	bool less(const Author *rhs) const;
	static std::ostream& csv_header(std::ostream& os, std::string prefix);

	unsigned int id;
	std::string email;
	std::string email_domain;
	unsigned int commits;
	unsigned int committer_hours[24];
	unsigned int committer_wdays[8];
	unsigned long first_commit;
	unsigned long last_commit;
	unsigned int patches;
	unsigned int author_hours[24];
	unsigned int  author_wdays[8];
	unsigned long first_patch;
	unsigned long last_patch;
};

std::ostream& operator<<(std::ostream&, const Author&);

#endif
