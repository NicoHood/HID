#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#if defined(OS_LINUX) || defined(OS_MACOSX)
#include <sys/ioctl.h>
#include <termios.h>
#elif defined(OS_WINDOWS)
#include <conio.h>
#endif

#include "hid.h"


static char get_keystroke(void);


int main()
{
	int i, r, num;
	char c, buf[200];

	// C-based example is 16C0:0480:FFAB:0200
	r = rawhid_open(1, 0x16C0, 0x0480, 0xFFAB, 0x0200);
	if (r <= 0) {
		// Arduino-based example is 0x2341:XXXX:FFC0:0C00
		// To keep compatible with other vendors we only use the raw HID number
		r = rawhid_open(1, -1, -1, 0xFFC0, 0x0C00);
		if (r <= 0) {
			printf("no rawhid device found\n");
			return -1;
		}
	}
	printf("found rawhid device\n");

	while (1) {
		// check if any Raw HID packet has arrived
		num = rawhid_recv(0, buf, 64, 220);
		if (num < 0) {
			printf("\nerror reading, device went offline\n");
			rawhid_close(0);
			return 0;
		}
		if (num > 0) {
			printf("\nrecv %d bytes:\n", num);
			for (i=0; i<num; i++) {
				printf("%02X ", buf[i] & 255);
				if (i % 16 == 15 && i < num-1) printf("\n");
			}
			printf("\n");
		}
		// check if any input on stdin
		while ((c = get_keystroke()) >= 32) {
			printf("\ngot key '%c', sending...\n", c);
			buf[0] = c;
			for (i=1; i<sizeof(buf); i++) {
				buf[i] = i;
			}
			rawhid_send(0, buf, sizeof(buf), 100);
		}
	}
}

#if defined(OS_LINUX) || defined(OS_MACOSX)
// Linux (POSIX) implementation of _kbhit().
// Morgan McGuire, morgan@cs.brown.edu
static int _kbhit() {
	static const int STDIN = 0;
	static int initialized = 0;
	int bytesWaiting;

	if (!initialized) {
		// Use termios to turn off line buffering
		struct termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initialized = 1;
	}
	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}
static char _getch(void) {
	char c;
	if (fread(&c, 1, 1, stdin) < 1) return 0;
	return c;
}
#endif


static char get_keystroke(void)
{
	if (_kbhit()) {
		char c = _getch();
		if (c >= 32) return c;
	}
	return 0;
}


