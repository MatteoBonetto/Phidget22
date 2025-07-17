# Phidget22

## 1. Create a Build Directory

Navigate into the root of the repository and apply this command to go into the building file directory:

```bash
cd build/install
```

## 2. Run the `configure` Script with Local `--prefix`

Run the `configure` script located in the parent folder and specify the current path as installation prefix:

```bash
../../configure --prefix=$(pwd)
```

> 🔧 This tells the build system to install everything (headers, libraries, etc.) **inside the `build/install` folder**.

## 3. Compile the Library

```bash
make -j$(nproc)
```

> This builds the project using all available CPU cores.

## 4. Install Locally

```bash
make install
```

This will install:
- Libraries in `build/install/lib/`
- Headers in `build/install/include/`

---

## ✅ Done!
