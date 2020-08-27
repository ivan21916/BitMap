#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint> // 可以設定整數位元大小 

using namespace std;

#pragma pack(2) // 防止struct裡有extra padding bytes

namespace bitmapstruct{

struct BitmapFileHeader{
	char header[2]{'B', 'M'};
	int32_t fileSize;
	int32_t reserved{0};
	int32_t dataOffset;
};

}




#endif
