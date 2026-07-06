# C++ Ping Pong Game (SFML 3)

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Compiler](https://img.shields.io/badge/Compiler-MSVC%202022-brightgreen.svg)](https://visualstudio.microsoft.com/)
[![SFML Version](https://img.shields.io/badge/SFML-3.0-green.svg)](https://www.sfml-dev.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A high-performance, lightweight, and fully completed implementation of the classic Pong game for two players. The project is built from scratch using **C++17**, **Microsoft Visual Studio 2022**, and the next-generation multimedia library **SFML 3**.

The core technical highlight of this project is the complete avoidance of standard high-level shapes like `sf::RectangleShape` and `sf::CircleShape`. Instead, the rendering of paddles and the ball is implemented at a low level using custom **`sf::VertexArray`** structures. This minimizes draw calls and optimizes the graphics pipeline for maximum efficiency.

---

## 🚀 Key Features & Architecture

The project is engineered following clean Object-Oriented Programming (OOP) principles, ensuring that each component handles a strict area of responsibility:

1. **`Config.hpp`** — The single source of truth for game configuration. It contains global inline constants (`PLAYER_WIDTH`, `PLAYER_HEIGHT`, `PLAYER_SPEED`, `BALL_R`), round outcome states (`Goal`), and required SFML linker workarounds for MSVC.
2. **`Player.hpp`** — The paddle controller class.
   * Implemented as an inline class inheriting from `sf::Drawable`.
   * Paddle geometry is dynamically generated using the `sf::PrimitiveType::TriangleStrip` primitive with a Z-shaped 4-vertex layout.
   * Input handling relies on physical scancodes (`sf::Keyboard::Scancode`), completely avoiding keyboard layout conflict issues.
3. **`Ball.hpp`** — The dynamic game ball class.
   * Generates a perfectly smooth circle consisting of **30 segments** via sine and cosine trigonometric functions using the `sf::PrimitiveType::TriangleFan` primitive layout.
   * Contains encapsulated collision math, automated anti-clipping algorithms (to prevent the ball from getting stuck inside walls or paddles), and progressive velocity acceleration (`* 1.05`) upon each successful paddle bounce.
4. **`main.cpp`** — The main engine controller. It orchestrates the render window, frame synchronization (VSync), system events, match score keeping, and text UI rendering.

---

## 🕹️ Controls

The game is designed for local versus multiplayer sharing a single keyboard:

* **Left Player (Player 1):**
  * `W` — Move Up
  * `S` — Move Down
* **Right Player (Player 2):**
  * `Up Arrow` — Move Up
  * `Down Arrow` — Move Down

---

## 🛠️ Physics Engine Insights

* **Delta Time Synchronization:** All physical movements of both the ball and the paddles are scaled by the frame time delta `dt` (`clock.restart().asSeconds()`). This guarantees that the gameplay speed remains perfectly identical regardless of the monitor's refresh rate.
* **Accurate LERP-Based Velocity Randomization:** The `resetBall` function avoids heavy random distribution classes. Instead, it computes random launch angles using a custom linear interpolation (LERP) of the standard `rand()` generator mapped precisely into boundaries of $[22.4; 40.0]$ on the X-axis and $[0.0; 22.4]$ on the Y-axis. This preserves predictable bounce bounds while keeping launches unpredictable.

---

## 📦 Compilation & Setup

### Prerequisites:
* **Microsoft Visual Studio 2022** with the "Desktop development with C++" workload (configured for the **C++17** standard).
* Installed and configured **SFML 3** library development files linked to your MSVC project settings.

⚠️ **Note on Assets:** The code points directly to a default Windows system font path: `C:/Windows/Fonts/Arial.ttf`. Since the project is built via Visual Studio on Windows, the asset will load out of the box.

---

## 📄 License

This project is licensed under the **MIT License**.

You are free to use, copy, modify, merge, publish, or distribute this code for personal, educational, or commercial purposes. The only condition is that the original copyright and permission notice must be included in all copies or substantial portions of the software.

*Note: The SFML library itself is distributed under its own permissive zlib/libpng license.*
