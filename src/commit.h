/* SPDX-License-Identifier: MIT */

#ifndef COMMIT_H
#define COMMIT_H

#include <iostream>
#include <string>
#include "author.h"

class Commit
{

public:
	Commit();
	~Commit();
	bool less(const Commit *) const;
	static std::ostream& csv_header(std::ostream& os);

	// header
	std::string hash;
	std::string committer_email;
	unsigned long committer_timestamp;
	int committer_wday;
	int committer_hour;
	std::string author_email;
	unsigned long author_timestamp;
	int author_wday;
	int author_hour;
	Author author;
	Author committer;

	// commit message
	unsigned int commit_message_lines;
	unsigned int signed_offs;
	unsigned int testeds;
	unsigned int reviews;
	unsigned int fixes;

	// diff
	unsigned int changed_files;
	unsigned int hunks;
	unsigned int lines_added;
	unsigned int lines_removed;

	// other
	unsigned int fixed;

};

std::ostream& operator<<(std::ostream&, const Commit&);

#endif
