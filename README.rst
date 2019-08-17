Git Log Analyzer
================

The Git Log Analyzer parses a Git log and creates a CSV file which can serve
as a basis for an analyis of commit behavior.

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
    --full-diff -p . | gitlog_analyzer > result.csv

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
