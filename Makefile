exec = pr55.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flats = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)


%.o: %;c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./pr55.out /usr/local/bin/pr55

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o