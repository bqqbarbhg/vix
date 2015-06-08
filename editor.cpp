#include "prelude.h"

struct Line
{
	U32 length;
	const char *text;
};

struct Buffer
{
	char *name;
	char **lines;
};

struct Cursor
{
	U32 row, col;
};

Cursor set_row(Cursor c, U32 row) {
	c.row = row;
	return c;
}
Cursor set_col(Cursor c, U32 col) {
	c.col = col;
	return c;
}

struct View
{
	Buffer *buffer;
	Cursor cursor;
};

const char *get_line(const View* view, U32 row) {
	return view->lines[row];
}

