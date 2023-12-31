out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra -O3

debug: cpp.cpp
	g++ -g -o out cpp.cpp -Wall -Wextra -O3 -fsanitize=address -fsanitize=undefined
	./out < input

test: out
	./out < small

run: out
	./out < input

py:
	python3 py.py < input

clean:
	rm -f out

