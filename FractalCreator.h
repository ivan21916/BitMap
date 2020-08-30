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
	unique_ptr<int[]> m_histogram; // ���}�C�����x�s�F�@���X��iterations�ƬۦP��PIXEL(��piterations 10�������X��, 50�������X��)
	unique_ptr<int[]> m_fractal; // ���}�C�����x�s�F�C�ӹ��������h��iterataions
	BitMap m_bitmap;
	ZoomList m_zoomList;
	int m_total{ 0 };
};

}

#endif
