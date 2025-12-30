# miniRT — Minimal Ray Tracer (C + MLX42)

> A compact **ray tracing** engine written in **C** (42-school miniRT project).  
> Renders simple 3D scenes from `.rt` files by casting rays, computing intersections, and shading with diffuse lighting + hard shadows.

---

## ✨ Features

- **Primitives**: Sphere (`sp`), Plane (`pl`), Cylinder (`cy`)
- **Lighting**: Lambertian diffuse shading + **hard shadows**
- **Camera**: Movable camera with orientation vectors + FOV
- **Scene Parsing**: Strict `.rt` parser + validation
- **Memory Safety**: Custom GC-style allocator (`gc_malloc`, `gc_free_all`) to prevent leaks
- **Real-time Loop**: Keyboard hooks for smooth interactions

---

## 📦 Repository layout

```text
.
├── gnl/         # get_next_line
├── includes/    # headers
├── libft/       # libft
├── minilibx/    # MLX42 (vendored)
├── scenes/      # example .rt scenes
├── src/         # renderer, parser, math, hooks, etc.
├── Makefile
└── README.md
````

---

## 🧰 Prerequisites

This project uses **MLX42**, which relies on **GLFW** and **CMake**.

### macOS (Homebrew)

```bash
brew install glfw cmake
```

### Linux (Debian/Ubuntu)

```bash
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev libglfw3 cmake xorg-dev
```

> If you’re on another distro, install the equivalents of **GLFW**, **CMake**, and X11 development packages.

---

## 🛠️ Build

```bash
git clone https://github.com/Neko-Bytes/minirt.git
cd minirt
make
```

Common targets (if present in your Makefile):

```bash
make clean
make fclean
make re
```

---

## ▶️ Run

```bash
./miniRT scenes/example.rt
```

> You can pass any valid `.rt` file path.

---

## ⌨️ Controls

| Key   | Action                  |
| ----- | ----------------------- |
| ↑ / ↓ | Move forward / backward |
| ← / → | Strafe left / right     |
| A / D | Rotate camera (yaw)     |
| ESC   | Exit                    |

---

## 🧾 Scene format (`.rt`)

A scene is a plain text file with one element per line.

### 1) Ambient light (`A`)

```txt
A 0.2 255,255,255
# Ratio   Color(R,G,B)
```

### 2) Camera (`C`)

```txt
C 0,0,0 0,0,1 70
# Position(x,y,z)   Orientation(x,y,z)   FOV
```

### 3) Light (`L`)

```txt
L -10,10,20 0.6 255,255,255
# Position(x,y,z)   Brightness   Color(R,G,B)
```

### 4) Objects

**Sphere**

```txt
sp 0,0,20 10 255,0,0
# Position   Diameter   Color
```

**Plane**

```txt
pl 0,0,0 0,1,0 0,0,255
# Position   Normal     Color
```

**Cylinder**

```txt
cy 50,0,20 0,1,0 14.2 21.4 10,0,255
# Position   Axis       Diameter   Height   Color
```

---

## 🧠 How it works (high level)

For each pixel:

1. **Generate a ray** from the camera through the view plane
2. **Test intersections** against all objects
3. Pick the **closest valid hit** (smallest positive `t`)
4. Compute **diffuse lighting** using `dot(normal, light_dir)`
5. Cast a **shadow ray** toward the light:

   * if blocked → the point is in shadow
   * else → apply lighting normally

---

## 🧮 Math toolkit

The renderer relies heavily on linear algebra (see `src/`):

* Vector ops: add/sub, dot, cross, normalize
* Camera basis vectors + transformations

---

## 🧯 Troubleshooting

* **GLFW / CMake missing** → install prerequisites (see above)
* **Linux build errors about X11** → ensure `xorg-dev` (or equivalent) is installed
* **Black screen** → validate your `.rt` file (camera orientation, light ratio, colors)

---

## 👥 Authors

* **Neko-Bytes** and **unicorn453**

---

