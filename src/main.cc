/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <list>
#include <set>
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
				std::cout << "invalid Fixes: " << line
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
	commit->committer_timestamp = std::stoul(line, nullptr);
	commit->author_timestamp = std::stol(line, nullptr);

	std::getline(std::cin, line);
	commit->author_wday = day_of_week(line);
	commit->author_hour = std::stoi(line.substr(17,2), nullptr);

	return true;
}

/**
 * parse() - parse input from standard input
 */
static void parse()
{
	Commit *commit = new Commit();
	CommitList commit_list;
	CommitSet commit_set;
	FixList fixes;
	FixList::iterator fix_pos;

	while (parse_header(commit) && parse_commit_message(commit, fixes) &&
	       parse_diff(commit)) {

		commit_set.insert(commit);
		commit_list.push_back(commit);

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
 * main() - entry point
 *
 * @argc:	number of arguments
 * @argv:	arguments
 * Return:	0 on success
 */
int main(int argc, char *argv[])
{
	parse();
	return 0;
}
