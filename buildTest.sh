g++ -g -Wall -std=c++11  -I./dep/include -L./dep/lib -lpthread -lmongoc-1.0 -lbson-1.0 test.cpp -o test -Wl,-rpath=dep/lib

