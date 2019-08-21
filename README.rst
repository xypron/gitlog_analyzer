Git Log Analyzer
================

The Git Log Analyzer parses a Git log and creates two CSV files which can serve
as a basis for an analyis of the commit behavior.

Building
--------

The software can be built with::

    git clone https://github.com/xypron/gitlog_analyzer
    cd gitlog_analyzer
    ./autogen.sh
    ./configure
    make

It is installed with::

    sudo make install

Usage
-----

In the Git directory execute::

    git log --date=iso-strict --no-merges \
    --pretty=']start::commit[%n%H%n%cE%n%ct%n%cD%n%aE%n%at%n%aD%n%B%n]start::diff[' \
    --full-diff -p . | gitlog_analyzer authors.csv commits.csv

To output only data since a give Unix time stamp (2013.01.01T00:00:00Z)::

    git log --date=iso-strict --no-merges \
    --pretty=']start::commit[%n%H%n%cE%n%ct%n%cD%n%aE%n%at%n%aD%n%B%n]start::diff[' \
    --full-diff -p . | gitlog_analyzer authors.csv commits.csv 1356998400

File format
-----------

authors.csv
~~~~~~~~~~~

This file describes the authors and commiters of the patches.

* id - number identifying the author
* email_domain - email domain of the author
* commits - number of commits by the author
* committer_hour_xx - number of commits in hour xx of the day
* committer_wday_y - number of commits on the day y of the week (1 = Monday)
* first_commit - Unix timestamp of the first commit by the author
* last_commit - Unix timestamp of the last commit
* patches - number of patches by the authors
* author_hour_xx - number of patches in hour xx of the day
* author_wday_y - number of patches on the day y of the week (1 = Monday)
* first_patch - Unix timestamp of the first patch by the author
* last_patch - Unix timestamp of the last patch
* commit_message_lines - total number of commit lines by the author
* changed_files - total number of changed files by the author
* hunks - total number of changed hungs by the author
* lines_added - total number of lines added by the author
* lines_removed - total number of lines removed by the author

commits.csv
~~~~~~~~~~~

This file describes the commits.

* hash - hash of the commit
* committer_timestamp - timestamp when committed
* committer_wday - weekday when committed
* committer_hour - hour of the day when committed
* author_timestamp - timestamp when the patch was authored
* author_wday - weekday when the patch was authored
* author_hour - hour of the day when the patch was authored
* commit_message_lines - number of lines in the commit message
* signed_offs - number of 'Signed-off-by:' for the commit
* testeds - number of 'Tested-by:' for the commit
* reviews - number of the 'Reviewed-by:' for the commit
* fixes - number of the 'Fixes:' lines in the commit message
* changed_files - number of the files changed by the commit
* hunks - number of the hunks changed by the commit
* lines_added - number of the lines added by the commit
* lines_removed - number of the lines removed by the commit
* fixed - number of patches that fixed this commit
* author_* - author with statistic measures at the time of the commit
* committer_* - committer with statistic measures at the time of the commit

License
-------

The MIT License

Copyright 2019 Heinrich Schuchardt <xypron.glpk@gmx.de>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
