# Panorama Image Stitcher 🖼️

Aplicație C++ pentru crearea de imagini panoramice din mai multe fotografii folosind OpenCV.

## 📋 Descriere

Acest proiect permite combinarea automată a mai multor imagini într-o singură panoramă, cu suport pentru diferite tipuri de proiecții și procesare avansată a imaginii.

## ✨ Funcționalități

- **Stitching automat** de imagini multiple
- **Trei tipuri de proiecții**:
  - Cilindrică (implicit)
  - Sferică
  - Plană
- **Proiecție inversă** pentru curbură interioară
- **Decupare automată** pentru eliminarea zonelor negre
- **Retușare** (inpainting) a zonelor negre rămase
- **Sortare alfabetică** a imaginilor pentru ordinea corectă

## 🛠️ Prerequisite

- **C++17** sau mai nou
- **CMake** 3.10+
- **OpenCV** 4.x (cu modulul stitching)

## 📦 Instalare

### Instalare OpenCV

1. Descarcă OpenCV de la [opencv.org](https://opencv.org/releases/)
2. Extrage și notează calea de instalare

### Configurare proiect

1. Clonează repository-ul:
```bash
git clone https://github.com/TauConteleElveti/panorama.git
cd panorama
```

2. Actualizează calea către OpenCV în `CMakeLists.txt`:
```cmake
set(OpenCV_DIR "C:/OpenCV/opencv/build/x64/vc16/lib")
```

3. Creează directorul de build și compilează:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 🚀 Utilizare

```bash
panorama.exe <cale_folder> [nume_output] [proiecție] [inside]
```

### Parametri

- `<cale_folder>` - **Obligatoriu**: Calea către folderul cu imagini
- `[nume_output]` - Opțional: Numele fișierului de ieșire (implicit: `imagine_finala.jpg`)
- `[proiecție]` - Opțional: Tipul de proiecție
  - `cylindrical` (implicit)
  - `spherical`
  - `plane`
- `[inside]` - Opțional: Adaugă parametrul `inside` pentru curbură interioară

### Exemple

```bash
# Panoramă cilindrică standard
panorama.exe images/

# Panoramă sferică cu nume personalizat
panorama.exe images/ output.jpg spherical

# Panoramă cu curbură interioară
panorama.exe images/ result.jpg cylindrical inside
```

## 📁 Structură proiect

```
Panorama/
├── src/
│   └── main.cpp          # Codul sursă principal
├── images/               # Folder pentru imagini de test
├── CMakeLists.txt        # Configurație CMake
└── README.md
```

## ⚙️ Detalii tehnice

### Configurație Stitcher

- **Prag de încredere**: 0.65
- **Rezoluție estimare cusături**: 0.5
- **Rezoluție înregistrare**: 0.6
- **Corecție ondulații**: Orizontală activată

### Formate suportate

- JPEG (.jpg, .jpeg)
- PNG (.png)
- BMP (.bmp)
- TIFF (.tif, .tiff)

## 📝 Licență

Acest proiect este open-source și disponibil pentru utilizare liberă.

## 🤝 Contribuții

Contribuțiile sunt binevenite! Deschide un issue sau trimite un pull request.

## 👤 Autor

Victor - [@TauConteleElveti](https://github.com/TauConteleElveti)

## 🙏 Mulțumiri

- OpenCV pentru biblioteca excelentă de procesare imagine
- Comunitatea open-source pentru inspirație și suport
