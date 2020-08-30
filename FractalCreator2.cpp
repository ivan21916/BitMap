#include "FractalCreator.h"


namespace bitmapstruct {

FractalCreator::FractalCreator(int width, int height): m_width(width), m_height(height), m_histogram(new int[MandelBrot::MAX_ITERATIONS]{ 0 }),
m_fractal(new int[m_width * m_height]{ 0 }), m_bitmap(m_width, m_height), m_zoomList(m_width, m_height) {
	m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

void FractalCreator::calculateIteration() { // first nested loop
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			//double xFractal = (x - WIDTH / 2)*(2.0 / WIDTH); // �n��xFractal�q-1~1, ���� x - WIDTH/2�|��x�q(0-800/2)=-400��(799-800/2)=400(����), �A���H800/2
			double xFractal = (x - m_width / 2 - 200) * (2.0 / m_height); // �NxFractal���HHEIGHT�i�H���ϧΤ�ҧ�n(���|�Ԧ������Y), -200�������첾200 (���|�Q����)
			double yFractal = (y - m_height / 2)*(2.0 / m_height);

			//pair<double, double> coords = m_zoomList.doZoom(x, y);

			int iterations = MandelBrot::getIteration(xFractal, yFractal);
			//int iterations = MandelBrot::getIteration(coords.first, coords.second);

			m_fractal[y * m_width + x] = iterations;

			if (iterations != MandelBrot::MAX_ITERATIONS) {
				m_histogram[iterations]++; // �N���ۦPiteration�ƪ�pixel�Ӽ�+1
			}

		}
	}
}

void FractalCreator::calculateTotalIteration() {
	for (int i = 0; i < MandelBrot::MAX_ITERATIONS; i++) {
		m_total += m_histogram[i];
	}
}

void FractalCreator::drawFractal() { // second nested loop
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {

			uint8_t red = 0; // �T���C��w�]��0���¦�
			uint8_t green = 0;
			uint8_t blue = 0;

			int iterations = m_fractal[y * m_width + x];

			//uint8_t color = (uint8_t)(256 * (double)iterations / MandelBrot::MAX_ITERATIONS); // �����N���A�ഫ��double

			if (iterations != MandelBrot::MAX_ITERATIONS) {

				double hue = 0.0;

				for (int i = 0; i <= iterations; i++) {
					hue += ((double)m_histogram[i]) / m_total; // ��Ѥp��j��iterations�Ӽư��H�Ҧ�iterations�A�ۥ[(hue���d��|�q0~1)
				}

				green = pow(255, hue); // 255��hue���� (hue�q0~1), �o�i�H������iteration��pixel�ݰ_�ӧ�G
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
void FractalCreator::addZoom(const Zoom& zoom) {
	m_zoomList.add(zoom);
}
void FractalCreator::writeBitmap(string name) {
	m_bitmap.write(name);
}
}