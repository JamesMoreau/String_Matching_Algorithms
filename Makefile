CFLAGS = -g

all: P11 P12 P21 P22 P23 P24

P11: P11.c vector.c
	gcc $(CFLAGS) P11.c vector.c -o $@

P12: P12.c
	gcc $(CFLAGS) P12.c vector.c -o $@

P21: P21.c
	gcc $(CFLAGS) P21.c -o $@

P22: P22.c
	gcc $(CFLAGS) P22.c -o $@

P23: P23.c
	gcc $(CFLAGS) P23.c -o $@

P24: P24.c
	gcc $(CFLAGS) P24.c -o $@

cleanWL:
	del *.exe

cleanWD:
	rm *.exe
