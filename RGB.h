#ifndef RGB_H_
#define RGB_H_

namespace bitmapstruct {

struct RGB{

	RGB(double r, double g, double b);
	double r;
	double g;
	double b;

};

RGB operator-(const RGB& first, const RGB& second);

}

#endif