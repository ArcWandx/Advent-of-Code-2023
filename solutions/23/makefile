out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra -O3

debug:
	g++ -o out cpp.cpp -Wall -Wextra -g -O3 -fsanitize=address -fsanitize=undefined
	./out < small_parsed

perf:
	rm perf.data*
	g++ -o out cpp.cpp -Wall -Wextra -O3 -g
	perf record --call-graph dwarf ./out < parsed
	hotspot

test2: out
	./out < small_parsed

run2: out
	./out < parsed

test:
	python py.py < small

py:
	python py.py < input

p2:
	python py.py < parsed

clean:
	rm -f out

