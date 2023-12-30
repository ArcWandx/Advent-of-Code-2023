out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra

.PHONY: clean run py
clean:
	rm -f out

run: out
	./out < input

py:
	python3 py.py < input

