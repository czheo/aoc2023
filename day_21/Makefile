all: part1 part2

part1: part1.cpp
	g++ -std=c++17 -o part1 part1.cpp -Wall -Wextra -pedantic
	./part1 6 < test.txt
	./part1 64 < input.txt

part2: part2.cpp
	g++ -std=c++17 -o part2 part2.cpp -Wall -Wextra -pedantic
	./part2 6 < test.txt
	./part2 10 < test.txt
	./part2 50 < test.txt
	./part2 5000 < test.txt
	# ./part2 26501365 < input.txt

clean:
	rm -f part1 part2
