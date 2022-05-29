CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE

test: main.o matrix.o vector.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 

main.o: main.cpp matrix.cpp matrix.h vector.cpp vector.h unit_test.h
	$(CXX) $(CXXFLAGS) -c $< 

matrix.o: matrix.cpp matrix.h vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $<  

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $< 

clean:
	rm -f main.o matrix.o vector.o test
