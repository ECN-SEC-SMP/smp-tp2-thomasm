EXEC= tp2
CXXFLAGS= -g -O0 -Wall -std=c++17

$(EXEC) : lit_ecrit.o utilitaires.o main.o
	g++ -o $(EXEC) lit_ecrit.o utilitaires.o main.o

main.o : main.cpp lit_ecrit.h utilitaires.h
	g++ -c $(CXXFLAGS) main.cpp

lit_ecrit.o : lit_ecrit.cpp lit_ecrit.h
	g++ -c $(CXXFLAGS) lit_ecrit.cpp

utilitaires.o : utilitaires.cpp utilitaires.h
	g++ -c $(CXXFLAGS) utilitaires.cpp

clean :
	rm -f $(EXEC) *.o