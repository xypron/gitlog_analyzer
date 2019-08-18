#include "author.h"
#include "commit.h"

static long author_count;

Author::Author()
{
}

Author::Author(std::string email)
{
	size_t i;

	this->id = ++author_count;
	this->email = email;
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
}

Author::~Author()
{
}

void Author::add_commit(Commit *commit) {
	++this->commits;
	++this->committer_hours[commit->committer_hour];
	++this->committer_wdays[commit->committer_wday];
}

void Author::add_patch(Commit *commit) {
	++this->patches;
	++this->author_hours[commit->author_hour];
	++this->author_wdays[commit->author_wday];
}

bool Author::less(const Author *rhs) const
{
	return this->email < rhs->email;
}

std::ostream& operator<<(std::ostream& os, const Author& author)
{
	int i;

	os << author.id << "," << author.email << "," << author.patches << "," << author.commits;
		
	for (i = 1; i < 8; ++i)
		os << "," << author.author_wdays[i];
	for (i = 1; i < 8; ++i)
		os << "," << author.committer_wdays[i];

	return os;
}
