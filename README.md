# ikik | High-Precision Network Throughput Analyzer

![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Qt Version](https://img.shields.io/badge/Qt-6.10-green.svg)
![Build System](https://img.shields.io/badge/Build-CMake%20%2F%20Ninja-orange.svg)
![License](https://img.shields.io/badge/License-GPL--3.0-red.svg)

**ikik**, kritik ağ altyapılarında veri iletim performansını ölçmek, asenkron ağ trafiğini analiz etmek ve sistem üzerindeki throughput (iş çıkarma kapasitesi) limitlerini belirlemek amacıyla geliştirilmiş mühendislik odaklı bir ağ analiz aracıdır.

---

## 🛠 Teknik Mühendislik Özellikleri

Proje geliştirme sürecinde, savunma sanayii standartlarında aranan **deterministik yaklaşımlar** ve **kaynak optimizasyonu** ön planda tutulmuştur:

* **Non-Blocking I/O Mimarisi:** `QNetworkAccessManager` kullanılarak geliştirilen asenkron event-loop yapısı sayesinde arayüz donmaları engellenmiş ve ağ istekleri paralelize edilmiştir.
* **Düşük Seviyeli Zamanlama (Low-Level Timing):** `QElapsedTimer` ile CPU cycle hassasiyetinde ölçümler yapılarak, gerçek zamanlı veri hızı (bps) hesaplamalarında sapma payı minimize edilmiştir.
* **Custom Widget Architecture:** Standart bileşenlerin ötesine geçilerek, kullanıcı etkileşimini artırmak adına `DraggableLabel` gibi özelleştirilmiş sınıflar üzerinden OOP prensipleri uygulanmıştır.
* **Windows Resource Integration:** Uygulama seviyesinde `.rc` entegrasyonu ile sistem kaynakları (icons, metadata) doğrudan binary içerisine gömülmüştür.

## 🏗 Sistem Mimarisi

Uygulama, **MVC (Model-View-Controller)** benzeri bir ayrıştırma ile tasarlanmıştır:
- **UI Layer:** `.ui` ve `mainwindow.ui` üzerinden deklaratif arayüz yönetimi.
- **Logic Layer:** Network stack ve hız hesaplama algoritmaları.
- **Resource Layer:** `.qrc` üzerinden statik varlıkların bellek optimizasyonu.

## 🚀 Derleme ve Dağıtım (Build Strategy)

Proje, modern derleme standartları olan **CMake** ve **Ninja** kullanılarak yapılandırılmıştır.

### Gereksinimler
- Qt 6.x (MinGW 13.1.0 veya üstü)
- CMake 3.16+
- Ninja Build Tool

### Derleme Adımları
```bash
# 1. Depoyu klonlayın
git clone [https://github.com/Flexsz/ikik.git](https://github.com/Flexsz/ikik.git) && cd ikik

# 2. Build dizini oluşturun ve yapılandırın
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

# 3. Binary üretimini başlatın
cmake --build build --parallel 8
