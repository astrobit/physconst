files=$(patsubst %.cpp,%,$(wildcard *.cpp))
all:$(files)

%: %.cpp
	$(CXX) $(CFLAGS) --std=c++11 $< `pkg-config -cflags xastro-1` -o $(patsubst %.cpp,%,$<) `pkg-config -libs xastro-1`

clean:
	-rm $(files)
	-rm *.o

