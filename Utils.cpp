#include "Utils.h"

namespace Utils
{
    bool ppmToBmp(const std::string& ppmFileName, const std::string& bmpFileName)
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

        if (format != Config::PPM_FORMAT)
        {
            std::cout << "Error: Wrong file format, should be P3!\n";
            return false;
        }

        Dimensions::dimension_t imgWidth, imgHeight;
        int maxColor;
        if (!(ppmFile >> imgWidth >> imgHeight >> maxColor))
        {
            std::cout << "Error: Couldnt read file dimensions\n";
            return false;
        }

        if (maxColor != Config::RGB_MAX)
        {
            std::cout << "Error: Wrong max color, should be:" << Config::RGB_MAX << "\n";
            return false;
        }

        BMPHeader bmpHeader = {};
        DIBHeader dibHeader = {};

        dibHeader.height = -imgHeight; // minus to mirror the image vertically, otherwise the image is upside down 
        dibHeader.width = imgWidth;
        uint32_t rowSize = imgWidth * sizeof(BGRQuad);
        dibHeader.imageSize = rowSize * imgHeight;

        bmpHeader.dataOffset = sizeof(bmpHeader) + sizeof(dibHeader);
        bmpHeader.fileSize = bmpHeader.dataOffset + dibHeader.imageSize;

        std::ofstream bmpFile(bmpFileName, std::ios_base::binary);

        bmpFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
        bmpFile.write(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));

        std::vector<BGRQuad> rowData(imgWidth);
        int ir, ig, ib; // rgb as ints

        for (int y = 0; y < imgHeight; y++)  // BMP stores bottom-up!
        {
            for (int x = 0; x < imgWidth; x++)
            {
                ppmFile >> ir >> ig >> ib;  // Read PPM pixel

                rowData[x] = { (uint8_t)ib, (uint8_t)ig, (uint8_t)ir };  // Store in row buffer
            }

            bmpFile.write(reinterpret_cast<char*>(rowData.data()), rowData.size() * sizeof(BGRQuad));  // Write row
        }

        ppmFile.close();
        bmpFile.close();
        return true;
    }

    Vec3 RNG::randomVector(const Interval& elementInterval)
    {
        Vec3 result = { random0to1(), random0to1(), random0to1() };
        // get result in the range of the given interval
        result *= elementInterval.size();
        result += Vec3(elementInterval.min(), elementInterval.min(), elementInterval.min());
        return result;
    };

    Vec3 RNG::randomOnUnitSphere()
    {
        Vec3 v;
        float vSquaredMag;
        float minimumMag = 0.0001f;
        do
        {
            // get vector with each element between -1 and 1
            v = randomVector({ -1,1 });
            vSquaredMag = v.squaredMagnitude();
        } while (vSquaredMag > 1 || vSquaredMag < minimumMag);
        //repeat until we get something inside the unit sphere but not too small

        return v.normalized();
    }
}