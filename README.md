# OpenGL_Renderer
A basic graphics renderer made with OpenGL.

This project is made following [The Cherno](https://www.youtube.com/@TheCherno)'s [OpenGL series](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2), and (hopefully) expanded upon i the future.

# Dependencies
- stb_image (found under src/vendor)

Dependencies listed here are **NOT** included in this repo, and needs to be installed manually.
- GLFW (A wrapper for window creation)
- GLEW (A wrapper for OpenGL instructions)

# Building
When dependencies are installed, use the following commands:
```
mkdir build
cd build
cmake ..
make
./app -2D
```

The argument '-2D' should display an image of Mario on a colorful background.
You can use `./app -help` for instructions on how to use additional arguments.
