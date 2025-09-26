# Spiral with LittleCMS 🎨🌀

This project draws a colorful spiral using **SFML** for graphics and **LittleCMS (lcms2)** for color profile conversion.  
The spiral is rendered point by point, with colors generated in HSV space, converted from **AdobeRGB** to **sRGB** using LittleCMS, and displayed in real time.

---

## ✨ Features
- Draws a rainbow spiral (clockwise or counter‑clockwise).
- Uses **LittleCMS** to convert colors from AdobeRGB to sRGB.
- Smooth animation: spiral grows gradually instead of appearing instantly.
- Configurable point size, speed, and spiral direction.

---

## 📂 Project Structure
.   
├── CMakeLists.txt   
│  
├── main.cpp    
│  
├── color_utils.cc   
│  
├── color_utils.hh  
│  
├── convertColor.cc  
│  
├── convertColor.hh  
│  
├──cmake-wrapper/   # CMakeLists.txt for Little-CMS   
│  
├──profiles/    # contain *icc files  
│   
├── third_party/    # external libraries (fetched automatically by CMake)   
│  
└── README.md  


---

## ⚙️ Requirements
- **CMake** ≥ 3.15
- **C++20** compiler (tested with clang/LLVM and MSVC)
- **SFML 3.0.2** (fetched automatically via CMake FetchContent)
- **LittleCMS (lcms2)**

---

## 🔧 Build Instructions

```bash
# Clone the repository
git clone https://github.com/minh-9999/Dynamic-Spiral-with-Dots.git
cd Dynamic-Spiral-with-Dots

# Configure and build
cmake -B build -S .
cmake --build build
```
The build system will automatically fetch SFML into third_party/.  
Make sure you have lcms2 installed on your system or add it via FetchContent.


## ▶️ Run
./build/SpiralColors 

When you run the program, you’ll be asked to choose spiral direction:

```
Choose spiral direction:  
    1 - Counter‑clockwise  
    2 - Clockwise  
Your choice:  
```

## 🎛 Configuration
Spiral direction: chosen at runtime.

Point size: adjustable in main.cc (radius).

Speed: controlled by "pointsPerFrame" and "stepSeconds".

Boundary: number of points in the spiral.

## 📸 Preview
The program generates a vibrant spiral of colored dots, smoothly expanding from the center outward.  

## 📜 License
This project is released under the MIT License. SFML and LittleCMS are licensed under their respective terms.


