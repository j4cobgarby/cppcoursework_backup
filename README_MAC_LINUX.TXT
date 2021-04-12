I suggest to use the proper config long term, but you could use the quick run options at the bottom of this file short term if necessary.



Proper Configuration for Mac or Linux - using cmake
===================================================

This uses cmake to find the required libraries and build the relevant project files for your preferred build system. You will need to have installed cmake (cmake.org) along with the relevant SDL libraries (SDL2, SDL2_ttf and SDL2_image). These exist for Windows, Mac and Linux and should be installed in the appropriate manner.


1) Install the SDL development libraries mentioned above (SDL2, SDL2_ttf and SDL2_image).


2) Download and unzip the supplied zip file of source code for the windows project.


3) Download and unzip the file of Linux/Mac additions into exactly the same directory. I.e. the one directory will contain a number of sub-directories including make, build and src.


4) Ensure that you have cmake installed. Either build it (see https://cmake.org/install/ ) or use something like Homebrew on Mac to install it (https://brew.sh , then 'brew install cmake').


5) Move to the build directory of your project, e.g. cd <somepath>/CPPCoursework2021.../build
(This is one of the directories that you unzipped from the new Linux\Mac additions zip file.)


6) Generate the build files for the project, using cmake options a, b or c:

6a) Mac/Xcode instructions:

On a Mac, assuming you've followed the steps above you would execute the following:

cmake -G Xcode ..

which would generate a G52CPP.xcodeproj that can be opened in XCode to build the project. 
(Note: the .. means to look in the parent directory for the CMakeLists.txt file and the cmake directory.)

Hint: When I tried this on a Mac, having used Brew to install cmake, I had to run 'sudo xcode-select --reset' (see https://stackoverflow.com/questions/41380900/cmake-error-no-cmake-c-compiler-could-be-found-using-xcode-and-glfw ) before CMake would find the compiler.

Then use Xcode to build the project.
Hint: if it runs but no text appears on the screen then ensure you copy the .ttf files and image files from the src directory into the directory you are running the application from (the current directory).

6b) Mac/Linux Make/gcc options:

Under linux or Mac, make files can be created using:

cmake -G 'Unix Makefiles' ..

instead (note the single quotation marks), which will generate a Makefile that can be used to build the project. 

You can then edit the files and project/Makefiles as normal to complete your coursework. 

In this case to make the project just run 'make' from the build directory. (I must admit that even on Mac I found this a lot more straight forward than Xcode, but I guess you know Xcode better than me.)

6c) Similar generators exist for cmake to create build files for VisualStudio, Eclipse etc if you prefer those environments.




Linux or Mac Quick Run
======================

In the Linux_Simplistic_Makefile and Mac_simplistic_makefile directories are two VERY simplistic makefiles. Don't use these longterm, but if you have cmake issues, they may help you out to get going until you fix cmake and generate a reasonable makefile for yourself.

These are simplistic because they will not take account of dependencies correctly. e.g. a good makefile should ensure that if you change a header file the files which include it are recompiled. This will not do that.
1) Install your sdl devel files - for SDL2, SDL2_ttf and SDL2_image.
2) Copy the relevant makefile to your src directory.
3) Run make

Note: the files are set up to use ../SDL as the directory with header files in. You may want to change this to use the SDL header files that you installed instead.
The mac makefile works on the machines in the maclab - BUT it is a quick Hack to allow me to test the source code before cmake was installed. DO NOT USE THESE LONGTERM - instead use cmake to generate a better makefile.

