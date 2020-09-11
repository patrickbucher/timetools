CC=gcc
CFLAGS=-Wall -std=c99

.PHONY: all test memtest clean 

.SUFFIXES: .c .o
.c .o:
	${CC} ${CFLAGS} -c $<

all: countdown timecalc

countdown: countdown.o timefmt.o
	${CC} ${CFLAGS} -o $@ countdown.o timefmt.o
	
timecalc: timecalc.o timefmt.o
	${CC} ${CFLAGS} -o $@ timecalc.o timefmt.o

test: test_timefmt
	./test_timefmt

test_timefmt: test_timefmt.o timefmt.o
	${CC} ${CFLAGS} $^ -o test_timefmt

memtest: test_timefmt countdown
	valgrind ./test_timefmt
	valgrind ./countdown 3s

clean:
	rm -f countdown timecalc test_timefmt *.o
