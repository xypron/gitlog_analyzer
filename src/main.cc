/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <ctime>
#include "gitlog_analyzer.h"

/**
 * starts_with() - checks if string starts with a given prefix
 *
 * @str:	string to check
 * @prefix:	prefix
 * Return:	true if str starts with prefix
 */
static bool starts_with(std::string str, std::string prefix)
{
	return (str.substr(0, prefix.length()) == prefix);
}

/**
 * parse_diff() - parse the diff section of the commit
 *
 * @commit:	commit to parse
 * Return:	true if the start token of the next commit message is found
 */
static bool parse_diff(Commit *commit)
{
	std::string line;

	while (std::getline(std::cin, line)) {
		if (starts_with(line, "diff "))
			++commit->changed_files;
		else if (starts_with(line, "@@"))
			++commit->hunks;
		else if (starts_with(line, "+"))
			++commit->lines_added;
		else if (starts_with(line, "-"))
			++commit->lines_removed;
		if (line == START_TOKEN)
			return true;
	}
	return false;
}

/**
 * parse_commit_message() - parse commit message
 *
 * @commit:	commit to parse
 * Return:	true if the starta of the diff section is found
 */
static bool parse_commit_message(Commit *commit, FixList &fixes)
{
	std::string line;

	while (std::getline(std::cin, line)) {
		++commit->commit_message_lines;

		if (starts_with(line, "Signed-off-by:")) {
			++commit->signed_offs;
		} else if (starts_with(line, "Tested-by:")) {
			++commit->testeds;
		} else if (starts_with(line, "Reviewed-by:")) {
			++commit->reviews;
		} else if (starts_with(line, "Fixes:")) {
			++commit->fixes;
			try {
				fixes.push_back(Fix(line));
			} catch (...) {
				std::cerr << "invalid Fixes: " << line
					  << std::endl;
			}


		} else if (line == DIFF_TOKEN) {
			return true;
		}
	}
	return false;
}

/**
 * day_of_week() - convert day of week
 *
 * Convert the day of week from a time stamp in RFC 2822 format to an integer.
 *
 * @date:	date in time stamp in RFC 2822 format
 * Return:	1 = Monday, 7 = Sunday, 0 = invalid
 */
static int day_of_week(std::string date)
{
	std::string wday = date.substr(0, 3);

	if (wday == "Mon")
		return 1;
	if (wday == "Tue")
		return 2;
	if (wday == "Wed")
		return 3;
	if (wday == "Thu")
		return 4;
	if (wday == "Fri")
		return 5;
	if (wday == "Sat")
		return 6;
	if (wday == "Sun")
		return 7;
	return 0;
}

/**
 * parse_header() - parse header information of a commit
 *
 * @commit:	commit to parse
 * Return:	false if at end of file
 */
static bool parse_header(Commit *commit)
{
	static unsigned long last_commit_timestamp;
	std::string line;

	if (!std::getline(std::cin, line))
		return false;
	if (line == START_TOKEN)
		std::getline(std::cin, line);

	commit->hash = line;

	std::getline(std::cin, line);
	commit->committer_email = line;

	std::getline(std::cin, line);
	commit->committer_timestamp = std::stoul(line, nullptr);

	std::getline(std::cin, line);
	commit->committer_wday = day_of_week(line);
	commit->committer_hour = std::stoi(line.substr(17,2), nullptr);

	std::getline(std::cin, line);
	commit->author_email = line;

	std::getline(std::cin, line);
	commit->author_timestamp = std::stol(line, nullptr);
	/*
	 * A patch cannot be committed before being written. Allow one day grace
	 * period for incorrect clocks.
	 */
	if (commit->author_timestamp > commit->committer_timestamp + 86400) {
		commit->author_timestamp = 0;
	}

	std::getline(std::cin, line);
	commit->author_wday = day_of_week(line);
	commit->author_hour = std::stoi(line.substr(17,2), nullptr);

	return true;
}

/**
 * parse() - parse input from standard input
 */
