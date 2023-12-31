out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra -O3

debug:
	g++ -o out cpp.cpp -Wall -Wextra -g -fsanitize=address -fsanitize=undefined
	./out < small

test: out
	./out < small

run: out
	./out < input

py:
	python3 py.py < input

clean:
	rm -f out

