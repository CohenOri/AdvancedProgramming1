# Ori Cohen
# ID: 207375783
# Yana Patyuk
# ID:317106755

a.out: compileAll
	g++ *.o 
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp

run:
	./a.out
