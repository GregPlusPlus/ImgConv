# ImgConv
## An image convolution filtering program written in C++ and OpenCL

![Screen capture](doc/screenshot.png)

This program is written in C++ (using the Qt framework for the GUI), and OpenCL is used for the actual image processing.

### Presentation

The user can open an image, select an effect, adjust the parameters and then run the convolution. The program automatically generates a matrix according to the effect settings that is convoluted with the input image to produce the output image.

The output image can be feeded back to the input to chain effects.

The user can also import its own matrix to apply custom effects.

Some other useful features are implemented such as color-to-grascale conversion, color inversion and hitogram equalization.

An integrated code editor allows the user to edit its own OpenCL program, thus making much more complicated effects :
| Code editor | Example of complex effect |
| :---: | :---: |
| ![Code editor](doc/code_editor.png) | ![Bubble effect](doc/bubble_effect.png) |

A tiny OpenCL "library" was developped to provide basic pixel manipulation, convolution, geometry primitives, etc...

OpenCL code examples are provided in the [ImgConv/code_examples](ImgConv/code_examples) folder. The code editor can also generates basic code templates to start more easily.

Since an OpenCL kernel cannot be canceled, the convolution operation is divided in chunks (factor adjustable by the user) so the overall process can be monitored and the user can abort the process.

For now, french translations are available, through the _Help > Language_ menu.

### Build

Note : Currently, the build process is only valid for Windows with Qt \[MingGW kit\]. To build on Linux, the process should not be much different, except for the [OpenCL.lib](ImgConv/libs/lib) file that must be replaced with the Linux version.

Prerequisites : 
- Make sure Qt (6 or later, MinGW kit) is installed
- Make sure Git is available (needed for qmake to get the current git revision)
- Make sure OpenCL runtime + drivers are installed (needed for the program to run)

Steps :
1. Clone the repo
2. Open [ImgConv.pro](ImgConv/) with QtCreator
3. Set the kit to MinGW when asked
4. Run qmake
5. Build
6. Run

No external dependencies should be needed to actually build the project. As noted, to build on Linux the [OpenCL.lib](ImgConv/libs/lib) file must be replaced by his linux counterpart since this file was extracted from the Nvidia CUDA SDK on windows.

To be able to run the program, OpenCL runtime (.dll) must be installed, and _at least_ one OpenCL-compatible device must be available with his driver installed.