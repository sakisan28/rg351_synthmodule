all : pgmchanger

pgmchanger : pgmchanger.c pdcurses.a
	gcc -o pgmchanger pgmchanger.c pdcurses.a -lncurses -lSDL2 -lasound
	chmod +x pgmchanger.sh

install : pgmchanger pgmchanger.sh
	sudo cp pgmchanger pgmchanger.sh /roms/tools

clean :
	rm -fr PDCurses
	rm pdcurses.h curspriv.h pdcurses.a pdcsdl.h

pdcurses.a :
	git clone https://github.com/wmcbrine/PDCurses
	$(MAKE) -C PDCurses/sdl2
	cp PDCurses/curses.h ./pdcurses.h
	cp PDCurses/curspriv.h .
	cp PDCurses/sdl2/pdcsdl.h .
	cp PDCurses/sdl2/pdcurses.a .
	sed -i 's/<curses.h>/\"pdcurses.h\"/g' curspriv.h
	sed -i 's/<curses.h>/\"pdcurses.h\"/g' pdcsdl.h
	sed -i 's/<SDL.h>/<SDL2\/SDL.h>/g' pdcsdl.h
	sed -i 's/<curspriv.h>/\"curspriv.h\"/g' pdcsdl.h
