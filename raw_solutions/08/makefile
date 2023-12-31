test: out
	./out < small

run: out
	./out < parsed

out: cpp.cpp
	g++ -o out cpp.cpp -Wall -Wextra

clean:
	rm -f out

