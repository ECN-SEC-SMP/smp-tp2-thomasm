EXEC= tp2

$(EXEC) : lit_ecrit.o utilitaires.o main.o
	g++ -o $(EXEC) lit_ecrit.o utilitaires.o main.o

main.o : main.cpp lit_ecrit.h utilitaires.h
	g++ -c -Wall main.cpp

lit_ecrit.o : lit_ecrit.cpp lit_ecrit.h
	g++ -c -Wall lit_ecrit.cpp

utilitaires.o : utilitaires.cpp utilitaires.h
	g++ -c -Wall utilitaires.cpp

clean :
	rm -f $(EXEC) *.o