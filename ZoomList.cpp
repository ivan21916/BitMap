#include "ZoomList.h"
#include <iostream>

using namespace std;

namespace bitmapstruct {

ZoomList::ZoomList(int width, int height): m_width(width), m_height(height) {

}

void ZoomList::add(const Zoom& zoom) {
	zooms.push_back(zoom);

	m_xCenter += (zoom.x - m_width / 2) * m_scale;
	m_yCenter += -(zoom.y - m_height / 2) * m_scale; // �]���˵��Ϥ��y�Ф��\�઺y�b�W�U�A��, �ҥH�b�������[�W�t��
	m_scale *= zoom.scale;

	cout << m_xCenter << ", " << m_yCenter << ", " << m_scale << endl;
}

pair<double, double>  ZoomList::doZoom(int x, int y) {

	double xFractal = (x - m_width / 2) * m_scale + m_xCenter; // �����N�쥻�����I���ʨ���I, �A�[�Wm_xCenter���ʨ����j����m
	double yFractal = (y - m_height / 2) * m_scale + m_yCenter;
	return pair<double, double>(xFractal, yFractal);
}
}