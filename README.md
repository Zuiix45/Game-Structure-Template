<h1 align="center">
    Game Structure Template
</h1>

This project provides an environment for creating 2D games with c++ and OpenGL. It offers wide range of lightweight systems and essential components. It can be a starting point of any 2D game project.

## Features
* **2D Rendering:** Handles everything for 2D rendering inside GPU.
* **Object Management:** Provides a system for handling all objects and their attributes like coordinates.
* **Sprite Management:** Implements easy to use sprite and animation rendering system.
* **Resource Management:** Reads all resources in a specific folder automatically.
* **Flexible Structure:** Modular design of systems and components makes expansion easier.
* **Window management and input handling:** GLFW3 library makes window creation and input handling easier.

## Getting Started
To use this template, follow these steps:

1. **Clone the repository recursively:** 
```bash
git clone --recursive https://github.com/Zuiix45/Game-Structure-Template.git
```

2. **Create required folders:**
```bash
cd The-Game
mkdir build
mkdir src/.Game
```

3. **Build the project:** CMake is essential for building the project.
After downloading CMake follow these steps:
```bash
cd build
cmake .. -G "compiler-goes-here"
cmake --build .
#Checkout CMake documentation for more info
```

4. **Run the executable file:** You can find executable file inside bin folder if the project compiled properly.

5. **Create your own game:** Use built-in systems and components to create a game. You don't have involve any other folders except your game folder

6. ***DON'T forget to check out [example branches](https://github.com/Zuiix45/Game-Structure-Template/tree/example-1) and [documents](https://docs.google.com/document/d/1-xHisD3rndT31Uj1_URGL3GEwytmkYkRCA825woLIGc/edit?usp=sharing).***

7. ***Please let me know if you have suggestions or issues.***

## Future Updates
* Physics engine improvements
* GPU Particles
* Lighting system

## License
This project is licensed under the GPL v3 license - see the [LICENSE](https://github.com/Zuiix45/Game-Structure-Template/blob/master/LICENSE)
