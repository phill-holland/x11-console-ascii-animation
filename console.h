#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#ifndef _CONSOLE
#define _CONSOLE

namespace console
{
	class console
	{
	public:
		const static int columns = 80, rows = 25;

	private:
		bool init;

		Display *display;
		Visual *visual;
		int depth;
		Window window;
		XFontStruct *fontinfo;
		XGCValues gr_values;
		GC graphical_context;

		char buffer[columns * rows];

	public:
		console(int x = 0, int y = 0) { makeNull(); reset(x, y); }
		~console() { cleanup(); }

		void reset(int x, int y);
		bool initalised() { return init; }

		void clear();

		bool title(std::string source);
		void write(std::string source, bool timestamp = true);

		void set(const char *source, int length, int row);
		
		bool refresh();	

	protected:
		bool title(const char *source);
		void write(const char *source, int length);

	protected:	
		
		void fix(int w, int h);

	public:
		console operator<<(std::string &source) { write(source); return *this; }

	protected:
		static std::string fromTime(time_t source);

	protected:
		void makeNull();
		void cleanup();
	};
};

#endif