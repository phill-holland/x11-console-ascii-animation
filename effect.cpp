#include "effect.h"
#include <math.h>

void effect::reset(int width, int height)
{
    init = false; cleanup();

    x_offset = 0.0f;
    y_offset = 0.0f;

    this->width = width;
    this->height = height;

    buffer = new char[width];
    if(buffer==NULL) return;

    init = true;
}

void effect::draw(console::console &destination)
{
    const char values[] = { ' ', '1', '2', '3', '4' ,'5', '6' ,'7', '8', '9' };
	const int values_length = 10;

	//const int width = 80;
	//const int height = 25;
	const int length = width * height;

	const float pi = 3.1412f;// * 2.0f;

	//char *buffer = new char[width * height];

	//for(int i=0;i<length;++i) buffer[i] = ' ';

	float x_scale = pi / (float)(width);// / 4.0f); // WIDTH / 4 VARIABLE
	float y_scale = (pi*2.0f) / (float)(height);// / 2.0f);

// -1 to 1

	for(int y=0;y<height;++y)
	{
		float y_angle = (y_scale * ((float)y));//+ noise(y + pi);//(pi);// + 1.0f;// / 2.0f); // + (pi) OFFSET VARIABLE
		float y_cos = cos(y_angle + y_offset);// + sin(y_angle + (y_offset / 25));// + noise(y); // -1 to 1

		for(int x=0;x<width;++x)
		{
			float x_angle = x_scale * ((float)x);// + noise(x);// + 2.0f;
			float x_sin = sin(x_angle + x_offset);// + cos(x_angle + (x_offset / 10)); // -1 to 1
			
			float m = ((y_cos + x_sin) + 2.0f);// * ((float)values_length);
			m /= 4.0f;
			m *= (float)values_length;

			int t = (int)floor(m);

			//std::cout << x_sin << "," <<m << "," << t << " =" << values[t] << "\r\n";

			//buffer[(y * width) + x] = values[t];
            buffer[x] = values[t];
			//buffer[x,y] = values[t];
		}

        destination.set(buffer, width, y);

		//std::cout << "\r\n\r\n";
	}

/*
	for(int y=0;y<height;++y)
	{
		//string line;

		for(int x=0;x<width;++x)
		{
			std::cout << buffer[(y * width) + x];
			//char a = buffer[x,y];
			//line.concat(&a,1);
		}

std::cout << "\r\n";
		//line.concat(string("\r\n"));
		//std::cout << line;
	}
*/
	
}

void effect::next()
{
    x_offset += 0.001f;
    y_offset += 0.02f;
}

void effect::makeNull()
{
    buffer = NULL;
}

void effect::cleanup()
{
    if(buffer != NULL) delete[] buffer;
}