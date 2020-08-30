#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_
#include "Zoom.h"
#include <vector>
#include <utility> // ¨Ï¥Îpair

using namespace std;

namespace bitmapstruct {

class ZoomList{
public:
	ZoomList(int width, int height);
	void add(const Zoom& zoom);
	pair<double, double> doZoom(int x, int y);

private:
	int m_width{ 0 };
	int m_height{ 0 };
	double m_xCenter{ 0 };
	double m_yCenter{ 0 };
	double m_scale{ 1.0 };
	vector<Zoom> zooms; 
};


}


#endif
