
CPP_FLAGS := -std=c++11 -c -g -Iinclude
TEST_OBJECTS := obj/test.o obj/utils.o obj/sort.o
MAIN_OBJECTS := obj/main.o obj/utils.o obj/sort.o
BENCH_OBJECTS := obj/bench.o obj/utils.o obj/sort.o

all:
	make bin/test
	make bin/sort-program
	make bin/bench

test:
	make bin/test
	bin/test

sort-program:
	make bin/sort-program
	bin/sort-program

bench:
	make bin/bench
	bin/bench

obj/main.o: src/main.cpp include/sort.hpp include/utils.hpp
	g++ ${CPP_FLAGS} -o obj/main.o src/main.cpp

obj/test.o: src/test.cpp include/sort.hpp include/utils.hpp
	g++ ${CPP_FLAGS} -o obj/test.o src/test.cpp

obj/bench.o: src/bench.cpp include/sort.hpp include/utils.hpp
	g++ ${CPP_FLAGS} -o obj/bench.o src/bench.cpp

obj/utils.o: src/utils.cpp include/utils.hpp
	g++ ${CPP_FLAGS} -o obj/utils.o src/utils.cpp

obj/sort.o: src/sort.cpp include/sort.hpp
	g++ ${CPP_FLAGS} -o obj/sort.o src/sort.cpp

bin/test: ${TEST_OBJECTS}
	g++ -std=c++11 -o bin/test ${TEST_OBJECTS}

bin/sort-program: ${MAIN_OBJECTS}
	g++ -std=c++11 -o bin/sort-program ${MAIN_OBJECTS}

bin/bench: ${BENCH_OBJECTS}
	g++ -std=c++11 -o bin/bench ${BENCH_OBJECTS}

clean:
	rm obj/* || exit 0
	rm bin/* || exit 0
	rm output.txt
