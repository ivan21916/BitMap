#include <iostream>
//#include "bitmap.h"
//#include <cstdint>
//#include "MandelBrot.h"
//#include <memory>
//#include <math.h> // 為了使用power funciton	
//#include "ZoomList.h"
#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"

using namespace std;
using namespace bitmapstruct;

int main() {
	//int const m_width = 800;
	//int const m_height = 600;

	//BitMap m_bitmap(w_width, w_height);

	//int height = 600;

	FractalCreator fractalCreator(800, 600);
	
	fractalCreator.addRange(0.0, RGB(0, 0, 0));
	fractalCreator.addRange(0.3, RGB(255, 0, 0)); // range: 0~300 pixels
	fractalCreator.addRange(0.5, RGB(255, 255, 0)); // range: 300~500 pixels
	fractalCreator.addRange(1.0, RGB(255, 255, 255)); // range: 500~1000 pixels

	fractalCreator.addZoom(Zoom(399, 162, 0.1));
	fractalCreator.run("test.bmp");

	//fractalCreator.addZoom(Zoom(399, height-162, 0.1))
	//double min = 999999;
	//double max = -999999;

	//ZoomList m_zoomList(w_width, w_height);

	//m_zoomList.add(Zoom(w_width / 2, w_height / 2, 4.0/w_width)); // 從中心點開始
	//zoomlist.add(Zoom(399, HEIGHT - 162, 0.1));
	//unique_ptr<int[]> m_histogram(new int[MandelBrot::MAX_ITERATIONS]{0}); // 此陣列指標儲存了共有幾個iterations數相同的PIXEL(比如iterations 10次的有幾個, 50次的有幾個)
	//unique_ptr<int[]>	m_fractal(new int[w_width*w_height]{0}); // 此陣列指標儲存了每個像素對應多少iterataions
	//for (int y = 0; y < w_height; y++) {
	//	for (int x = 0; x < w_width; x++) {
	//		//double xFractal = (x - WIDTH / 2)*(2.0 / WIDTH); // 要讓xFractal從-1~1, 首先 x - WIDTH/2會讓x從(0-800/2)=-400到(799-800/2)=400(接近), 再除以800/2
	//		//double xFractal = (x - WIDTH / 2 - 200) * (2.0 / HEIGHT); // 將xFractal除以HEIGHT可以讓圖形比例更好(不會拉伸或壓縮), -200為往左位移200 (不會被切到)
	//		//double yFractal = (y - HEIGHT / 2)*(2.0 / HEIGHT);

	//		pair<double, double> coords = m_zoomList.doZoom(x, y);

	//		//int iterations = MandelBrot::getIteration(xFractal, yFractal);
	//		int iterations = MandelBrot::getIteration(coords.first, coords.second);

	//		m_fractal[y * w_width + x] = iterations;

	//		if (iterations != MandelBrot::MAX_ITERATIONS) {
	//			m_histogram[iterations]++; // 將有相同iteration數的pixel個數+1
	//		}
	//		
	//	}
	//}
	//cout << endl;

	//int count = 0;
	//for (int i = 0; i < MandelBrot::MAX_ITERATIONS; i++) {
	//	cout << histogram[i] << " " << flush;
	//	count += histogram[i];
	//}
	//cout << count << "; " << WIDTH * HEIGHT << endl; //count表示總共有多少個iterations結果(小於MAX_ITERATIONS), WIDTH*HEIGHT代表總共有多少個pixel

	
	//int total = 0;
	//for (int i = 0; i < MandelBrot::MAX_ITERATIONS; i++){
	//	total += m_histogram[i];
	//}

	//for (int y = 0; y < w_height; y++) {
	//	for (int x = 0; x < w_width; x++) {

	//		uint8_t red = 0; // 三個顏色預設為0為黑色
	//		uint8_t green = 0;
	//		uint8_t blue = 0;

	//		int iterations = m_fractal[y * w_width + x];

	//		//uint8_t color = (uint8_t)(256 * (double)iterations / MandelBrot::MAX_ITERATIONS); // 必須將型態轉換成double

	//		if (iterations != MandelBrot::MAX_ITERATIONS) {

	//			double hue = 0.0;

	//			for (int i = 0; i <= iterations; i++) {
	//				hue += ((double)m_histogram[i]) / total; // 把由小到大的iterations個數除以所有iterations再相加(hue的範圍會從0~1)
	//			}

	//			//green = pow(255, hue); // 255的hue次方 (hue從0~1), 這可以讓有更高iteration的pixel看起來更亮
	//			green = hue*255;
	//		}

			//color = color * color * color; // 使color增加more rapidly, 使圖片鮮明度, color不會影響記憶體, 因為color已經宣告為uint8_t, 只會在0-255之間
			//if (xFractal < min) {
			//	min = xFractal; // 只會執行一次(0-800/2)*(2/800) = -1
			//}
			//if (xFractal > max) {
			//	max = xFractal; // 會執行x++到799, (799-800/2)*(2/800) = 0.9975
			//}
			//bitmap.setPixel(x, y, 0, color, 0);
			//m_bitmap.setPixel(x, y, red, green, blue);
			//if (color < min) { // 
			//	min = color;
			//}
			//if (color > max) {
			//	max = color;
			//}
	//	}
	//}
	//m_bitmap.write("test.bmp");
	//fractalCreator.calculateIteration();
	//fractalCreator.calculateTotalIteration();
	//fractalCreator.drawFractal();
	//fractalCreator.writeBitmap("test.bmp");
	//cout << min << ", " << max << endl;


	cout << "Finished" << endl;
	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
