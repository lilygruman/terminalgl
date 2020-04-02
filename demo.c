#include "terminalgl.h"

void main()
{
    char command;

    tgl_init();

    do
    {
        command = get_command();
        switch(command)
        {
            case 'b':
                set_cell_color(BLUE);
                set_glyph_color(YELLOW);
                break;
            case 'c':
                clear();
                break;
            case 'j':
                movedown(1);
                break;
            case 'k':
                moveup(1);
                break;
            case 'g':
                set_square_mode(false);
            case 'h':
                moveleft(1);
                break;
            case 'l':
                moveright(1);
                break;
            case 'q':
                break;
            case 'r':
                set_cell_color(RED);
                set_glyph_color(CYAN);
                break;
            case 's':
                set_square_mode(true);
            case 'y':
                set_cell_color(YELLOW);
                set_glyph_color(BLUE);
                break;
            default:
                set_glyph(command);
                draw();
                break;
        }
    } while(command != 'q');

    tgl_deinit();
}
