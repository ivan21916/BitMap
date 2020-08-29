#include "MandelBrot.h"
#include  <complex>

using namespace std;

namespace bitmapstruct {

MandelBrot::MandelBrot() {
	
}

MandelBrot::~MandelBrot() {

}

int MandelBrot::getIteration(double x, double y) { // 取得迭代次數

	complex<double> z = 0; // complex "=" operator overlading, z = 0 + i*0
	complex<double> c(x, y);
	
	int iterations = 0;

	while (iterations < MAX_ITERATIONS) {
		z = z * z + c;

		if (abs(z) > 2) { // abs為complex class內建函式, 為z到原點之距離,同等於(x^2+y^2)^(1/2)
			break;
		}

		iterations++;
	}
	
	return iterations;
}






}

