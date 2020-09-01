#include "FractalCreator.h"
#include "iostream"
#include <assert.h>

using namespace std;

namespace bitmapstruct {

void FractalCreator::run(string name) {

	calculateIteration();
	calculateTotalIteration();
	calculateRangeTotals();
	drawFractal();
	writeBitmap("test.bmp");
}

FractalCreator::FractalCreator(int width, int height): m_width(width), m_height(height), m_histogram(new int[MandelBrot::MAX_ITERATIONS]{ 0 }),
m_fractal(new int[m_width * m_height]{ 0 }), m_bitmap(m_width, m_height), m_zoomList(m_width, m_height) {
	m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

void FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
	m_ranges.push_back(rangeEnd*MandelBrot::MAX_ITERATIONS);
	m_colors.push_back(rgb);

	if (m_bGotFirstRange) { // 為了不讓第一個(addRange(0.0, RGB(0, 0, 0)))有rangeTotal
		m_rangeTotals.push_back(0);
	}
	m_bGotFirstRange = true;

}

int FractalCreator::getRange(int iterations) const {
	int range = 0;

	for (int i = 1; i < m_ranges.size(); i++) { // 因為起始點fractalCreator.addRange(0.0, RGB(0, 0, 0))不比較, 所以從1開始
		range = i;
		if (m_ranges[i] > iterations) {
			break;
		}
	}

	range--; // 要獲得zero based index, 要將rage-1

	assert(range > -1); // 此處須include assert.h來雙重檢查, 避免程式當掉
	assert(range < m_ranges.size());

	return range;
}

void FractalCreator::addZoom(const Zoom& zoom) {
	m_zoomList.add(zoom);
}
void FractalCreator::calculateIteration() { // first nested loop
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			//double xFractal = (x - WIDTH / 2)*(2.0 / WIDTH); // 要讓xFractal從-1~1, 首先 x - WIDTH/2會讓x從(0-800/2)=-400到(799-800/2)=400(接近), 再除以800/2
			//double xFractal = (x - m_width / 2 - 200) * (2.0 / m_height); // 將xFractal除以HEIGHT可以讓圖形比例更好(不會拉伸或壓縮), -200為往左位移200 (不會被切到)
			//double yFractal = (y - m_height / 2)*(2.0 / m_height);

			pair<double, double> coords = m_zoomList.doZoom(x, y);

			//int iterations = MandelBrot::getIteration(xFractal, yFractal);
			int iterations = MandelBrot::getIteration(coords.first, coords.second);

			m_fractal[y * m_width + x] = iterations;

			if (iterations != MandelBrot::MAX_ITERATIONS) {
				m_histogram[iterations]++; // 將有相同iteration數的pixel個數+1
			}

		}
	}
}

void FractalCreator::calculateRangeTotals() {

	int rangeIndex = 0;
	
	for (int i = 0; i < MandelBrot::MAX_ITERATIONS; i++) {
		int pixels = m_histogram[i];

		if (i >= m_ranges[rangeIndex + 1]) {
			rangeIndex++;
		}

		m_rangeTotals[rangeIndex] += pixels;
	}

	for (int value : m_rangeTotals) {
		cout << "Range total: " << value << endl;
	}
}

void FractalCreator::calculateTotalIteration() {
	for (int i = 0; i < MandelBrot::MAX_ITERATIONS; i++) {
		m_total += m_histogram[i];
	}
}

void FractalCreator::drawFractal() { // second nested loop

	//RGB startColor(0, 0, 0);
	//RGB endColor(255, 136, 28);
	//RGB colorDiff = endColor - startColor;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {

			int iterations = m_fractal[y * m_width + x];

			int range = getRange(iterations); // 首先先找出iterations落在的區間範圍
			int rangeTotal = m_rangeTotals[range];
			int rangeStart = m_ranges[range];

			RGB& startColor = m_colors[range];
			RGB& endColor = m_colors[range+1];
			RGB colorDiff = endColor - startColor;

			uint8_t red = 0; // 三個顏色預設為0為黑色
			uint8_t green = 0;
			uint8_t blue = 0;

			//uint8_t color = (uint8_t)(256 * (double)iterations / MandelBrot::MAX_ITERATIONS); // 必須將型態轉換成double

			if (iterations != MandelBrot::MAX_ITERATIONS) {

				//double hue = 0.0;

				//for (int i = 0; i <= iterations; i++) {
				//	hue += ((double)m_histogram[i]) / m_total; // 把由小到大的iterations個數除以所有iterations再相加(hue的範圍會從0~1)
				//}

				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; i++) {
					totalPixels += m_histogram[i];
				}

				//red = startColor.r + colorDiff.r * hue;
				//green = startColor.g + colorDiff.g * hue;
				//blue = startColor.b + colorDiff.b * hue;

				red = startColor.r + colorDiff.r * (double)totalPixels/rangeTotal; // totalPixels/rangeTotal為0~1的值
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;

				//green = pow(255, hue); // 255的hue次方 (hue從0~1), 這可以讓有更高iteration的pixel看起來更亮
				//green = hue * 255;
			}

			//color = color * color * color; // 使color增加more rapidly, 使圖片鮮明度, color不會影響記憶體, 因為color已經宣告為uint8_t, 只會在0-255之間
			//if (xFractal < min) {
			//	min = xFractal; // 只會執行一次(0-800/2)*(2/800) = -1
			//}
			//if (xFractal > max) {
			//	max = xFractal; // 會執行x++到799, (799-800/2)*(2/800) = 0.9975
			//}
			//bitmap.setPixel(x, y, 0, color, 0);
			m_bitmap.setPixel(x, y, red, green, blue);
			//if (color < min) { // 
			//	min = color;
			//}
			//if (color > max) {
			//	max = color;
			//} 
		}
	}
} 


void FractalCreator::writeBitmap(string name) {
	m_bitmap.write(name);
}
}