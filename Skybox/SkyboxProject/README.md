# Skybox Project

## Overview
The Skybox Project is a graphical application that displays three spheres representing the Sun, Earth, and Moon, rotating around a central point in a skybox environment. The application utilizes Qt for the GUI and OpenGL for rendering.

## Project Structure
```
SkyboxProject
├── textures
│   ├── background.png  // Background image for the skybox
│   ├── earth.jpg       // Texture for the Earth sphere
│   ├── moon.jfif      // Texture for the Moon sphere
│   └── sun.jfif       // Texture for the Sun sphere
├── src
│   ├── main.cpp        // Entry point of the application
│   ├── glwidget.h      // Header file for the GLWidget class
│   └── glwidget.cpp     // Implementation of the GLWidget class
├── build               // Directory for compiled files
├── CMakeLists.txt      // CMake configuration file
└── README.md           // Documentation for the project
```

## Setup Instructions
1. **Clone the repository**:
   ```
   git clone <repository-url>
   cd SkyboxProject
   ```

2. **Install dependencies**:
   Ensure you have Qt and CMake installed on your system.

3. **Build the project**:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the application**:
   After building, execute the generated binary to launch the application.

## Usage
- The application will display a skybox with the background image and three rotating spheres representing the Sun, Earth, and Moon.
- The spheres will rotate around a central point, providing a dynamic visual experience.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.