static void parse(CommitList &commit_list)
{
	Commit *commit = new Commit();
	CommitSet commit_set;
	FixList fixes;
	FixList::iterator fix_pos;

	while (parse_header(commit) && parse_commit_message(commit, fixes) &&
	       parse_diff(commit)) {

		commit_set.insert(commit);
		commit_list.push_front(commit);

		commit = new Commit();
	}
	commit_set.insert(commit);
	commit_list.push_back(commit);

	/* Mark fixed commits */
	for (fix_pos = fixes.begin(); fix_pos != fixes.end(); ++fix_pos) {
		Commit seek = Commit();
		CommitSet::iterator found;

		seek.hash = fix_pos->hash;
		found = commit_set.lower_bound(&seek);

		if (found != commit_set.end() &&
		    starts_with((*found)->hash, seek.hash)) {
			++(*found)->fixed;
		}
	}
}

/**
 * authors() - collect authors of patches and commits
 *
 * @author_set:		set of authors of patches and commits
 * @commit_list:	list of commits to scan for authors
 */
static void authors(AuthorSet &author_set, CommitList &commit_list)
{
	Author seek;
	AuthorSet::iterator it_auth;
	Author *author;
	CommitList::iterator pos;

	for (pos = commit_list.begin(); pos != commit_list.end(); ++pos) {
		Commit *commit = *pos;
		seek.email = commit->committer_email;
		it_auth = author_set.find(&seek);
		if (it_auth != author_set.end()) {
			author = *it_auth;
		} else {
			author = new Author(commit->committer_email);
			author_set.insert(author);
		}
		author->add_commit(commit);
		commit->committer = *author;

		seek.email = commit->author_email;
		it_auth = author_set.find(&seek);
		if (it_auth != author_set.end()) {
			author = *it_auth;
		} else {
			author = new Author(commit->author_email);
			author_set.insert(author);
		}
		author->add_patch(commit);
		commit->author = *author;
	}
}

/**
 * output_authors() - write authors to CSV file
 *
 * @os:		output stream to receive CSV file
 * @start:	authors with last activity before this Unix time will be
 *		ingnored
 */
static void output_authors(std::ostream &os, AuthorSet &author_set,
			   unsigned long start) {
	AuthorSet::iterator pos;
	
	Author::csv_header(os, "");
	os << std::endl;

	for (pos = author_set.begin(); pos != author_set.end(); ++pos) {
		Author *author = *pos;

		if (author->last_commit < start && author->last_patch < start) {
			continue;
		}

		os << *author << std::endl;
	}
}

/**
 * output_commits() - write commits to CSV file
 *
 * @os:		output stream to receive CSV file
 * @start:	commits with commit date before this Unix time will be
 *		ingnored
 */
static void output_commits(std::ostream &os, CommitList commit_list,
			   unsigned long start) {
	CommitList::iterator pos;

	Commit::csv_header(os);
	os << std::endl;

	for (pos = commit_list.begin(); pos != commit_list.end(); ++pos) {
		Commit *commit = *pos;

		if (commit->committer_timestamp < start) {
			continue;
		}

		os << *commit << std::endl;
	}
}

/**
 * main() - entry point
 *
 * @argc:	number of arguments
 * @argv:	arguments
 * Return:	0 on success
 */
int main(int argc, char *argv[])
{
	AuthorSet author_set;
	CommitList commit_list;
	std::ofstream file;
	unsigned long start = 0;

	if (argc < 3 || argc > 4) {
		std::cerr << "Usage: " << argv[0] <<
			    " authors.csv commits.csv [unix start time]"
			  << std::endl;
		return 1;
	}

	if (argc > 3) {
		start = std::stoul(argv[3], nullptr);
		time_t start_time = start;
		std::cout << "Commit activity before " <<
			     std::put_time(std::gmtime(&start_time), "%c %Z") <<
			     " will be ignored." << std::endl;
	}

	parse(commit_list);
	authors(author_set, commit_list);

	file.open(argv[1]);
	output_authors(file, author_set, start);
	file.close();
	file.open(argv[2]);
	output_commits(file, commit_list, start);
	file.close();

	return 0;
}

