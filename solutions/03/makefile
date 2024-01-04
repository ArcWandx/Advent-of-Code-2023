bin: bin/part1 bin/part2

bin/part1: src/part1.cpp
	g++ -o bin/part1 src/part1.cpp -Wall -Wextra

bin/part2: src/part2.cpp
	g++ -o bin/part2 src/part2.cpp -Wall -Wextra

clean:
	rm -f bin/*

p1: bin/part1
	bin/part1 < input

p2: bin/part2
	bin/part2 < input

