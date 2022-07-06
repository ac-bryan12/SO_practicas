binaries = shell d_timeday_p d_timeday_h d_clock_p d_clock_h
all:
	gcc shell.c -o shell

gettimeofday_p:
	gcc decrementar_p.c -o d_timeday_p

gettimeofday_h:
	gcc decrementar_h.c -o d_timeday_h -pthread

clock_gettime_p:
	gcc decrementar_clock_p.c -o  d_clock_p

clock_gettime_h:
	gcc decrementar_clock_h.c -o d_clock_h -pthread

.PHONY: clean

clean:
	rm -f $(binaries)

