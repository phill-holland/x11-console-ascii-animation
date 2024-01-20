#include <iostream>
#include <vector>
#include <math.h>
#include <thread>
#include "console.h"
#include "effect.h"

int main(int argc, char *argv[])
{
	console::console c;
	effect e(console::console::columns,console::console::rows);

	while (true)
	{	
		e.draw(c);
		c.refresh();
		e.next();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	};

	return 0;
}