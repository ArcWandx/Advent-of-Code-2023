out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra -O3

test: out
	./out < small

edit:
	nvim cpp.cpp

run: out
	./out < input

py:
	python3 py.py < input

clean:
	rm -f out

