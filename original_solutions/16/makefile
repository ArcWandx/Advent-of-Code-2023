out: src/cpp.cpp
	g++ -o out src/cpp.cpp -Wall -Wextra -O3 -fopenmp

debug:
	g++ -o out src/cpp.cpp -Wall -Wextra -O3 -g -fsanitize=address -fsanitize=undefined
	./out < input/big

perf:
	touch perf.data && rm perf.data*
	g++ -o out src/cpp.cpp -Wall -Wextra -O3 -g -fopenmp
	perf record --call-graph dwarf ./out < input/big
	hotspot

edit:
	nvim src/cpp.cpp
test: out
	./out < input/small
repl:
	sed -i "s/constexpr int SIZE = \\([0-9]*\\);/constexpr int SIZE = $(ARGS);/" src/cpp.cpp

run: out
	./out < input/input
110: out
	sed -i "s/constexpr int SIZE = \\([0-9]*\\);/constexpr int SIZE = 110;/" src/cpp.cpp
	./out < input/input

large: out
	./out < input/large
220: out
	sed -i "s/constexpr int SIZE = \\([0-9]*\\);/constexpr int SIZE = 220;/" src/cpp.cpp
	./out < input/large

extralarge: out
	./out < input/extralarge
440: out
	sed -i "s/constexpr int SIZE = \\([0-9]*\\);/constexpr int SIZE = 440;/" src/cpp.cpp
	./out < input/extralarge

big: out
	./out < input/big
880: out
	sed -i "s/constexpr int SIZE = \\([0-9]*\\);/constexpr int SIZE = 880;/" src/cpp.cpp
	./out < input/big

evenbigger: out
	./out < input/evenbigger
1760: out
	sed -i "s/constexpr int SIZE = \\([0-9]*\\);/constexpr int SIZE = 1760;/" src/cpp.cpp
	./out < input/evenbigger

clean:
	rm -f out

