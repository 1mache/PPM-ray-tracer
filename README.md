# PPM-ray-tracer
#### A simple ray tracing program that runs on the CPU and outputs to a .ppm and .bmp file.

![Screenshot](https://github.com/1mache/PPM-ray-tracer/blob/main/images/random1.bmp)

## Acknowledgements
 - [RayTracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera/cameraviewinggeometry)\
The project was made using this wonderful book as a guide, though, of course, changes were made.
 - [Premake5](https://github.com/premake/premake-core)\
I put the premake exe file for windows in **premake/** for convenience. [Here](https://premake.github.io/download) you can download premake for other OS's.

## Project Description

The goal of the project was to get a feel of graphics and rendering in their simplest form, a static image.\
Onto this image we render objects from the three dimesional world that we describe in the code by using a technique called ✨*Ray Tracing*✨.\
The best explanation is in the book that I linked, but to put it really simply, it involves having a ray, sort of like a ray of light, shot from a pixel on the screen
into the world we render and asking "what did you hit?", "did that thing reflect you? did you pass through it?", "what color was it?".\
The project ended up taking way more than a weekend, since it involves quite a bit of math and physics formulas which I tried to understand instead of using them blindly.\
I feel like it gave me my first glimpse into the world of graphics programming, and fueled my passion for the subject.\
I will definitely continue to explore it further and come back with even more exciting projects.

## In more detail

- There is no dependencies in the project, it writes raw pixel data into binary/text files.
- The only object in the world is a sphere since, of all 3D objects spheres have the simplest mathematical formula for checking intersection.\
- There are 3 Materials:
#### Matte objects (Lambertian)
Matte objects reflect the ray in a random direction (in a certain range) and add a can reflect some colors more than others,\
this is also true for the Metal material and it's called the *albedo*. If a sphere reflects the red component more than other ones,\
it will apear reddish, if it reflects red and blue the same amount it will appear purplish etc.
![Matte](https://github.com/1mache/PPM-ray-tracer/blob/main/images/matte.bmp)

#### Metal objects
Metal also has an albedo, there are metals in different colors so it makes sense. The difference between them and matte objects is that\
they are better at reflecting. The Metal class has a fuzziness member which allows you to make metals that are well ... fuzzy,\
or perfect mirrors.
![Metal](https://github.com/1mache/PPM-ray-tracer/blob/main/images/metal.bmp)

#### Dielectrics
Transparent materials that let light true but refract it in an angle defined by material specific ratio called the [refractive index](https://en.wikipedia.org/wiki/Refractive_index).\
The examples for them would be glass or water.
![Dielectric](https://github.com/1mache/PPM-ray-tracer/blob/main/images/dielectric.bmp)

- The camera class has a few members that let us toggle how we look at the world, like position, direction that we look in, and FOV.
- Image format: in the [book](https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera/cameraviewinggeometry) Peter Shirley suggests creating
an image in the [.ppm format](https://en.wikipedia.org/wiki/Netpbm#File_formats) and thats how I started as well.\
In a nutshell a *ppm* is a text file where each line represents a pixel in the RGB format, you can look at it in the `images` folder.\
Needless to say they weigh a lot since no compression at all is involved, but the bigger problem was that Windows` photo viewer doesn't recognize them as images\
which was quite annoying while debugging. So I ended up making the program output to a .bmp file which doesn't have that issue.\
A bmp file is also uncompressed pixel data, but instead it is a binary file, so converting the output to it wasn't a big deal.

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
