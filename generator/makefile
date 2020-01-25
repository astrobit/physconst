files=$(patsubst %.cpp,%,$(wildcard *.cpp))
all:$(files)

%: %.cpp
	g++ --std=c++17 $< `pkg-config -cflags xastro-1` -o $(patsubst %.cpp,%,$<) `pkg-config -libs xastro-1`

clean:
	-rm $(files)
	-rm *.o

