# PPM-ray-tracer
Simple ray tracer that runs on the CPU and outputs to a .ppm and .bmp file.\
The output can be seen in the bin/ folder next to the .exe.

## Acknowledgements
 - [RayTracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera/cameraviewinggeometry)\
The project was made using this wonderful book as a guide, though, of course, some changes were made.
 - [Premake5](https://github.com/premake/premake-core)\
I put the premake exe file for windows in **premake/** for convenience. [Here](https://premake.github.io/download) you can download premake for other OS's.

## Building

Build the project by running:
```bash
  premake/premake5.exe vs2022
```
(if you're using VisualStudio2022)\
Or by executing build.bat (on Windows).\
This will create VisualStudio2022 project files inside the main folder.

This was tested on Windows, but in theory you should be able to build the project files for your specified editor if premake supports it.

## If you want to play with it
The main.cpp file contains an example on how to spawn spheres and materials for them. \ 
You can also change the image dimensions, FOV, lookat vector of the camera or its position vector by passing relevant arguments to ImageGenerator constructor.
