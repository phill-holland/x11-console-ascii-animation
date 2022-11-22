//#include "core/queue/interface/features.h"
//#include "core/string/string.h"
//#include "core/threading/thread.h"
//#include "core/threading/semaphore.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#ifndef _CONSOLE
#define _CONSOLE

namespace console
{
	//using namespace std;

	class console //: public core::queue::interface::features::fifo::destination<string>
	{
		bool init;

		Display *display;
		Visual *visual;
		int depth;
		Window window;
		XFontStruct *fontinfo;
		XGCValues gr_values;
		GC graphical_context;

		const static int columns = 80, rows = 25;
		char buffer[columns * rows];

		//core::threading::semaphore::token token;

	public:
		console(int x = 0, int y = 0) { makeNull(); reset(x, y); }
		~console() { cleanup(); }

		void reset(int x, int y);
		bool initalised() { return init; }

		void clear();
		bool move(int x, int y);

		bool title(std::string source);
		void write(std::string source, bool timestamp = true);

		bool set(std::string &source) { write(source); return true; }
		bool isfull() { return false; }

		//std::string identifier() { return string("console"); }

	protected:
		bool title(const char *source);
		void write(const char *source, int length);

	protected:
		bool refresh();
		void fix(int w, int h);

	public:
		console operator<<(std::string &source) { write(source); return *this; }

	protected:
		void makeNull();
		void cleanup();
	};
};

#endif