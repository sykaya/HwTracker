<p align="center">
  <img src="assets/image.png" alt="HWTracker" width="128">
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
  <img src="https://img.shields.io/badge/License-GPLv3-blue?style=flat-square&logo=gnu">
  <img src="https://img.shields.io/badge/Status-Stable-brightgreen?style=flat-square">
</p>

---

## Overview

**HWTracker** is a lightweight yet powerful hardware monitoring application designed for Windows systems. It provides real-time telemetry data for critical system components including CPU, GPU, RAM, storage, network interfaces, and active processes.

Developed with performance engineers, system administrators, and security researchers in mind — HWTracker delivers accurate, low-latency hardware metrics through a clean, professional interface.

---

## Key Capabilities

| Component | Monitored Metrics |
|-----------|-------------------|
| CPU | Utilization, Core Frequency (MHz), Temperature (C) |
| GPU | Utilization, Core Clock (MHz), Temperature (C) |
| Memory (RAM) | Total Capacity (GB), Used (GB), Available (GB), Usage |
| Storage | Total Capacity (GB), Used (GB), Available (GB), Usage |
| Network | IPv4 Address, MAC Address, Download/Upload Speed (MB/s), ICMP Latency (ms) |
| Processes | Live process list with Process ID (PID) |

---

## Technical Architecture

| Layer | Technology |
|-------|------------|
| Language | C++17 |
| GUI Framework | Qt 6 (Core, Gui, Widgets, Network modules) |
| Build System | CMake 3.16+ |
| Platform API | Windows API, IP Helper API, WMI |
| Performance | Lightweight event-driven updates |
| Deployment | Single portable executable |

---

## System Requirements

| Requirement | Minimum |
|-------------|---------|
| Operating System | Windows 10 / 11 (64-bit) |
| Processor | Any x86_64 architecture |
| Memory | 256 MB RAM |
| Storage | 15 MB free space |
| Dependencies | None (static linking) |

---

## Features in Detail

### CPU Monitoring
- Real-time utilization percentage
- Current operating frequency
- Thermal reading (when available from hardware sensors)

### GPU Monitoring
- Utilization tracking via Windows Performance API
- Core clock frequency reading
- Temperature monitoring for compatible GPUs (NVIDIA, AMD, Intel)

### Memory and Storage
- Accurate capacity detection
- Real-time used and available calculation
- Usage percentage with visual progress indicators

### Network Analysis
- Local IPv4 address detection with automatic interface selection
- MAC address retrieval for active adapters
- Download and upload speed calculation via byte differential monitoring
- ICMP-based latency measurement

### Process Management
- Live enumeration of all running processes via Windows Toolhelp API
- Process ID (PID) display for each entry
- Clean scrollable list interface

### User Interface
- Dark theme optimized for extended monitoring sessions
- Automatic refresh every 2 seconds
- Manual refresh button for on-demand updates
- Integrated network latency test
- Resizable layout with splitter support

---

## Quality Assurance

HWTracker has undergone comprehensive testing to ensure reliability and performance.

| Test Category | Status | Details |
|---------------|--------|---------|
| Functional Testing | ✅ Passed | All monitoring modules verified |
| Performance Testing | ✅ Passed | CPU usage under 3%, memory footprint below 50MB |
| Compatibility Testing | ✅ Passed | Windows 10, Windows 11 (64-bit) |
| Latency Testing | ✅ Passed | ICMP responses within expected range |
| Memory Leak Testing | ✅ Passed | No leaks detected over extended runs (8+ hours) |
| Edge Case Testing | ✅ Passed | Handles missing sensors, disconnected networks gracefully |

**Build Configuration:**
- Debug symbols removed in release builds
- Optimized with O2 flag for production use
- Static linking for zero dependencies

---

## Installation

### Option 1: Pre-built Binary

1. Download the latest `HWTracker.exe` from [Releases](https://github.com/SyKaya/HWTracker/releases)
2. Run directly — no installation required

### Option 2: Build from Source

```bash
git clone https://github.com/SyKaya/HWTracker.git
cd HWTracker
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2019_64"
cmake --build . --config Release
./Release/HWTracker.exe
