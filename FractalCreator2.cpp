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

	if (m_bGotFirstRange) { // ���F�����Ĥ@��(addRange(0.0, RGB(0, 0, 0)))��rangeTotal
		m_rangeTotals.push_back(0);
	}
	m_bGotFirstRange = true;

}

int FractalCreator::getRange(int iterations) const {
	int range = 0;

	for (int i = 1; i < m_ranges.size(); i++) { // �]���_�l�IfractalCreator.addRange(0.0, RGB(0, 0, 0))�����, �ҥH�q1�}�l
		range = i;
		if (m_ranges[i] > iterations) {
			break;
		}
	}

	range--; // �n��ozero based index, �n�Nrage-1

	assert(range > -1); // ���B��include assert.h�������ˬd, �קK�{����
	assert(range < m_ranges.size());

	return range;
}

void FractalCreator::addZoom(const Zoom& zoom) {
	m_zoomList.add(zoom);
}
void FractalCreator::calculateIteration() { // first nested loop
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			//double xFractal = (x - WIDTH / 2)*(2.0 / WIDTH); // �n��xFractal�q-1~1, ���� x - WIDTH/2�|��x�q(0-800/2)=-400��(799-800/2)=400(����), �A���H800/2
			//double xFractal = (x - m_width / 2 - 200) * (2.0 / m_height); // �NxFractal���HHEIGHT�i�H���ϧΤ�ҧ�n(���|�Ԧ������Y), -200�������첾200 (���|�Q����)
			//double yFractal = (y - m_height / 2)*(2.0 / m_height);

			pair<double, double> coords = m_zoomList.doZoom(x, y);

			//int iterations = MandelBrot::getIteration(xFractal, yFractal);
			int iterations = MandelBrot::getIteration(coords.first, coords.second);

			m_fractal[y * m_width + x] = iterations;

			if (iterations != MandelBrot::MAX_ITERATIONS) {
				m_histogram[iterations]++; // �N���ۦPiteration�ƪ�pixel�Ӽ�+1
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

			int range = getRange(iterations); // ��������Xiterations���b���϶��d��
			int rangeTotal = m_rangeTotals[range];
			int rangeStart = m_ranges[range];

			RGB& startColor = m_colors[range];
			RGB& endColor = m_colors[range+1];
			RGB colorDiff = endColor - startColor;

			uint8_t red = 0; // �T���C��w�]��0���¦�
			uint8_t green = 0;
			uint8_t blue = 0;

			//uint8_t color = (uint8_t)(256 * (double)iterations / MandelBrot::MAX_ITERATIONS); // �����N���A�ഫ��double

			if (iterations != MandelBrot::MAX_ITERATIONS) {

				//double hue = 0.0;

				//for (int i = 0; i <= iterations; i++) {
				//	hue += ((double)m_histogram[i]) / m_total; // ��Ѥp��j��iterations�Ӽư��H�Ҧ�iterations�A�ۥ[(hue���d��|�q0~1)
				//}

				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; i++) {
					totalPixels += m_histogram[i];
				}

				//red = startColor.r + colorDiff.r * hue;
				//green = startColor.g + colorDiff.g * hue;
				//blue = startColor.b + colorDiff.b * hue;

				red = startColor.r + colorDiff.r * (double)totalPixels/rangeTotal; // totalPixels/rangeTotal��0~1����
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;

				//green = pow(255, hue); // 255��hue���� (hue�q0~1), �o�i�H������iteration��pixel�ݰ_�ӧ�G
				//green = hue * 255;
			}

			//color = color * color * color; // ��color�W�[more rapidly, �ϹϤ��A����, color���|�v�T�O����, �]��color�w�g�ŧi��uint8_t, �u�|�b0-255����
			//if (xFractal < min) {
			//	min = xFractal; // �u�|����@��(0-800/2)*(2/800) = -1
			//}
			//if (xFractal > max) {
			//	max = xFractal; // �|����x++��799, (799-800/2)*(2/800) = 0.9975
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