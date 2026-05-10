# ikik | High-Precision Network Throughput Analyzer

![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Qt Version](https://img.shields.io/badge/Qt-6.10-green.svg)
![Build System](https://img.shields.io/badge/Build-CMake%20%2F%20Ninja-orange.svg)
![License](https://img.shields.io/badge/License-GPL--3.0-red.svg)

**ikik** is an engineering-grade network analysis tool designed to measure data transmission performance, analyze asynchronous network traffic, and determine system throughput limits within critical network infrastructures.

---

## 🛠 Engineering & Technical Specifications

The development process prioritizes **deterministic approaches** and **resource optimization**, which are essential for defense industry software standards:

* **Non-Blocking I/O Architecture:** Implemented via an asynchronous event-loop using `QNetworkAccessManager`, ensuring a responsive GUI while parallelizing multiple network requests.
* **Low-Level Timing Precision:** Utilizes `QElapsedTimer` to achieve CPU cycle-level precision, minimizing margins of error in real-time bits-per-second (bps) calculations.
* **Custom Widget Architecture:** Extends beyond standard components by implementing specialized classes like `DraggableLabel`, demonstrating robust OOP principles and custom UI interaction handling.
* **System Resource Integration:** Deep integration with Windows `.rc` resources, embedding application metadata and high-fidelity icons directly into the binary executable.

## 🏗 System Architecture

The application is designed with a separation of concerns similar to the **MVC (Model-View-Controller)** pattern:
- **UI Layer:** Managed via `.ui` declarations and `mainwindow.ui` for a scalable and maintainable interface.
- **Logic Layer:** Core network stack and optimized throughput calculation algorithms.
- **Resource Layer:** Efficient memory management of static assets via the Qt Resource System (`.qrc`).

## 🚀 Build & Deployment Strategy

The project utilizes modern build standards, specifically **CMake** and **Ninja**, for rapid and reliable compilation.

### Prerequisites
- Qt 6.x (MinGW 13.1.0 or higher recommended)
- CMake 3.16+
- Ninja Build Tool

### Build Instructions
```bash
# 1. Clone the repository
git clone [https://github.com/Flexsz/ikik.git](https://github.com/Flexsz/ikik.git) && cd ikik

# 2. Configure the build directory
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

# 3. Execute the build process
cmake --build build --parallel 8
