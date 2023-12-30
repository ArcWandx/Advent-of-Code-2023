test: out
	./out < small

run: out
	./out ${ARGS} < input

py:
	python3 py.py < input

out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra -O3

clean:
	rm -f out

