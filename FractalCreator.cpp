#include <iostream>
//#include "bitmapfileheader.h" 
//#include "bitmapinfoheader.h"
//#include "FractalCreator/bitmap.h"
#include "bitmap.h"
using namespace std;
using namespace bitmapstruct;

int main() {
	int const WIDTH = 800;
	int const HEIGHT = 600;

	BitMap bitmap(WIDTH, HEIGHT);

	bitmap.setPixel(WIDTH / 2, HEIGHT / 2, 255, 0, 0);

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			bitmap.setPixel(x, y, 255, 0, 0);
		}
	}

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
