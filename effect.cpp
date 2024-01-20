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

	const int length = width * height;

	const float pi = 3.1412f;

	float x_scale = pi / (float)(width);
	float y_scale = (pi*2.0f) / (float)(height);

	for(int y=0;y<height;++y)
	{
		float y_angle = (y_scale * ((float)y));
		float y_cos = cos(y_angle + y_offset);

		for(int x=0;x<width;++x)
		{
			float x_angle = x_scale * ((float)x);
			float x_sin = sin(x_angle + x_offset);
			
			float m = ((y_cos + x_sin) + 2.0f);
			m /= 4.0f;
			m *= (float)values_length;

			int t = (int)floor(m);

            buffer[x] = values[t];
		}

        destination.set(buffer, width, y);
	}	
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