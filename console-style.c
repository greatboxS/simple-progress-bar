#include "console-style.h"

#define CHECK_FILE(x) \
    if (!x)           \
        return;
// ESC N	0x8E	SS2	Single Shift Two
// ESC O	0x8F	SS3	Single Shift Three
// ESC P	0x90	DCS	Device Control String
// ESC [    0x9B	CSI	Control Sequence Introducer
// ESC \	0x9C	ST	String Terminator
// ESC ]	0x9D	OSC	Operating System Command
// ESC X	0x98	SOS	Start of String
// ESC ^    0x9E	PM	Privacy Message
// ESC _	0x9F	APC	Application Program Command

#define ESC "\033"
#define CSI "\033["
// CSI n A	CUU	Cursor Up
// CSI n B	CUD	Cursor Down
// CSI n C	CUF	Cursor Forward
// CSI n D	CUB	Cursor Back
// CSI n E	CNL	Cursor Next Line
// CSI n F	CPL	Cursor Previous Line
// CSI n G	CHA	Cursor Horizontal Absolute
// CSI n ; m H	CUP	Cursor Position
// CSI n J	ED	Erase in Display
// CSI n K	EL	Erase in Line
// CSI n S	SU	Scroll Up
// CSI n T	SD	Scroll Down
// CSI n ; m f	HVP	Horizontal Vertical Position
// CSI n m	SGR	Select Graphic Rendition
// CSI 5i		AUX Port On
// CSI 4i		AUX Port Off
// CSI 6n	DSR	Device Status Report
//

void console_cursor_move(FILE *fd, int cursor_dir, int n)
{
    CHECK_FILE(fd);

    char cursor = '\0';
    switch (cursor_dir)
    {
    case CURSOR_UP:
        cursor = 'A';
        break;
    case CURSOR_DOWN:
        cursor = 'B';
        break;
    case CUSOR_FORWARD:
        cursor = 'C';
        break;
    case CURSOR_BACK:
        cursor = 'D';
        break;
    case CURSOR_NEXTLINE:
        cursor = 'E';
        break;
    case CURSOR_PREV_LINE:
        cursor = 'F';
        break;
    case CURSOR_HOR_ABSOLUTE:
        cursor = 'G';
        break;
    case CURSOR_SCROLL_UP:
        cursor = 'S';
        break;
    case CURSOR_SCROLL_DOWN:
        cursor = 'T';
        break;
    default:
        break;
    }
    fprintf(fd, CSI "%d%c", n, cursor);
}

void console_erase_display(FILE *fd, int type)
{
    CHECK_FILE(fd);
    if (type < 0 || type > 2)
        type = ERASE_TO_END;
    fprintf(fd, CSI "%dJ", (int)type);
}

void console_erase_line(FILE *fd, int type)
{
    CHECK_FILE(fd);
    if (type < 0 || type > 2)
        type = ERASE_TO_END;
    fprintf(fd, CSI "%dK", (int)type);
}

void console_set_style(FILE *fd, int type, int control, int color_bits)
{
    CHECK_FILE(fd);
    if ((int)type == 38 || (int)type == 48)
    {
        if (color_bits == COLOR_8BITS)
            fprintf(fd, CSI "%d;5;%dm", (int)type, control);
        else
            fprintf(fd, CSI "%d;2;%dm", (int)type, control);
    }
    else
    {
        printf(CSI "%dm", (int)type);
    }
}

void console_set_background(FILE *fd, int color, int type)
{
    CHECK_FILE(fd);
    console_set_style(fd, SET_BACKGRND_COLOR, color, type);
}

void console_set_forceground(FILE *fd, int color, int type)
{
    CHECK_FILE(fd);
    console_set_style(fd, SET_FOREGROUND_COLOR, color, type);
}

void console_reset_style(FILE *fd)
{
    CHECK_FILE(fd);
    console_set_style(fd, STYLE_RESET, 0, 0);
}