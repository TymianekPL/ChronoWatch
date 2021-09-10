#include <stdio.h>
#include <string.h>

enum Color
{
     ForeBlack,
     ForeBlue,
     ForeGreen,
     ForeCyan,
     ForeRed,
     ForePink,
     ForeBrown,
     ForeGray,
     ForeDarkGray,
     ForeLightBlue,
     ForeLightGreen,
     ForeLightCyan,
     ForeLightRed,
     ForeLightPink,
     ForeLightYellow,
     ForeWhite
};

const int colorDefault = 7;
const int MaxPrintLenght = 6;

const int _position = 753664;

void print_char_in(const char *toPrint, const int position, enum Color term_color)
{
     int x = position;
     char *video_memory = (char *)x;
     *video_memory = toPrint;
     video_memory++;
     *video_memory = (char *)term_color;
}
int line = 0;
int column = 0;
void print_char(char *toPrint, enum Color term_color)
{
     print_char_in(toPrint, _position + (line * 2) + (column * 200), term_color);
     line++;
}

int ColorToBack(enum Color color)
{
     return color << 4;
}

/// <summary>
/// Set cursor position to next line
/// </summary>
void next_line()
{
     line = 0;
     column++;
}

void print_string(char string[], enum Color term_color)
{
     for (int i = 0; i < sizeof(string) - 2; i++)
     {
          char *x = string[i];
          print_char(x, term_color);
     }
}

void clear_screen(enum Color color)
{
     line = 0;
     column = 0;
     for (size_t i = 0; i < 600; i++)
     {
          print_string("     ", ColorToBack(color));
     }
     line = 0;
     column = 0;
}
