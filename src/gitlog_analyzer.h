/* SPDX-License-Identifier: MIT */

#ifndef GITLOG_ANALYZER_H
#define GITLOG_ANALYZER_H

#include "author.h"
#include "author_comparator.h"
#include "commit.h"
#include "commit_comparator.h"
#include "fix.h"

#define START_TOKEN "]start::commit["
#define DIFF_TOKEN "]start::diff["

typedef std::set<Author *, AuthorComparator> AuthorSet;
typedef std::list<Commit *> CommitList;
typedef std::set<Commit *, CommitComparator> CommitSet;
typedef std::list<Fix> FixList;

#endif
