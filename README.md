<p align="center">
  <img src="docs/icon.png" alt="HWTracker" width="128">
</p>

<h1 align="center">HWTracker</h1>

<p align="center">
  <strong>Professional Real-Time Hardware Monitoring & System Telemetry Tool for Windows</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Windows%2010%20%7C%2011-0078d7?style=flat-square&logo=windows">
  <img src="https://img.shields.io/badge/Standard-C%2B%2B17-00599c?style=flat-square&logo=c%2B%2B">
  <img src="https://img.shields.io/badge/Framework-Qt%206-41cd52?style=flat-square&logo=qt">
  <img src="https://img.shields.io/badge/Build-CMake-064f8c?style=flat-square&logo=cmake">
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=flat-square">
  <img src="https://img.shields.io/badge/Status-Stable-brightgreen?style=flat-square">
</p>

---

## 📌 Overview

**HWTracker** is a lightweight yet powerful hardware monitoring application designed for Windows systems. It provides real-time telemetry data for critical system components including CPU, GPU, RAM, storage, network interfaces, and active processes.

Developed with performance engineers, system administrators, and security researchers in mind — HWTracker delivers accurate, low-latency hardware metrics through a clean, professional interface.

---

## 🎯 Key Capabilities

| Component | Monitored Metrics |
|-----------|-------------------|
| **CPU** | Utilization (%), Core Frequency (MHz), Temperature (°C) |
| **GPU** | Utilization (%), Core Clock (MHz), Temperature (°C) |
| **Memory (RAM)** | Total Capacity (GB), Used (GB), Available (GB), Usage (%) |
| **Storage** | Total Capacity (GB), Used (GB), Available (GB), Usage (%) |
| **Network** | IPv4 Address, MAC Address, Download/Upload Speed (MB/s), ICMP Latency (ms) |
| **Processes** | Live process list with Process ID (PID) |

---

## ⚙️ Technical Architecture

| Layer | Technology |
|-------|------------|
| **Language** | C++17 |
| **GUI Framework** | Qt 6 (Widgets, Network, Core modules) |
| **Build System** | CMake 3.16+ |
| **Platform API** | Windows API, IP Helper API, WMI |
| **Performance** | Lightweight event-driven updates |
| **Deployment** | Single portable executable |

---

## 🔧 System Requirements

| Requirement | Minimum |
|-------------|---------|
| **OS** | Windows 10 / 11 (64-bit) |
| **CPU** | Any x86_64 processor |
| **RAM** | 256 MB |
| **Disk** | 15 MB free space |
| **Dependencies** | None (static linking) |

---

## 🚀 Features in Detail

### CPU Monitoring
- Real-time utilization percentage
- Current operating frequency
- Thermal reading (when available)
- Multi-core architecture support

### GPU Monitoring
- Utilization tracking
- Core clock frequency
- Temperature monitoring (for supported GPUs)

### Memory & Storage
- Accurate capacity detection
- Real-time used/free calculations
- Usage percentage with visual progress bars

### Network Analysis
- Local IPv4 address detection (automatic interface selection)
- MAC address retrieval
- Download/Upload speed calculation (bytes monitoring)
- ICMP-based latency testing (8.8.8.8)

### Process Management
- Live enumeration of all running processes
- PID display for each process
- Clean, scrollable list interface

### User Interface
- Dark theme optimized for long monitoring sessions
- Live data refresh (2-second intervals)
- Manual refresh button
- Built-in network latency test button
- Resizable, modern layout with splitter support

---

## 📥 Installation

### Option 1: Pre-built Binary

1. Download the latest `HWTracker.exe` from [Releases](https://github.com/SyKaya/HWTracker/releases)
2. Run directly — no installation required

### Option 2: Build from Source

```bash
# Clone repository
git clone https://github.com/SyKaya/HWTracker.git
cd HWTracker

# Configure and build
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2019_64"
cmake --build . --config Release

# Run
./Release/HWTracker.exe
