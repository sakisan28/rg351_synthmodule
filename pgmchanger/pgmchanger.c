//
// pgmchanger.c
//     game controller midi

#include <alsa/asoundlib.h>
#include <SDL2/SDL.h>
#include "pdcurses.h"
#include "pdcsdl.h"

#include <stdio.h>
#include <unistd.h>

// B:0 A:1 X:2 Y:3 L1:4 R1:5 L2:6 R2:7 Select:8 Start:9
// L3:11 R3:12
// U:13 D:14 L:15 R:16

/*
int GM_ON_LEN = 6;
char GM_ON[] = { 0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7 };
int XG_ON_LEN = 9;
char XG_ON[] = { 0xf0, 0x43, 0x10, 0x4c, 0, 0, 0x7e, 0, 0xf7};
*/

char buf[4];

/*
enum {
	BTN_B, BTN_A, BTN_X, BTN_Y, BTN_L1, BTN_R1, BTN_L2, BTN_R2, BTN_SEL, BTN_STA,
	BTN_L3 = 11, BTN_R3,
	BTN_U = 13, BTN_D, BTN_L, BTN_R
};
*/

#define ERRCHECK(ret) if(ret < 0) { printf("%s\n", snd_strerror(ret)); abort();};

void print_ch(int x)
{
	sprintf(buf, "%03d", x + 1);
	mvprintw(1, 35, buf);
	refresh();
}

void print_pgm(int x)
{
	sprintf(buf, "%03d", x);
	mvprintw(3, 35, buf);
	refresh();
}

void print_msb(int x)
{
	sprintf(buf, "%03d", x);
	mvprintw(5, 35, buf);
	refresh();
}

void print_lsb(int x)
{
	sprintf(buf, "%03d", x);
	mvprintw(7, 35, buf);
	refresh();
}

void print_rev(int x)
{
	sprintf(buf, "%03d", x);
	mvprintw(9, 35, buf);
	refresh();
}

void print_cho(int x)
{
	sprintf(buf, "%03d", x);
	mvprintw(11, 35, buf);
	refresh();
}


void init_screen(void)
{
	noecho();
	cbreak();
	curs_set(0);
	mvprintw( 1,  1, "[SELECT]/[START]");
	mvprintw( 1, 20, "MIDI CH");
	mvprintw( 3,  1, "[DOWN]/[UP]");
	mvprintw( 3, 20, "PROGRAM");
	mvprintw( 5,  1, "[LEFT]/[RIGHT]");
	mvprintw( 5, 20, "BANK(MSB)");
	mvprintw( 7,  1, "[Y]/[X]");
	mvprintw( 7, 20, "BANK(LSB)");
	mvprintw( 9,  1, "[L1]/[R1]");
	mvprintw( 9, 20, "REVERB");
/*
	mvprintw(11,  1, "[L2]/[R2]");
	mvprintw(11, 20, "CHORUS");
*/
	mvprintw(13,  1, "[A]");
	mvprintw(13, 20, "TEST TONE");
	mvprintw(15,  1, "[B]");
	mvprintw(15, 20, "QUIT");
/*
	mvprintw(19,  1, "[L3]");
	mvprintw(19, 20, "ALL NOTES OFF");
	mvprintw(21,  1, "[R3]");
	mvprintw(21, 20, "XG ON");
*/
	print_ch(0);
	print_pgm(0);
	print_msb(0);
	print_lsb(0);
	print_rev(0);
/*
	print_cho(0);
*/
	refresh();
}

void quit_screen(void)
{
	endwin();
}


