# ikik - High-Performance Network Analysis & Monitoring Tool

![License](https://img.shields.io/badge/license-GPL--3.0-blue.svg)
![C++](https://img.shields.io/badge/language-C%2B%2B17-00599C.svg)
![Qt](https://img.shields.io/badge/framework-Qt6-41CD52.svg)
![Platform](https://img.shields.io/badge/platform-Windows-0078D6.svg)

**ikik**, C++ ve Qt framework kullanılarak geliştirilmiş, düşük gecikmeli ve yüksek hassasiyetli bir ağ trafik analiz aracıdır. Modern yazılım mimarisi prensipleriyle tasarlanan bu proje, ağ kaynaklarının verimliliğini ölçmek ve veri iletim süreçlerini optimize etmek amacıyla geliştirilmiştir.

## 🚀 Öne Çıkan Özellikler

* **Asenkron Veri Yönetimi:** `QNetworkAccessManager` ile non-blocking mimaride ağ istekleri yönetimi.
* **Hassas Ölçüm Modülü:** `QElapsedTimer` entegrasyonu ile milisaniye bazlı veri transfer hızı hesaplama.
* **Modern Kullanıcı Deneyimi:** Windows 11 tasarım diliyle uyumlu, performans odaklı minimalist Qt GUI.
* **Modüler Derleme:** CMake & Ninja build sistemleri ile farklı platform ve CI/CD süreçlerine kolay entegrasyon.

## 🛠 Teknik Mimari ve Standartlar

Proje, özellikle savunma sanayii ve kritik sistem yazılımlarında aranan **modülerlik**, **kod okunabilirliği** ve **kaynak yönetimi** standartlarına uygun olarak yapılandırılmıştır.

* **Dil:** C++17
* **Arayüz Teknolojisi:** Qt 6.x
* **Yapılandırma:** CMake 3.16+
* **Derleyici:** Ninja / MSVC / MinGW

## 📦 Kurulum ve Derleme

Projeyi yerel ortamınızda derlemek için aşağıdaki adımları izleyin:

```bash
# Depoyu klonlayın
git clone [https://github.com/Flexsz/ikik.git](https://github.com/Flexsz/ikik.git)

# Build dizinini oluşturun
mkdir build && cd build

# CMake yapılandırmasını başlatın
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release

# Projeyi derleyin
ninja
