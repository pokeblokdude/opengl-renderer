# OpenGL Renderer (WIP)

A simple 3D rendering program written in C++, using GLFW and ImGui.

## Current Features

- Sample scene with textured primitives
- First-person camera controls when holding right-click
- Fake lighting based on camera angle

## Planned Features

- Simple lighting w/ Blinn-Phong shading
- Model loading from `.obj` files

## Building

I installed GLAD and GLFW using `vcpkg` (x64-windows versions). ImGui is included in the project as a Git submodule, and stb_image is simply included in the files (both in `/vendor/`).