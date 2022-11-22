#include <iostream>
#include <vector>
#include <math.h>
//#include "kdtree.h"


float noise(int x)
{	
	//random number generator (with inbuilt seed) 
	int n = (x<<13) ^ x;
	//Log << "NNN" << n;
	//Log << "blur " << (float)( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    return (float)( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float hermiteInterpolate(float current,float next,float currentPosition)
{
		// test seperately !!
		// or use linear interpolation

		float time2 = currentPosition * currentPosition;
		float time3 = time2 * currentPosition;
		
		float a = 2.0f * time3 - 3.0f * time2 + 1.0f;
		//float b = time3 - (2.0f * time2) + currentPosition;
		//float c = time3 - time2;
		float d = -2.0f * time3 + 3.0f * time2;

		return a * current + d * next; // can be extended to 3D interpolation :-)
		//return = a * current + b * 0.0 + c * 0.0 + d * next;				
}

float perlin(float x)
{
	int octaves = 5;
	float result = 0.0f;

	float persistance = 1.0f;
	float amplitude,frequency;

	//Log << "X XXX " << x;
	float value;// = x;

	for(int n=0;n<octaves;n++)
	{
		frequency = 2.0f;
		amplitude = persistance;

		for(int i=0;i<n - 1;i++)
		{
			frequency *= 2.0f;
			amplitude *= persistance;
		}

		value = x * frequency;
		//Log << "value " << value << "frequency " << frequency << "amp " << amplitude;
		//Log << "val " << value;
		float a = noise((int)value);
		float b = noise((int)(value) + 1);

		//Log << "a " << a << "b " << b;

		result += hermiteInterpolate(a,b,value - (float)((int)value)) * amplitude;
	//	Log << result;
	}

	return result;
}

void out()
{
	const char values[] = { ' ', '1', '2', '3', '4' ,'5', '6' ,'7', '8', '9' };
	const int values_length = 10;

	const int width = 50;
	const int height = 50;
	const int length = width * height;

	const float pi = 3.1412f;// * 2.0f;

	char *buffer = new char[width * height];

	for(int i=0;i<length;++i) buffer[i] = ' ';

	float x_scale = pi / (float)(width / 4.0f); // WIDTH / 4 VARIABLE
	float y_scale = (pi*2.0f) / (float)(height / 2.0f);

	std::cout << x_scale << "\r\n";

// -1 to 1

	for(int y=0;y<height;++y)
	{
		float y_angle = (y_scale * ((float)y)) + noise(y + pi);//(pi);// + 1.0f;// / 2.0f); // + (pi) OFFSET VARIABLE
		float y_cos = cos(y_angle);// + noise(y); // -1 to 1

		for(int x=0;x<width;++x)
		{
			float x_angle = x_scale * ((float)x) + noise(x);// + 2.0f;
			float x_sin = sin(x_angle); // -1 to 1
			
			float m = ((y_cos + x_sin) + 2.0f);// * ((float)values_length);
			m /= 4.0f;
			m *= (float)values_length;

			int t = (int)floor(m);

			std::cout << x_sin << "," <<m << "," << t << " =" << values[t] << "\r\n";

			buffer[(y * width) + x] = values[t];
			//buffer[x,y] = values[t];
		}

		std::cout << "\r\n\r\n";
	}

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

	delete buffer;
}

int main(int argc, char *argv[])
{
	/*
    int points[][2] = { {97,23},{55,77},{34,76},{80,60},{99,04},{81,05},{05,81},{30,79},{15,80},{70,65},
                        {90,40},{40,30},{30,40},{20,60},{60,50},{20,20},{30,01},{60,40},{70,25},{44,62},
                        {55,55},{55,10},{15,45},{83,22},{76,46},{56,32},{45,55},{10,70},{10,30},{79,50}
                      };

    const int count = 30;
    bool is_front[count];

	kdtree::kdpoint origin(2);
	origin.set(0L);

	kdtree::kdtree *approximation = new kdtree::kdtree(2,count);
	if(approximation == NULL) return 0;

	for(int i = 0; i < count; ++i)
	{	
        is_front[i] = true;

		kdtree::kdpoint point1(2);
		point1.set(points[i][0],0);
		point1.set(points[i][1],1);

		approximation->insert(&point1);
	}

	for(int i = 0; i < count; ++i)
	{
		kdtree::kdpoint point1(2);
		point1.set(points[i][0],0);
		point1.set(points[i][1],1);

		for(int j = 0; j < count; ++j)
		{
			if(i != j)
			{
				kdtree::kdpoint point2(2);
				point2.set(points[j][0],0);
				point2.set(points[j][1],1);

				if(approximation->inside(point1, &origin, &point2))
				{
					is_front[i] = false;
					break;
				}
				
			}
		}
	}
    
    std::cout << "Pareto Front;\n";

	for(int i = 0; i < count; ++i)
	{
		if(is_front[i]) 
		{
            std::cout << points[i][0] << "," << points[i][1] << "\r\n";
		}
	}

    delete approximation;
	*/
    return 0;
}