 CXXFLAGS = -std=c++17 -Wextra -Wpedantic -O2 -fno-inline -fPIC -fPIE
# CXXFLAGS = -std=c++17 -Wall -g -O0 

test: matrix.o vector.o unit.o test.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 

mytest: matrix.o vector.o unit.o main.o unit_test.h
	$(CXX) $(CXXFLAGS) $^ -o $@ 

main.o: main.cpp matrix.h vector.h unit_test.h power_series.h
	$(CXX) $(CXXFLAGS) -c $< 

matrix.o: matrix.cpp matrix.h vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $<  

vector.o: vector.cpp vector.h
	$(CXX) $(CXXFLAGS) -c $< 

clean:
	rm -f main.o matrix.o vector.o test mytest
