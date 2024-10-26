var=hello.txt

$(var): main.o plus.o minus.o
	gcc -o $@ $^
main.o: main.c
	gcc -c main.c
plus.o: plus.c
	gcc -c plus.c
minus.o: minus.c
	gcc -c minus.c
clean:
	rm *.o $(var)
