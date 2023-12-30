out: test.cpp
	g++ -o out test.cpp -Wall -Wextra

part1: part1.cpp
	g++ -o part1 part1.cpp -Wall -Wextra

.PHONY: edit clean run replaced p1
edit:
	nvim test.cpp

clean:
	rm -f out part1

run: out
	./out < input

replaced: part1
	./part1 < replaced

p1: part1
	./part1 < input
