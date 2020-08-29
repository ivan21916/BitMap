#include "MandelBrot.h"
#include  <complex>

using namespace std;

namespace bitmapstruct {

MandelBrot::MandelBrot() {
	
}

MandelBrot::~MandelBrot() {

}

int MandelBrot::getIteration(double x, double y) { // ���o���N����

	complex<double> z = 0; // complex "=" operator overlading, z = 0 + i*0
	complex<double> c(x, y);
	
	int iterations = 0;

	while (iterations < MAX_ITERATIONS) {
		z = z * z + c;

		if (abs(z) > 2) { // abs��complex class���ب禡, ��z����I���Z��,�P����(x^2+y^2)^(1/2)
			break;
		}

		iterations++;
	}
	
	return iterations;
}






}

