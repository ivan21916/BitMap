#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>
#include <memory>
using namespace std;

namespace bitmapstruct{

class BitMap
{
public:
	BitMap(int width, int height);
	~BitMap();
	bool write(string filename);
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue); // uint8_t為unsigned的8 bits, 同等於unsigned char
	
private:
	int m_width{0};
	int m_height{0};
	unique_ptr<uint8_t[]> m_pPixels{nullptr}; 
};

}
#endif
