#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include "Constants.h"

namespace Utils
{
#pragma pack(push, 1) // we want no padding in the structs!

    // info on bmp headers: https://learn.microsoft.com/en-us/windows/win32/gdi/bitmap-storage
    
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
        const uint16_t bitsPerPixel = 32; // 32-bit BMP
        const uint32_t compression = 0; // No compression
        uint32_t imageSize;  // Image data size (can be 0 for uncompressed BMPs)
        const int32_t xPixelsPerMeter = 2835; // 72 DPI
        const int32_t yPixelsPerMeter = 2835; // 72 DPI
        const uint32_t colorsUsed = 0; // All colors used
        const uint32_t importantColors = 0; // All colors important
    };

    struct BGRQuad
    {
        uint8_t b = 0;
        uint8_t g = 0;
        uint8_t r = 0;

        BGRQuad() = default;
        BGRQuad(uint8_t _b, uint8_t _g, uint8_t _r) : b(_b), g(_g), r(_r) {};
    private:
        uint8_t reserved = 0; // so that every pixel is 4 bytes
    };

#pragma pack(pop) // restore allignment

    bool ppmToBmp(const std::string& ppmFileName, const std::string& bmpFileName);

    // gets the path to dir where the executable sits 
    inline std::filesystem::path getExePath()
    {
        return std::filesystem::path(__argv[0]).parent_path();
    }
};