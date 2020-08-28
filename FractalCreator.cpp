#include <iostream>
//#include "bitmapfileheader.h" 
//#include "bitmapinfoheader.h"
#include "bitmap.h"
#include <cstdint>
#include "MandelBrot.h"

using namespace std;
using namespace bitmapstruct;

int main() {
	int const WIDTH = 800;
	int const HEIGHT = 600;

	BitMap bitmap(WIDTH, HEIGHT);

	double min = 999999;
	double max = -999999;



	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			double xFractal = (x - WIDTH / 2)*(2.0 / WIDTH); // 要讓xFractal從-1~1, 首先 x - WIDTH/2會讓x從(0-800/2)=-400到(799-800/2)=400(接近), 再除以800/2
			double yFractal = (y - HEIGHT / 2)*(2.0 / HEIGHT);

			int iterations = MandelBrot::getIteration(xFractal, yFractal);

			uint8_t red = (uint8_t)(256*(double)iterations / MandelBrot::MAX_ITERATIONS); // 必須將型態轉換成double

			//if (xFractal < min) {
			//	min = xFractal; // 只會執行一次(0-800/2)*(2/800) = -1
			//}
			//if (xFractal > max) {
			//	max = xFractal; // 會執行x++到799, (799-800/2)*(2/800) = 0.9975
			//}
			bitmap.setPixel(x, y, red, red, red);
			if (red < min) {
				min = red; 
			}
			if (red > max) {
				max = red; 
			}
		}
	}

	cout << min << ", " << max << endl;
	bitmap.write("test.bmp");



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
