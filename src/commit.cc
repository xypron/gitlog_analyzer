/* SPDX-License-Identifier: MIT */

#include "commit.h"

/**
 * Commit::Commit() - create new commit
 */
Commit::Commit()
{
	this->commit_message_lines = 0;
	this->signed_offs = 0;
	this->testeds = 0;
	this->reviews = 0;
	this->fixes = 0;
	this->changed_files = 0;
	this->hunks = 0;
	this->lines_added = 0;
	this->lines_removed = 0;
	this->fixed = 0;
}

/**
 * Commit::~Commit() - destroy commit
 */
Commit::~Commit()
{
}

/**
 * Commit::less() - compare two commits by hash
 *
 * @rhs:	right hand side of comparison
 * Return:	true if this commit's hass less then other commit's hash
 */
bool Commit::less(const Commit *rhs) const
{
	return this->hash < rhs->hash;
}

/**
 * Commit::csv_header() - write CSV header for commits
 *
 * @os:		output stream
 * Return:	output stream
 */
std::ostream& Commit::csv_header(std::ostream& os)
{
	os << "hash" << ",committer_timestamp" <<
	      ",committer_wday" << ",committer_hour" << ",author_timestamp" <<
	      ",author_wday" << ",author_hour" << ",commit_message_lines" <<
	      ",signed_offs" << ",testeds" << ",reviews" << ",fixes" <<
	      ",changed_files" << ",hunks" << ",lines_added" <<
	      ",lines_removed" << ",fixed,";
	      Author::csv_header(os, "author_");
	      os << ",";
	      Author::csv_header(os, "committer_");

	return os;
}

/**
 * operator<<() - write commit to CSV file
 *
 * @os:		output stream
 * @commit:	commit
 * Return:	output stream
 */
std::ostream& operator<<(std::ostream& os, const Commit& commit)
{
	os <<
	   commit.hash << ',' <<
	   commit.committer_timestamp << ',' <<
	   commit.committer_wday << ',' <<
	   commit.committer_hour << ',' <<
	   commit.author_timestamp << ',' <<
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

	   commit.fixed << ',' <<

	   commit.author << ',' <<
	   commit.committer;

	return os;
}
