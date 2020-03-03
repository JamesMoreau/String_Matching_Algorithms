CFLAGS = -g

all: P11 P12 P21 P22 P23

P11: P11.c vector.c
	gcc $(CFLAGS) P11.c vector.c -g -o $@

P12: P12.c
	gcc $(CFLAGS) P12.c vector.c -g -o $@

P21: P21.c
	gcc $(CFLAGS) P21.c -g -o $@

P22: P22.c
	gcc $(CFLAGS) P22.c -g -o $@

P23: P23.c
	gcc $(CFLAGS) P23.c -g -o $@

cleanWL:
	del *.exe

cleanWD:
	rm *.exe
