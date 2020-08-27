#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint> // �i�H�]�w��Ʀ줸�j�p 

using namespace std;

#pragma pack(2) // ����struct�̦�extra padding bytes

namespace bitmapstruct{

struct BitmapFileHeader{
	char header[2]{'B', 'M'};
	int32_t fileSize;
	int32_t reserved{0};
	int32_t dataOffset;
};

}




#endif
