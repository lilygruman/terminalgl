#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "terminalgl.h"

const char CSI[] = "\033[";
const static int BG_COLOR_OFFSET = 40;
const static int GLYPH_COLOR_OFFSET = 30;

static struct winsize size;
static struct winsize size_old;
static struct termios settings_old;
static char glyph = ' ';
static bool square_mode = true;

void handle_resize();

void clear()
{
    set_cell_color(BLACK);
    set_glyph_color(WHITE);
    printf("%s2J", CSI);
    moveto(0, 0);
}

void draw()
{
    if (square_mode)
    {
        printf("  ");
    }
    else
    {
        printf("%c", glyph);
    }
    moveleft(1);
}

void moveto(int x, int y)
{
    printf("%s%d;%dH", CSI, y + 1, x + 1);
}

void moveup(int n)
{
    while(n > 0)
    {
        printf("%sA", CSI);
        n--;
    }
}

void movedown(int n)
{
    while(n > 0)
    {
        printf("%sB", CSI);
        n--;
    }
}

void moveright(int n)
{
    n = square_mode ? 2 * n : n;
    while(n > 0)
    {
        printf("%sC", CSI);
        n--;
    }
}

void moveleft(int n)
{
    n = square_mode ? 2 * n : n;
    while(n > 0)
    {
        printf("%sD", CSI);
        n--;
    }
}

void set_glyph(char g)
{
    glyph = g;
}

void set_cell_color(color c)
{
    printf("%s%dm", CSI, c + BG_COLOR_OFFSET);
}

void set_glyph_color(color c)
{
    printf("%s%dm", CSI, c + GLYPH_COLOR_OFFSET);
}

void set_square_mode(bool on)
{
    square_mode = on;
}

void tgl_init()
{
    struct termios settings_new;

    // Save terminal settings
    tcgetattr( STDIN_FILENO, &settings_old);
    settings_new = settings_old;

    // Report characters one by one and turn off echo
    settings_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &settings_new);

    // Make pixels square but keep terminal height
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_old);
    size = size_old;
    /*
    size.ws_row *= (size.ws_ypixel / size.ws_xpixel);
    */
    size.ws_ypixel = size.ws_xpixel;
    ioctl(STDOUT_FILENO, TIOCSWINSZ, &size);
    handle_resize();
}

void tgl_deinit()
{
    clear();

    // Restore terminal sizes and settings
    ioctl(STDOUT_FILENO, TIOCSWINSZ, &size_old);
    tcsetattr( STDIN_FILENO, TCSANOW, &settings_old);
}

char get_command()
{
    return getchar() & 0xFF;
}

void handle_resize()
{
    signal(SIGWINCH, SIG_IGN);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    clear();
    signal(SIGWINCH, handle_resize);
}

