# Raylib Projectile Motion Simulation

A lightweight C++ simulation demonstrating basic kinematic physics using the [Raylib](https://www.raylib.com/) library. This project visualizes a particle following a projectile trajectory under the influence of gravity.

## 🚀 Features

* **Custom Particle Class:** Encapsulates position, velocity, and acceleration vectors.
* **Vector Arithmetic:** Uses `raylib.h`'s `Vector2` struct for 2D movement.
* **Euler Integration:** Updates physics state frame-by-frame based on a fixed delta time (`dt`).
* **High Refresh Rate:** Optimized for 180 FPS rendering.

## 🧮 How It Works

The simulation uses standard kinematic equations implemented via Euler integration in the `update()` loop:

1.  **Velocity Update:** $v_{new} = v_{old} + (a \cdot \Delta t)$
2.  **Position Update:** $p_{new} = p_{old} + (v_{new} \cdot \Delta t)$

* **Gravity:** Constant downward acceleration ($9.81 m/s^2$).
* **Delta Time (`dt`):** Set to the frame time for the simulation step.

## 🛠️ Prerequisites

* **C++ Compiler:** (GCC/G++ recommended)
* **Raylib Library:** Must be installed on your system.

## 💻 Build & Run

A convenience script is provided to compile and link the necessary Raylib dependencies automatically.

1.  **Make the script executable:**
    ```bash
    chmod +x run.sh
    ```

2.  **Run the simulation:**
    ```bash
    ./run.sh
    ```

## ⚙️ Configuration

You can tweak the simulation constants in `main.cpp`:

* **`dt`**: Controls the time step (simulation speed).
* **`acceleration`**: Modify the `Particle` constructor to change gravity or add wind.
* **`velocity`**: Change the starting launch speed and angle.