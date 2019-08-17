/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include "gitlog_analyzer.h"

static bool starts_with(std::string str, std::string match)
{
	return (str.substr(0, match.length()) == match);
}

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

static bool parse_body(Commit *commit)
{
	std::string line;

	while (std::getline(std::cin, line)) {
		++commit->commit_message_lines;

		if (starts_with(line, "Signed-off-by:"))
			++commit->signed_offs;
		else if (starts_with(line, "Tested-by:"))
			++commit->testeds;
		else if (starts_with(line, "Reviewed-by:"))
			++commit->reviews;
		else if (starts_with(line, "Fixes:"), 0)
			++commit->fixes;
		else if (line == DIFF_TOKEN)
			return true;

	}
	return false;
}

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
		return 8;
	return 0;
}

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

static void parse()
{
	Commit *commit = new Commit();

	while (parse_header(commit) && parse_body(commit) &&
	       parse_diff(commit)) {
		std::cout << *commit << std::endl;
		commit->~Commit();		
		commit = new Commit();
	}
	std::cout << *commit << std::endl;
	commit->~Commit();		
}

int main(int argc, char *argv[])
{
	std::cout << "Hello world" << std::endl;
	parse();
	return 0;
}
