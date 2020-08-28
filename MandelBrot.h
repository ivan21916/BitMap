#ifndef MANDELBROT_H_
#define MANDELBROT_H_

namespace bitmapstruct {

class MandelBrot {
public:
	static const int MAX_ITERATIONS = 1000;
public:
	MandelBrot();
	virtual ~MandelBrot();
	static int getIteration(double x, double y);
};

}

#endif