# Spring–Mass System Simulation (Raylib)

A simple 2D physics simulation of a horizontal spring–mass system built using **C** and **Raylib**. The program visualizes a block attached to a spring, oscillating with Hooke’s law and linear friction.

---

## 📷 Preview

The simulation displays:

- A floor line
- A red square mass
- A zig-zag spring connected to the mass
- Real‑time motion with damping

---

## ⚙️ Physics Model

The system follows classical mechanics:

- **Hooke’s Law:**
  ( F*{spring} = -k(x - x*{rest}) )

- **Friction (linear damping):**
  ( F\_{friction} = -c \cdot sign(v) )

- **Acceleration:**

```
a = (-K * (x_mass - X_REST)) + friction
```

- **Velocity update:**

```
v += a * dt
```

- **Position update:**

```
x += v * dt
```

Where:

- `K` = spring constant
- `FRICTION` = damping coefficient
- `dt` = frame time

---

## 🧮 Features

- Real‑time physics simulation
- Variable time-step using `GetFrameTime()`
- Spring rendered using multiple line segments
- Window resizing support
- 240 FPS target

---

## 🛠️ Requirements

- C compiler (GCC / Clang / MSVC)
- Raylib installed

### Install Raylib (Linux example)

```bash
sudo apt install libraylib-dev
```

Or from source: [https://www.raylib.com](https://www.raylib.com)

---

## ▶️ How to Build & Run

### Linux / WSL

```bash
gcc main.c -o spring -lraylib -lm -lpthread -ldl -lrt -lX11
./spring
```

### Windows (MinGW)

```bash
gcc main.c -o spring.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

---

## 🔧 Key Constants

| Constant              | Description      | Default |
| --------------------- | ---------------- | ------- |
| `K`                   | Spring stiffness | 10      |
| `FRICTION`            | Damping force    | 10      |
| `FPS`                 | Target FPS       | 240     |
| `NUM_SPRING_ELEMENTS` | Spring segments  | 16      |
| `SPRING_ELEM_LENGTH`  | Segment length   | 60      |
| `MASS_WIDTH`          | Block size       | 100     |

---

## 🧠 Code Structure

| Function       | Purpose                  |
| -------------- | ------------------------ |
| `springDraw()` | Draws zig-zag spring     |
| `massDraw()`   | Draws mass block         |
| `floorDraw()`  | Draws ground line        |
| `main()`       | Physics loop & rendering |

---

## 🚀 Possible Improvements

- Use velocity-proportional damping instead of constant friction
- Add vertical motion (2D spring)
- User controls for spring constant & mass
- Energy graphs (kinetic + potential)
- Pause / reset functionality
- Multiple masses

---

## 🧪 Known Limitations

- Friction is direction-based, not proportional to velocity
- No mass parameter (implicitly 1)
- No collision handling
- Spring length not physically constrained

---

## 📜 License

Free to use for educational and personal projects.

---

## ✍️ Author

Kaustav Bhalla

---
