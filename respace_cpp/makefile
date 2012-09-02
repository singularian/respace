# Makefile
# Flex Multiscript
# CC = g++
#
#
#
#

#CCLD = $(CC)
#LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
#        $(AM_LDFLAGS) $(LDFLAGS) -o $@

testscanner: testscanner.c
	gcc -o testscanner testscanner.c
testscanner_stl: testscanner_stl.cpp
	g++ -o testscanner_stl testscanner_stl.cpp
despace.c: despace.l
	flex -t despace.l > despace.c
despace: despace.c
	gcc -o despace despace.c
respace: respace.cpp
	g++ -o respace respace.cpp
clean:
	rm despace.c despace.o despace testscanner testscanner_stl
