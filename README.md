# PPM-ray-tracer
Simple ray tracer that runs on the CPU and outputs to a .ppm and .bmp file.\
The output can be seen in the bin/ folder next to the .exe.\
![Screenshot](https://github.com/1mache/PPM-ray-tracer/images/random.bmp)

## Acknowledgements
 - [RayTracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera/cameraviewinggeometry)\
The project was made using this wonderful book as a guide, though, of course, changes were made.
 - [Premake5](https://github.com/premake/premake-core)\
I put the premake exe file for windows in **premake/** for convenience. [Here](https://premake.github.io/download) you can download premake for other OS's.

## Project Description

The goal of the project was to get a feel of graphics and rendering in their simplest form,\
in the [book](https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera/cameraviewinggeometry) Peter Shirley suggests creating
an image in the [.ppm format](https://en.wikipedia.org/wiki/Netpbm#File_formats) and thats how I started as well.\
In a nutshell a *ppm* is a text file where each line represents a pixel in the RGB format, you can look at it in the `images` folder.\
Needless to say they weigh a lot since no compression at all is involved, but the bigger problem was that Windows` photo viewer doesn't recognize them as images\
which was quite annoying while debugging. So I ended up making the program output to a .bmp file which doesn't have that issue.\
A bmp file is also uncompressed pixel data but instead it is a binary file, so converting the output to it wasn't a big deal.


## Building

Build the project by running:
```bash
  premake/premake5.exe vs2022
```
(if you're using *VisualStudio2022*)\
Or by executing `build.bat` (on Windows).\
This will create VisualStudio2022 project files inside DonkeyKong/ folder.

This was tested on Windows, but in theory you should be able to build the project files for your specified editor if premake supports it.

## If you want to play with it
The main.cpp file contains an example on how to spawn spheres and materials for them.\
You can also change the image dimensions, FOV, lookat vector of the camera or its position vector by passing relevant arguments to ImageGenerator constructor.
