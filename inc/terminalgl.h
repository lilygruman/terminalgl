#include <stdbool.h>

typedef enum
{
    BLACK   = 0,
    RED     = 1,
    GREEN   = 2,
    YELLOW  = 3,
    BLUE    = 4,
    MAGENTA = 5,
    CYAN    = 6,
    WHITE   = 7
} color;

void clear();
void draw();
char get_command();
void moveto(int x, int y);
void moveup(int n);
void movedown(int n);
void moveright(int n);
void moveleft(int n);
void set_glyph(char g);
void set_cell_color(color c);
void set_glyph_color(color c);
void set_square_mode(bool on);
void tgl_init();
void tgl_deinit();
