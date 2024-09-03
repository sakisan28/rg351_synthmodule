all : pgmchanger

pgmchanger : pgmchanger.c
	gcc -o pgmchanger pgmchanger.c -lncurses -lSDL2 -lasound

install : pgmchanger pgmchanger.sh
	sudo cp pgmchanger pgmchanger.sh /roms/ports

clean :
	rm pgmchanger
