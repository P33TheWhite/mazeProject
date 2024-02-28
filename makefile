_IGREEN=\033[42m
_WHITE=\033[1;37m
END=\033[0m
BGreen=\033[1;32m

exe: game.o event.o generation.o affichage.o main.o
	gcc -g game.o event.o generation.o affichage.o main.o -o exe
	@echo "${BGreen}[✔] TEST EXE PASSED${END}"

generation.o: generation.c generation.h structure.h
	gcc -g -c generation.c -o generation.o -Wall
	@echo "${BGreen}[✔] TEST generation PASSED${END}"

affichage.o: affichage.c affichage.h structure.h
	gcc -g -c affichage.c -o affichage.o -Wall
	@echo "${BGreen}[✔] TEST affichage PASSED${END}"
	
event.o: event.c event.h structure.h
	gcc -g -c event.c -o event.o -Wall
	@echo "${BGreen}[✔] TEST event PASSED${END}"

game.o: game.c game.h structure.h
	gcc -g -c game.c -o game.o -Wall
	@echo "${BGreen}[✔] TEST game PASSED${END}"

main.o: main.c event.h generation.h affichage.h game.h structure.h
	gcc -g -c main.c -o main.o -Wall
	@echo "${BGreen}[✔] TEST MAIN PASSED${END}"

clean:
	rm -f *.o
