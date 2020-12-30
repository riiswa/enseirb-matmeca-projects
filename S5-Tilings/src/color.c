#include "color.h"
#include "colors.h"
#include <string.h>

enum enum_color { MAGENTA,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    CYAN,
    WHITE,
    GRAY,
    BRIGHT_RED,
    BRIGHT_GREEN,
    BRIGHT_YELLOW,
    BRIGHT_BLUE,
    BRIGHT_MAGENTA,
    BRIGHT_CYAN,
    BRIGHT_WHITE,
    ERROR = -1 };

const char* array_ansi[SIZE] = { "\033[1;35m", "\033[1;31m", "\033[1;32m", "\033[1;34m", "\033[1;33m", "\033[1;30m", "\033[1;36m", "\033[1;30m", "\033[1;90m", "\033[1;91m", "\033[1;92m", "\033[1;93m", "\033[1;94m", "\033[1;95m", "\033[1;96m", "\033[1;97m", "" };

struct color {
    enum enum_color id;
};

struct color colors[SIZE] = { { MAGENTA }, { RED }, { GREEN }, { BLUE }, { YELLOW }, { BLACK }, { CYAN }, { WHITE }, { GRAY }, { BRIGHT_RED }, { BRIGHT_GREEN }, { BRIGHT_YELLOW }, { BRIGHT_BLUE }, { BRIGHT_MAGENTA }, { BRIGHT_CYAN }, { BRIGHT_WHITE }, { ERROR } };

int index_of(const char* tab[], const char* word)
{
    for (int i = 0; (SIZE - 1); ++i) {
        if (strcmp(tab[i], word) == 0)
            return i;
    }
    return -1;
}

const char* color_name(struct color* t)
{

    if (t->id == -1)
        return array_name[SIZE - 1];
    return array_name[t->id];
}

const char* color_cstring(struct color* t)
{

    if (t->id == -1)

        return array_ansi[SIZE - 1];

    return array_ansi[t->id];
}

struct color* color_from_name(const char* name)
{

    int index = index_of(array_name, name);
    if (index != -1)
        return &colors[index];
    else
        return &colors[SIZE - 1];
}
