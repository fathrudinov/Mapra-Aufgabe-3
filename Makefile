CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

test: matrix.o vector.o unit.o test.o
	$(CXX) $(CXXFLAGS) $^ -g -o $@ 

mytest: matrix.o vector.o unit.o main.o
	$(CXX) $(CXXFLAGS) $^ -g -o $@ 

main.o: main.cpp matrix.h vector.h unit_test.h power_series.h
	$(CXX) $(CXXFLAGS) -c $< 

matrix.o: matrix.cpp matrix.h vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $<  

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $< 

clean:
	rm -f main.o matrix.o vector.o test
