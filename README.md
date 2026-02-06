# Panorama Image Stitcher 🖼️

A C++ application for creating panoramic images from multiple photographs using OpenCV.

## 📋 Description

This project enables automatic combination of multiple images into a single panorama, with support for different projection types and advanced image processing.

## ✨ Features

- **Automatic stitching** of multiple images
- **Three projection types**:
  - Cylindrical (default)
  - Spherical
  - Planar
- **Inverse projection** for inward curvature
- **Automatic cropping** to remove black areas
- **Inpainting** for remaining black regions
- **Alphabetical sorting** of images for correct order

## 🛠️ Prerequisites

- **C++17** or newer
- **CMake** 3.10+
- **OpenCV** 4.x (with stitching module)

## 📦 Installation

### Installing OpenCV

1. Download OpenCV from [opencv.org](https://opencv.org/releases/)
2. Extract and note the installation path

### Project Setup

1. Clone the repository:
```bash
git clone https://github.com/Victor017936/panorama.git
cd panorama
```

2. Update the OpenCV path in `CMakeLists.txt`:
```cmake
set(OpenCV_DIR "C:/OpenCV/opencv/build/x64/vc16/lib")
```

3. Create build directory and compile:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 🚀 Usage

```bash
panorama.exe <folder_path> [output_name] [projection] [inside]
```

### Parameters

- `<folder_path>` - **Required**: Path to the folder containing images
- `[output_name]` - Optional: Output file name (default: `imagine_finala.jpg`)
- `[projection]` - Optional: Projection type
  - `cylindrical` (default)
  - `spherical`
  - `plane`
- `[inside]` - Optional: Add `inside` parameter for inward curvature

### Examples

```bash
# Standard cylindrical panorama
panorama.exe images/

# Spherical panorama with custom name
panorama.exe images/ output.jpg spherical

# Panorama with inward curvature
panorama.exe images/ result.jpg cylindrical inside
```

## 📁 Project Structure

```
Panorama/
├── src/
│   └── main.cpp          # Main source code
├── images/               # Folder for test images
├── CMakeLists.txt        # CMake configuration
└── README.md
```

## ⚙️ Technical Details

### Stitcher Configuration

- **Confidence threshold**: 0.65
- **Seam estimation resolution**: 0.5
- **Registration resolution**: 0.6
- **Wave correction**: Horizontal enabled

### Supported Formats

- JPEG (.jpg, .jpeg)
- PNG (.png)
- BMP (.bmp)
- TIFF (.tif, .tiff)

## 📝 License

This project is open-source and available for free use.

## 🤝 Contributing

Contributions are welcome! Open an issue or submit a pull request.

## 👤 Author

Victor - [@Victor017936](https://github.com/Victor017936)

## 🙏 Acknowledgments

- OpenCV for the excellent image processing library
- Open-source community for inspiration and support
