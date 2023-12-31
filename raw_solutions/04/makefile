test:
	python3 py.py < small

run: out
	./out < input

py:
	python3 py.py < input

out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra

clean:
	rm -f out

