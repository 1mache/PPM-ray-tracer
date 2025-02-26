#pragma once
#include <fstream>
#include <iostream>
#include "Vec3.h"
#include "Constants.h"

namespace Utils
{
#pragma pack(push, 1) // we want no padding in the structs!

    // info on headers: https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-storage
    
    struct BMPHeader {
        const uint16_t signature = 0x4D42; // "BM" - fixed value
        uint32_t fileSize;      // Total file size in bytes
        const uint32_t reserved = 0; // Reserved, always 0
        uint32_t dataOffset;    // Offset to pixel data (from start of file)
    };

    struct DIBHeader {
        const uint32_t headerSize = 40; // Always 40 for BITMAPINFOHEADER
        int32_t width;
        int32_t height;
        const uint16_t planes = 1;  // Always 1
        const uint16_t bitsPerPixel = 24; // 24-bit BMP
        const uint32_t compression = 0; // No compression
        uint32_t imageSize;  // Image data size (can be 0 for uncompressed BMPs)
        const int32_t xPixelsPerMeter = 2835; // 72 DPI
        const int32_t yPixelsPerMeter = 2835; // 72 DPI
        const uint32_t colorsUsed = 0; // All colors used
        const uint32_t importantColors = 0; // All colors important
    };

    struct RGBQuad
    {
        uint8_t r, g, b;
        const uint8_t reserved = 0;
    };

#pragma pack(pop) // restore allignment

    bool ppmToBmp(const std::string& ppmFileName)
	{
        std::ifstream ppmFile(ppmFileName);
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

        std::ofstream bmpFile(Constants::BMP_OUTPUT_FILE_NAME, std::ios_base::binary);

        bmpFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
        bmpFile.write(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));
        
        uint8_t r, g, b;
        while(ppmFile >> r >> g >> b)
        {
            RGBQuad pixelData = { r, g, b };
            bmpFile.write(reinterpret_cast<char*>(&pixelData), sizeof(pixelData));
        }

        ppmFile.close();
        bmpFile.close();
        return true;
	}
};