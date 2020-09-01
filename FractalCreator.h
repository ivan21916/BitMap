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
#include "RGB.h"
#include <vector>

using namespace std;

namespace bitmapstruct {

class FractalCreator{
public:
	void run(string name);
	FractalCreator(int width, int height);
	void addZoom(const Zoom& zoom);
	void addRange(double rangeEnd, const RGB& rgb);
private:

	void calculateIteration(); // first nested loop
	void calculateTotalIteration();
	void calculateRangeTotals();
	void drawFractal(); // second nested loop
	void writeBitmap(string name);
	int getRange(int iterations) const;

private:
	int m_width;
	int m_height;
	unique_ptr<int[]> m_histogram; // 此陣列指標儲存了共有幾個iterations數相同的Pixel(比如iterations 10次的有幾個, 50次的有幾個)
	unique_ptr<int[]> m_fractal; // 此陣列指標儲存了每個像素對應多少iterataions
	BitMap m_bitmap;
	ZoomList m_zoomList;
	int m_total{ 0 };

	vector<int> m_ranges; // 儲存區間的iterations次數
	vector<RGB> m_colors;
	vector<int> m_rangeTotals; // 儲存區間的pixels總數
	bool m_bGotFirstRange{ false };
};

}

#endif
