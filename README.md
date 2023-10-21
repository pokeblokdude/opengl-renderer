# OpenGL Renderer (WIP)

A simple 3D rendering program written in C++, using GLFW and Dear ImGui.

### Controls

- While holding right-click:
    - **W:** Move forward
    - **S:** Move backward
    - **A:** Move left
    - **D:** Move right
    - **Q:** Move down
    - **E:** Move up
    - **Move mouse:** Rotate camera (first-person)
- **Scroll wheel:** Adjust camera speed

### Hotkeys

- **Ctrl+N:** New scene
- **Ctrl+O:** Open model
- **Escape (or Alt+F4):** Quit

## Current Features

- First-person camera controls when holding right-click
- Fake lighting based on camera angle
- Model loading from `.obj` files with textures/materials

## Planned Features

- Simple lighting w/ Blinn-Phong shading
- Orbit camera
- Scene hierarchy
- Transformation tools/gizmos

## Building

I installed GLAD, GLFW, Assimp and NativeFileDialog using `vcpkg` (x64-windows versions), so the easiest way to build is with Visual Studio (MSVC). Alternatively, you could use CMake with the appropriate include targets (I don't know much about it).

ImGui is included in the project as a Git submodule, and stb_image is simply included in the files (both in `/vendor/`).