/* SPDX-License-Identifier: MIT */

#include "commit.h"

Commit::Commit()
{
	this->signed_offs = 0;
	this->reviews = 0;
	this->commit_message_lines = 0;
	this->fixes = 0;
	this->fixed = 0;
}

Commit::~Commit()
{
}

bool Commit::less(const Commit *rhs) const
{
	return this->hash < rhs->hash;
}

std::ostream& Commit::csv_header(std::ostream& os)
{
	os << "hash" << ",committer_wday" << ",committer_hour" <<
	      ",author_wday" << ",author_hour" << ",commit_message_lines" <<
	      ",signed_offs" << ",testeds" << ",reviews" << ",fixes" <<
	      ",changed_files" << ",hunks" << ",lines_added" <<
	      ",lines_removed" << ",fixes,";
	      Author::csv_header(os, "author_");
	      os << ",";
	      Author::csv_header(os, "committer_");

	return os;
}

std::ostream& operator<<(std::ostream& os, const Commit& commit)
{
	os <<
	   commit.hash << ',' <<
	   commit.committer_wday << ',' <<
	   commit.committer_hour << ',' <<
	   commit.author_wday << ',' <<
	   commit.author_hour << ',' <<

	   commit.commit_message_lines << ',' <<
	   commit.signed_offs << ',' <<
	   commit.testeds << ',' <<
	   commit.reviews << ',' <<
	   commit.fixes << ',' <<

	   commit.changed_files << ',' <<
	   commit.hunks << ',' <<
	   commit.lines_added << ',' <<
	   commit.lines_removed << ','<<

	   commit.author << ',' <<
	   commit.committer;

	return os;
}
