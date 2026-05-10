<p align="center">
  <img src="icon.png" alt="HWTracker Logo" width="120">
</p>

<h1 align="center">HWTracker</h1>

<p align="center">
  <strong>Real-Time Hardware Monitoring Tool for Windows</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Windows-10%2F11-blue?style=flat-square&logo=windows">
  <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square&logo=c%2B%2B">
  <img src="https://img.shields.io/badge/Qt-6.0-brightgreen?style=flat-square&logo=qt">
</p>

---

## Overview

**HWTracker** is a lightweight, real-time system monitoring application designed for Windows. It provides instant visibility into critical hardware metrics including CPU, GPU, RAM, disk usage, network activity, and running processes.

Designed with system administrators, performance engineers, and security researchers in mind — HWTracker delivers essential telemetry without unnecessary complexity.

---

## Features

| Module | Metrics |
|--------|---------|
| **CPU** | Usage (%), Frequency (MHz), Temperature (°C) |
| **GPU** | Usage (%), Core Clock, Temperature (°C) |
| **Memory** | Total, Used, Free (GB) |
| **Storage** | Total, Used, Free (GB) |
| **Network** | Local IP, MAC Address, Download/Upload Speed, Latency |
| **Processes** | Live process list with PID |

- **Live refresh** every 2 seconds
- **Built-in network latency test** (ICMP ping)
- **Process tracking** with PID
- **Dark, professional UI** optimized for extended monitoring sessions

---

## Technology Stack

| Component | Technology |
|-----------|------------|
| Language | C++17 |
| Framework | Qt 6 |
| Build System | CMake |
| Platform APIs | Windows API, WMI, IP Helper API |

---

## Screenshots

<p align="center">
  <img src="screenshot.png" alt="HWTracker Main Interface" width="650">
</p>

---

## Installation

### Prerequisites

- Windows 10 / 11 (64-bit)
- [Qt 6](https://www.qt.io/download) runtime (if building from source)

### Download

Pre-built binaries are available in the [Releases](https://github.com/SyKaya/HWTracker/releases) section.

### Build from Source

```bash
git clone https://github.com/SyKaya/HWTracker.git
cd HWTracker
mkdir build && cd build
cmake ..
cmake --build . --config Release
