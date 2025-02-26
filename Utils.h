#pragma once
#include <fstream>
#include <iostream>
#include "Vec3.h"
#include "Constants.h"

namespace Utils
{
#pragma pack(push, 1) // we want no padding in the structs!

    struct BMPHeader {
        static constexpr uint16_t signature = 0x4D42; // "BM" - fixed value
        uint32_t fileSize;      // Total file size in bytes
        static constexpr uint32_t reserved = 0; // Reserved, always 0
        uint32_t dataOffset;    // Offset to pixel data (from start of file)
    };

    struct DIBHeader {
        static constexpr uint32_t headerSize = 40; // Always 40 for BITMAPINFOHEADER
        int32_t width;
        int32_t height;
        static constexpr uint16_t planes = 1;  // Always 1
        static constexpr uint16_t bitsPerPixel = 24; // 24-bit BMP
        static constexpr uint32_t compression = 0; // No compression
        uint32_t imageSize;  // Image data size (can be 0 for uncompressed BMPs)
        static constexpr int32_t xPixelsPerMeter = 2835; // 72 DPI
        static constexpr int32_t yPixelsPerMeter = 2835; // 72 DPI
        static constexpr uint32_t colorsUsed = 0; // All colors used
        static constexpr uint32_t importantColors = 0; // All colors important
    };

#pragma pack(pop) // restore allignment

    bool ppmToBmp(std::ifstream& ppmFile)
	{
        if (!ppmFile.is_open())
        {
            std::cout << "Error: The file isn`t open!\n";
            return false;
        }

        std::string format;
        if (!(ppmFile >> format)) 
        {  
            std::cout << "Error: Could not read file or file is empty!\n";
            return false;
        }

        if (format != Constants::PPM_FORMAT) 
        { 
            std::cout << "Error: Wrong file format, should be P3!\n";
            return false;
        }

        Constants::dimension_t imgWidth, imgHeight;
        if(!(ppmFile >> imgWidth >> imgHeight))
        {
            std::cout << "Error: Couldnt read file dimensions\n";
            return false;
        }
        
        BMPHeader bmpHeader = {};
        DIBHeader dibHeader = {};

        dibHeader.height = imgHeight;
        dibHeader.width = imgWidth;
        uint32_t rowSize = (imgWidth * 3 + 3) & ~3;  // row size calculation + 4-byte alignment
        dibHeader.imageSize = rowSize * imgHeight;

        bmpHeader.dataOffset = sizeof(bmpHeader) + sizeof(dibHeader);
        bmpHeader.fileSize = bmpHeader.dataOffset + dibHeader.imageSize;


        return true;
	}
};