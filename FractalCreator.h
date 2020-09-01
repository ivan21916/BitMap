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
	unique_ptr<int[]> m_histogram; // ���}�C�����x�s�F�@���X��iterations�ƬۦP��Pixel(��piterations 10�������X��, 50�������X��)
	unique_ptr<int[]> m_fractal; // ���}�C�����x�s�F�C�ӹ��������h��iterataions
	BitMap m_bitmap;
	ZoomList m_zoomList;
	int m_total{ 0 };

	vector<int> m_ranges; // �x�s�϶���iterations����
	vector<RGB> m_colors;
	vector<int> m_rangeTotals; // �x�s�϶���pixels�`��
	bool m_bGotFirstRange{ false };
};

}

#endif
