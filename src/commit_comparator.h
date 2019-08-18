/* SPDX-License-Identifier: MIT */

#ifndef COMMIT_COMPARATOR_H
#define COMMIT_COMPARATOR_H

struct CommitComparator {
	inline bool operator ()(const Commit *left, const Commit *right) const
	{
		return left->less(right);
	}
};

#endif
