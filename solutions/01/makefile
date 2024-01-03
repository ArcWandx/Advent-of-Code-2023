bin: bin/part1 bin/part2 bin/part1_alt

bin/part1: src/part1.cpp
	g++ -o bin/part1 src/part1.cpp -Wall -Wextra -g

bin/part1.alt: src/part1.alt.cpp
	g++ -o bin/part1.alt src/part1.alt.cpp -Wall -Wextra -g

bin/part2: src/part2.cpp
	g++ -o bin/part2 src/part2.cpp -Wall -Wextra -g

clean:
	rm -f bin/*

p1: bin/part1
	./bin/part1 < input/input

p1_alt: bin/part1.alt
	./bin/part1.alt < input/input

p2: bin/part2
	./bin/part2 < input/input

p2_alt: bin/part1
	./bin/part1 < input/replaced

