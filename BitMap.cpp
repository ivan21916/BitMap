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
	
	file.open(filename, ios::out|ios::binary); // ios::out|ios::binary�p�G�ϥ�ofstream����i���[, �ϥ�fstream�ɶ��[�W 
	
	if(!file){ // �ˬdfile�O�_���`�}�� 
		return false;
	} 

	file.write((char *)&fileHeader, sizeof(fileHeader)); // �ݼg�J�Ѽƪ��Ѽƥ����ഫ���A��(char *) 
	file.write((char *)&infoHeader, sizeof(infoHeader));
	file.write((char *)m_pPixels.get(), m_width*m_height*3);
	file.close();

	if(!file){ // �ˬdfile�O�_���`���� 
		return false;
	} 
	return true;	
}

void BitMap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue){
	uint8_t* pPixel = m_pPixels.get(); // unique_ptr����Q�ഫ��uint8_t, ���O�i�H�ϥ�get()�Ө��o�@�ӥ�unique_ptr�޲z��pointer(�P�˫��Vm_pPixels)

	pPixel += (y * 3) * m_width + (x * 3);

	pPixel[0] = blue; // �]��bitmap�Olittle endian format, �ҥH�O����|�q�ƭȤp���}�l�s(�ϦV�s��)
	pPixel[1] = green;
	pPixel[2] = red;
}

BitMap::~BitMap(){
	
}

}
