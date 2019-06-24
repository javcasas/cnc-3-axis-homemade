test: test.out
	LD_LIBRARY_PATH=Criterion ./test.out --ascii

test.out: test/test.c Controller/traverse.ino Controller/comms_parser.ino
	gcc -o test.out test/test.c -lcriterion -I Criterion/include -L Criterion/

setup:
	sudo apt install cmake
	ls Criterion || git clone https://github.com/Snaipe/Criterion.git
	cd Criterion && git checkout v2.3.3
	cd Criterion && cmake . && cmake --build .

.PHONY: test setup
