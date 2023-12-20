all: part1 part2

part1: part1.cpp
	g++ -std=c++17 -o part1 part1.cpp -Wall -Wextra -pedantic
	./part1 < test.txt
	./part1 < test2.txt
	./part1 < input.txt

part2: part2.cpp
	g++ -std=c++17 -o part2 part2.cpp -Wall -Wextra -pedantic
	./part2 < input.txt

clean:
	rm -f part1 part2
