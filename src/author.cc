#include <iomanip>
#include <regex>
#include "author.h"
#include "commit.h"

static long author_count;

/**
 * Author::Author() - construct unitialized Author
 *
 * Use this constructor for the find functions of an AuthorSet.
 */
Author::Author()
{
}

/**
 * Author::Author() - construct Author
 *
 * @email:	email address of the author
 */
Author::Author(std::string email)
{
	size_t i;
	std::smatch match;
	/* Select the last two parts of the email domain */
	std::regex expression(".*[@\\.](\\S+\\.\\S+)");

	this->id = ++author_count;
	this->email = email;

	std::regex_match(email, match, expression,
			 std::regex_constants::match_default);
	if (match.size() > 1) {
		this->email_domain = match.str(1);
	} else {
		this->email_domain = "";
	}

	this->commits = 0;
	this->patches = 0;

	for (i = 0; i < 24; ++i) {
		this->committer_hours[i] = 0;
		this->author_hours[i] = 0;
	}
	for (i = 0; i < 8; ++i) {
		this->committer_wdays[i] = 0;
		this->author_wdays[i] = 0;
	}
	this->first_commit = 0;
	this->last_commit = 0;
	this->first_patch = 0;
	this->last_patch = 0;
	this->commit_message_lines = 0;
	this->changed_files = 0;
	this->hunks = 0;
	this->lines_added = 0;
	this->lines_removed = 0;
}

/**
 * Author::~Author() - destroy Author
 */
Author::~Author()
{
}

/**
 * Author::add_commit() - add a commit to the author's statistics
 *
 * @commit:	commit
 */
void Author::add_commit(Commit *commit) {
	++this->commits;
	++this->committer_hours[commit->committer_hour];
	++this->committer_wdays[commit->committer_wday];
	if (!this->first_commit) {
		this->first_commit = commit->committer_timestamp;
	}
	this->last_commit = commit->committer_timestamp;
}

/**
 * Author::add_patch() - add a patch to the author's statistics
 *
 * @patch:	patch
 */
void Author::add_patch(Commit *patch) {
	++this->patches;
	++this->author_hours[patch->author_hour];
	++this->author_wdays[patch->author_wday];
	if (patch->author_timestamp && (!this->first_patch ||
	    patch->author_timestamp < this->first_patch)) {
		this->first_patch = patch->author_timestamp;
	}
	this->last_patch = patch->author_timestamp;
	this->commit_message_lines += patch->commit_message_lines;
	this->changed_files += patch->changed_files;
	this->hunks += patch->hunks;
	this->lines_added += patch->lines_added;
	this->lines_removed += patch->lines_removed;
}

/**
 * Author::less() - compare two authors
 *
 * Authors are sorted by their email address.
 *
 * @rhs:	right hand side of the comparison
 * Return:	true if this Author is alphabetically less than the other
 *		author
 */
bool Author::less(const Author *rhs) const
{
	return this->email < rhs->email;
}

std::ostream&  Author::csv_header(std::ostream& os, std::string prefix) {
	int i;
	char fill = os.fill();

	os << prefix << "id";
	os << "," << prefix << "email_domain";
	os << "," << prefix << "commits";
	for (i = 0; i < 24; ++i) {
		os << "," << prefix << "committer_hour_" <<
		   std::setfill('0') << std::setw(2) <<  i;
	}
	for (i = 1; i < 8; ++i) {
		os << "," << prefix << "committer_wday_" << i;
	}
	os << "," << prefix << "first_commit";
	os << "," << prefix << "last_commit";
	os << "," << prefix << "patches";
	for (i = 0; i < 24; ++i) {
		os << "," << prefix << "author_hour_" <<
		   std::setfill('0') << std::setw(2) <<  i;
	}
	for (i = 1; i < 8; ++i) {
		os << "," << prefix << "author_wday_" << i;
	}
	os << "," << prefix << "first_patch";
	os << "," << prefix << "last_patch";

	os << "," << prefix << "commit_message_lines";
	os << "," << prefix << "changed_files";
	os << "," << prefix << "hunks";
	os << "," << prefix << "lines_added";
	os << "," << prefix << "lines_removed";

	return os;
}

/**
 * operator<<() - write Author to CSV file
 *
 * @os:		output stream
 * @author:	Author
 */
std::ostream& operator<<(std::ostream& os, const Author& author)
{
	int i;

	os << author.id;
	os << "," << author.email_domain;
	os << "," << author.commits;
	for (i = 0; i < 24; ++i) {
		os << "," << author.committer_hours[i];
	}
	for (i = 1; i < 8; ++i) {
		os << "," << author.committer_wdays[i];
	}
	os << "," << author.first_commit;
	os << "," << author.last_commit;
	os << "," << author.patches;
	for (i = 0; i < 24; ++i) {
		os << "," << author.author_hours[i];
	}
	for (i = 1; i < 8; ++i) {
		os << "," << author.author_wdays[i];
	}
	os << "," << author.first_patch;
	os << "," << author.last_patch;
	os << "," << author.commit_message_lines;
	os << "," << author.changed_files;
	os << "," << author.hunks;
	os << "," << author.lines_added;
	os << "," << author.lines_removed;

	return os;
}
