CFLAGS = -g

exec = pr55.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) -o $(exec)


%.o: %;-g include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./pr55.out /usr/local/bin/pr55

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o