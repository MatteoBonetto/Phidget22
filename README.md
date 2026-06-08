# Phidget22

## 1. Create a Build Directory

Navigate into the root of the repository and apply this command to go into the building file directory:

```bash
cd build/install
```

## 2.
C compiler and build tools

These are usually installed by a package called `build-essential`

`libusb 1.0`

This is generally already installed. The libusb dev files may need to
be installed - this is usually a package called `libusb-1.0-0-dev`.

```bash
sudo apt install libusb-1.0-0-dev
```

Avahi client library

## 3. Run the `configure` Script with Local `--prefix`

Run the `configure` script located in the parent folder and specify the current path as installation prefix:

```bash
../../configure --prefix=$(pwd)/..
```

> 🔧 This tells the build system to install everything (headers, libraries, etc.) **inside the `build/install` folder**.


## 4. Install Locally

```bash
make install -j$(nproc)
```

This will install:
- Libraries in `build/install/lib/`
- Headers in `build/install/include/`

---

## 5. Install Globally
```bash
../../configure --prefix=/usr/local && make && sudo make install -j$(nproc)
```

## ✅ Done!
