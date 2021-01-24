test:	tests/tests.cpp point.cpp cell.cpp grid.cpp
	g++ -o test tests/tests.cpp point.cpp cell.cpp grid.cpp -std=c++11
	./test
	rm test
run:	main.cpp point.cpp cell.cpp grid.cpp
	g++ -o conway main.cpp point.cpp cell.cpp grid.cpp -std=c++11
	./conway
