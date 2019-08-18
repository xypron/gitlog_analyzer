/* SPDX-License-Identifier: MIT */

#ifndef AUTHOR_COMPARATOR_H
#define AUTHOR_COMPARATOR_H

struct AuthorComparator {
	inline bool operator ()(const Author *left, const Author *right) const
	{
		return left->less(right);
	}
};

#endif
