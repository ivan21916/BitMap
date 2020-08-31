#include "ZoomList.h"
#include <iostream>

using namespace std;

namespace bitmapstruct {

ZoomList::ZoomList(int width, int height): m_width(width), m_height(height) {

}

void ZoomList::add(const Zoom& zoom) {
	zooms.push_back(zoom);

	m_xCenter += (zoom.x - m_width / 2) * m_scale;
	m_yCenter += -(zoom.y - m_height / 2) * m_scale; // 因為檢視圖片座標之功能的y軸上下顛倒, 所以在此必須加上負號
	m_scale *= zoom.scale;

	cout << m_xCenter << ", " << m_yCenter << ", " << m_scale << endl;
}

pair<double, double>  ZoomList::doZoom(int x, int y) {

	double xFractal = (x - m_width / 2) * m_scale + m_xCenter; // 首先將原本中心點移動到原點, 再加上m_xCenter移動到欲放大的位置
	double yFractal = (y - m_height / 2) * m_scale + m_yCenter;
	return pair<double, double>(xFractal, yFractal);
}
}