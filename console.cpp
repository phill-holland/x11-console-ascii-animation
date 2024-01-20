#include "console.h"
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>

void console::console::reset(int x, int y)
{
	init = false; cleanup();

	XInitThreads();

	display = XOpenDisplay(NULL);
	visual = DefaultVisual(display, 0);
	depth = DefaultDepth(display, 0);

	int width = 6 * columns;
	int height = 13 * rows;

	XSetWindowAttributes frame_attributes;
	frame_attributes.background_pixel = XBlackPixel(display, 0);
	window = XCreateWindow(display, XRootWindow(display, 0),
								x, y, width, height, 5, depth,
								InputOutput, visual, CWBackPixel, &frame_attributes);

	XSelectInput(display, window, ExposureMask | StructureNotifyMask);

	fix(width, height);

	fontinfo = XLoadQueryFont(display, "6x13");
	if (fontinfo == NULL) return;

	gr_values.font = fontinfo->fid;
	gr_values.foreground = XWhitePixel(display, 0);
	graphical_context = XCreateGC(display, window, GCFont + GCForeground, &gr_values);
	XMapWindow(display, window);

	if (!title("Console")) return;

	clear();

	init = true;
}

void console::console::clear()
{
	std::memset(buffer, 0, columns * rows);
}

bool console::console::title(std::string source)
{
	return title(source.c_str());
}

void console::console::write(std::string source, bool timestamp)
{
	if (timestamp)
	{
		time_t now = time(NULL);
		std::string temp;
		temp.append(fromTime(now));
		temp.append(std::string("> "));
		temp.append(source);

		write(temp.c_str(), temp.size());
	}
	else write(source.c_str(), source.size());
}

void console::console::set(const char *source, int length, int row)
{
	int l = length;
	if (l > columns) l = columns;

	int r = row;
	if(r > rows) r = rows;

	int index = (r * columns);
	memcpy(&buffer[index], source, l);
}

bool console::console::title(const char *source)
{
	XStoreName(display, window, source);

	return true;
}

void console::console::write(const char *source, int length)
{
	int previous = (rows - 2)  * columns;
	int current = (rows - 1) * columns;

	for (int i = 0; i < rows - 1; ++i)
	{
		memcpy(&buffer[current], &buffer[previous], columns);
		current = previous;
		previous -= columns;
	}

	memset(&buffer[0], 0, columns);

	if (length > columns) length = columns;

	for (int i = 0; i < length; ++i)
	{
		buffer[i] = source[i];
	}

	refresh();
}

bool console::console::refresh()
{
	XWindowAttributes window_attributes;
	int font_direction, font_ascent, font_descent;
	XCharStruct text_structure;

	XClearWindow(display, window);

	int offset = 0, x = 2, y = 12;
	for (int row = 0; row < rows; ++row)
	{
		char temp[columns];
		memset(temp, 0, columns);
		memcpy(temp, &buffer[offset], columns);

		XTextExtents(fontinfo, temp, strlen(temp), &font_direction, &font_ascent, &font_descent, &text_structure);
		XGetWindowAttributes(display, window, &window_attributes);
		XDrawString(display, window, graphical_context, x, y, temp, strlen(temp));

		y += 12;//text_structure.ascent + text_structure.descent + 2;
		offset += columns;
	}

	return true;
}

void console::console::fix(int w, int h)
{
	XSizeHints *sh = XAllocSizeHints();
	sh->flags = PMinSize | PMaxSize;
	sh->min_width = sh->max_width = 100;
	sh->min_height = sh->max_height = 100;
	XSetWMSizeHints(display, window, sh, XA_WM_SIZE_HINTS);
	XFree(sh);
}

std::string console::console::fromTime(time_t source)
{
	std::string result;
	tm now;

	localtime_r(&source, &now);
		
	if (now.tm_mday<10) result.append(std::string("0"));
	result.append(std::to_string(now.tm_mday));
	result.append(std::string("/"));
	if ((now.tm_mon + 1) < 10) result.append(std::string("0"));
	result.append(std::to_string(now.tm_mon + 1));
	result.append(std::string("/"));
	result.append(std::to_string(now.tm_year + 1900));
	result.append(std::string(" "));
	if (now.tm_hour<10) result.append(std::string("0"));
	result.append(std::to_string(now.tm_hour));
	result.append(std::string(":"));
	if (now.tm_min<10) result.append(std::string("0"));
	result.append(std::to_string(now.tm_min));
	result.append(std::string(":"));
	if (now.tm_sec<10) result.append(std::string("0"));
	result.append(std::to_string(now.tm_sec));

	return result;
}

void console::console::makeNull()
{
	display = NULL;
	visual = NULL;
}

void console::console::cleanup()
{
	if (display != NULL)
	{
		XDestroyWindow(display, window);
		XCloseDisplay(display);
	}
}