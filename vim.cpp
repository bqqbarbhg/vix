
// Find the first non-space character in a line
U32 first_nonspace_col(const View *view, U32 row) {
	Line *line = get_line(view, row);
	const U32 length = line->length;
	U32 col;
	for (col = 0; col < length; col++) {
		if (!isspace(line->text[col])) {
			break;
		}
	}
	return col;
}

// Move the cursor one line up
// Vim mapping: k; General mapping: Up
Cursor move_up(const View *view, Cursor cursor) {
	if (cursor.row > 0) {
		cursor.row--;
	}
	return cursor;
}

// Move the cursor one line up
// Vim mapping: j; General mapping: Down
Cursor move_down(const View *view, Cursor cursor) {
	if (cursor.row < view->line_count - 1) {
		cursor.row++
	}
	return cursor;
}

// Move the cursor left
// Vim mapping: h; General mapping: Lef5
Cursor move_left(const View *view, Cursor cursor) {
	if (cursor.col > 0) {
		cursor.col--;
	}
	return cursor;
}

// Move the cursor right
// Vim mapping: l; General mapping: Right
Cursor move_right(const View *view, Cursor cursor) {
	if (cursor.col < get_line(view, cursor.row)->length) {
		cursor.col++
	}
	return cursor;
}

// Move the cursor to the first non-white-space character of the row
// General mapping: Home
Cursor move_first_col(const View *view, Cursor cursor) {
	return set_col(cursor, 0);
}

// Move the cursor to the first non-white-space character of the row
// Vim mapping: 0, I
Cursor move_first_nonspace_col(const View *view, Cursor cursor) {
	return set_col(cursor, first_nonspace_col(view, cursor.row));
}

// Move the cursor to the first non-white-space character of the row
// Vim mapping: $; General mapping: End
Cursor move_last_col(const View *view, Cursor cursor) {
	return set_col(cursor, get_line(view, cursor.row)->length);
}

enum Vim_Mode {
	Vim_Normal_Mode,
	Vim_Insert_Mode,
};

struct Vim_View {
	View view;
	Vim_Mode mode;
};

void vim_character(Vim_View *vim_view, U32 key) {

	View *view = &vim_view->view;
	if (vim_view->mode == Vim_Normal_Mode) {
		switch (key) {
		case 'i':
			vim_view->mode = Vim_Insert_Mode;
			break;

		case 'h':
			view->cursor = move_left(view, view->cursor);
			break;
		case 'j':
			view->cursor = move_line_up(view, view->cursor);
			break;
		case 'k':
			view->cursor = move_line_down(view, view->cursor);
			break;
		case 'l':
			view->cursor = move_right(view, view->cursor);
			break;

		case '0':
			view->cursor = move_first_nonspace_col(view, view->cursor);
			break;
		case '$':
			view->cursor = move_last_col(view, view->cursor);
			break;

		}
	} else if (vim_view->mode == Vim_Insert_Mode) {
		if (key == VK_ESCAPE) {
			vim_view->mode = Vim_Normal_Mode;
		}
	}
}