int main(int argc, char *argv[])
{
	PDCEX SDL_Window *pdc_window;
	PDCEX SDL_Surface *pdc_screen;

	SDL_Joystick *joy;
	SDL_GameController *con;
	SDL_Event event;

	snd_seq_t *seq;
	snd_seq_event_t ev;
	int oid;
	int ret;

	int quit;
	int pgm, msb, lsb, rev, cho, ch;
	int dest;
	int dest_dev = 0;

	pgm = 0;
	msb = 0;
	lsb = 0;
	rev = 0;
	cho = 0;
	ch = 0;

	if (argc != 2) {
		printf("usage: pgmchanger MIDI_alsa(aconnect)_device_number\n");
		printf("       pgmchanger 128\n");
		return 0;
	}
	sscanf(argv[1], "%d", &dest);
	if (dest < 0 || dest > 255)
		abort();
	
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO);
	pdc_window = SDL_CreateWindow("pgmchanger", SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	pdc_screen = SDL_GetWindowSurface(pdc_window);


	initscr();
	start_color();
	scrollok(stdscr, TRUE);
	PDC_set_title("pgmchanger");
	init_pair(1, COLOR_WHITE + 8, COLOR_BLUE);
	bkgd(COLOR_PAIR(1));

	init_screen();


	joy = SDL_JoystickOpen(0);

	SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
	con = SDL_GameControllerOpen(0);
	//printf("\ndebug:: joy:%d,con:%d,%s\n", (int)joy, (int)con, SDL_GetError());


	ret = snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, SND_SEQ_NONBLOCK);
	ERRCHECK(ret);
	snd_seq_set_client_name(seq, "pgmchanger");

	oid = snd_seq_create_simple_port(seq, "OUTPUT", SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_APPLICATION);
	ERRCHECK(oid);

	ret = snd_seq_connect_to(seq, oid, dest, dest_dev);
	ERRCHECK(ret);
	snd_seq_ev_clear(&ev);
	snd_seq_ev_set_source(&ev, oid);
	snd_seq_ev_set_subs(&ev);
	snd_seq_ev_set_direct(&ev);


	quit = 0;
	while (!quit) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				switch (event.cbutton.button) {
					case SDL_CONTROLLER_BUTTON_B:
					//quit
						quit = TRUE;
						break;
					case SDL_CONTROLLER_BUTTON_A:
					//test tone
						if (ch == 9){
							snd_seq_ev_set_noteon(&ev, ch, 38, 100);
						} else {
							snd_seq_ev_set_noteon(&ev, ch, 60, 100);
						}
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_BACK:
					//ch dec
						if (--ch < 0)
							ch = 0;
						print_ch(ch);
						break;
					case SDL_CONTROLLER_BUTTON_START:
					//ch inc
						if (++ch > 15)
							ch = 15;
						print_ch(ch);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					//pgm dec
						if (--pgm < 0)
							pgm = 0;
						print_pgm(pgm);
						snd_seq_ev_set_pgmchange(&ev, ch, pgm);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_UP:
					//pgm inc
						if (++pgm > 127)
							pgm = 127;
						print_pgm(pgm);
						snd_seq_ev_set_pgmchange(&ev, ch, pgm);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
					//msb dec
						if (--msb < 0)
							msb = 0;
						print_msb(msb);
						snd_seq_ev_set_controller(&ev, ch, 0, msb);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
					//msb inc
						if (++msb > 127)
							msb = 127;
						print_msb(msb);
						snd_seq_ev_set_controller(&ev, ch, 0, msb);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_Y:
					//msb dec
						if (--lsb < 0)
							lsb = 0;
						print_lsb(lsb);
						snd_seq_ev_set_controller(&ev, ch, 32, lsb);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_X:
					//msb inc
						if (++lsb > 127)
							lsb = 127;
						print_lsb(lsb);
						snd_seq_ev_set_controller(&ev, ch, 32, lsb);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
					//rev dec
						rev -= 8;
						if (rev < 0)
							rev = 0;
						print_rev(rev);
						snd_seq_ev_set_controller(&ev, ch, 91, rev);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
					//rev inc
						rev += 8;
						if (rev == 8)
							rev = 7;
						if (rev > 127)
							rev = 127;
						print_rev(rev);
						snd_seq_ev_set_controller(&ev, ch, 91, rev);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
/*
					case SDL_CONTROLLER_BUTTON_PADDLE1:
					//cho dec
						cho -= 8;
						if (cho < 0)
							cho = 0;
						print_cho(cho);
						snd_seq_ev_set_controller(&ev, ch, 93, cho);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case SDL_CONTROLLER_BUTTON_PADDLE2:
					//cho inc
						cho += 8;
						if (cho == 8)
							cho = 7;
						if (cho > 127)
							cho = 127;
						print_cho(cho);
						snd_seq_ev_set_controller(&ev, ch, 93, cho);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case BTN_L3:
					//all notes off
						snd_seq_ev_set_controller(&ev, 0, 123, 0);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
					case BTN_R3:
					//XG on
						snd_seq_ev_set_sysex(&ev, GM_ON_LEN, GM_ON);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						usleep(500000);
						snd_seq_ev_set_sysex(&ev, XG_ON_LEN, XG_ON);
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
*/
				}
			} else if (event.type == SDL_CONTROLLERBUTTONUP) {
				switch (event.cbutton.button) {
					case SDL_CONTROLLER_BUTTON_A:
						if (ch == 9){
							snd_seq_ev_set_noteoff(&ev, ch, 38, 0);
						} else {
							snd_seq_ev_set_noteoff(&ev, ch, 60, 0);
						}
						snd_seq_event_output(seq, &ev);
						snd_seq_drain_output(seq);
						break;
				}
			}
		}

	}

	SDL_GameControllerClose(con);
	SDL_JoystickClose(joy);
	SDL_Quit();
	quit_screen();
	return 0;
}
