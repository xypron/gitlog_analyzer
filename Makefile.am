SUBDIRS = src

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = m4 autogen.sh

dist-hook:
	rm -rf $(distdir)/doc/doxygen
	rm -f $(distdir)/doc/version.html
	rm -rf `find $(distdir) -name '*~'`
	rm -rf `find $(distdir) -name .git`
	rm -rf `find $(distdir) -name '*.bak'`
