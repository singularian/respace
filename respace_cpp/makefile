# Makefile
# respace

#CCLD = $(CC)
#LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
#        $(AM_LDFLAGS) $(LDFLAGS) -o $@

respace: respace.c
	gcc -o respace respace.c
respace_stl: respace_stl.cpp
	g++ -o respace_stl respace_stl.cpp
clean:
	rm respace respace_stl
