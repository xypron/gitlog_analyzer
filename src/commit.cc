/* SPDX-License-Identifier: MIT */

#include "commit.h"

Commit::Commit()
{
	this->signed_offs = 0;
	this->reviews = 0;
	this->commit_message_lines = 0;
}

Commit::~Commit()
{
}

std::ostream& operator<<(std::ostream& os, const Commit& commit)
{
	os <<
	   commit.hash << '\t' <<
	   commit.committer_email << '\t' <<
	   commit.committer_timestamp << '\t' <<
	   commit.committer_wday << '\t' <<
	   commit.committer_hour << '\t' <<
	   commit.author_email << '\t' <<
	   commit.author_timestamp << '\t' <<
	   commit.author_wday << '\t' <<
	   commit.author_hour << '\t' <<

	   commit.commit_message_lines << '\t' <<
	   commit.signed_offs << '\t' <<
	   commit.testeds << '\t' <<
	   commit.reviews << '\t' <<
	   commit.fixes << '\t' <<
	
	   commit.changed_files << '\t' <<
	   commit.hunks << '\t' <<
	   commit.lines_added << '\t' <<
	   commit.lines_removed << '\t'<<
	   "";

	return os;
}
