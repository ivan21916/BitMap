#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <iostream>
#include <string>
#include "Zoom.h"
#include "bitmap.h"
#include "MandelBrot.h"
#include "ZoomList.h"
#include <cstdint>
#include <memory>
using namespace std;

namespace bitmapstruct {

class FractalCreator{
public:
	FractalCreator(int width, int height);

	void calculateIteration(); // first nested loop
	void calculateTotalIteration();
	void drawFractal(); // second nested loop
	void addZoom(const Zoom& zoom);
	void writeBitmap(string name);

private:
	int m_width;
	int m_height;
	unique_ptr<int[]> m_histogram; // 此陣列指標儲存了共有幾個iterations數相同的PIXEL(比如iterations 10次的有幾個, 50次的有幾個)
	unique_ptr<int[]> m_fractal; // 此陣列指標儲存了每個像素對應多少iterataions
	BitMap m_bitmap;
	ZoomList m_zoomList;
	int m_total{ 0 };
};

}

#endif
