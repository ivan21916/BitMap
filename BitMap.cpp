#include "bitmap.h"
#include "bitmapinfoheader.h"
#include "bitmapfileheader.h"
#include <fstream>

using namespace bitmapstruct;
using namespace std;

namespace bitmapstruct{

BitMap::BitMap(int width, int height):m_width(width), m_height(height), m_pPixels(new uint8_t[width*height*3]{}){ 
	
}

bool BitMap::write(string filename){
	
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	
	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width*m_height*3;
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
	
	infoHeader.width = m_width;
	infoHeader.height = m_height;
	
	ofstream file;
	
	file.open(filename, ios::out|ios::binary); // ios::out|ios::binary如果使用ofstream物件可不加, 使用fstream時須加上 
	
	if(!file){ // 檢查file是否正常開啟 
		return false;
	} 

	file.write((char *)&fileHeader, sizeof(fileHeader)); // 待寫入參數的參數必須轉換型態成(char *) 
	file.write((char *)&infoHeader, sizeof(infoHeader));
	file.write((char *)m_pPixels.get(), m_width*m_height*3);
	file.close();

	if(!file){ // 檢查file是否正常關閉 
		return false;
	} 
	return true;	
}

void BitMap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue){
	uint8_t* pPixel = m_pPixels.get(); // unique_ptr不能被轉換為uint8_t, 但是可以使用get()來取得一個由unique_ptr管理的pointer(同樣指向m_pPixels)

	pPixel += (y * 3) * m_width + (x * 3);

	pPixel[0] = blue; // 因為bitmap是little endian format, 所以記憶體會從數值小的開始存(反向存取)
	pPixel[1] = green;
	pPixel[2] = red;
}

BitMap::~BitMap(){
	
}

}
