# SimpleCompiler

This project uses `cmake` and requires version `3.7`

## macOS

### Install cmake

```
$ brew install cmake
```

### Create Xcode project with cmake

```
$ mkdir Xcode
$ cd Xcode
$ cmake .. -GXcode
```

### Build & Run

Open the Xcode project and run the `SimpleCompiler` Scheme

## Linux

### Install cmake

```
$ apt-get purge cmake
$ wget https://cmake.org/files/v3.8/cmake-3.8.0-Linux-x86_64.tar.gz
$ tar xzf cmake-3.8.0-Linux-x86_64.tar.gz
$ cd cmake-3.8.0-Linux-x86_64
$ sudo cp -r bin /usr/local/
$ sudo cp -r doc /usr/local/share/
$ sudo cp -r man /usr/local/share/
$ sudo cp -r share /usr/local/
$ cd ..
$ rm -Rf cmake-3.8.0-Linux-x86_64
$ rm cmake-3.8.0-Linux-x86_64.tar.gz
$ cmake --version
```

### Create Makefile with cmake

```
$ mkdir Make
$ cd Make
$ cmake ..
```

### Build & Run

```
$ make
$ SimpleCompiler <filename>
$ SimpleCompiler test
```

## Windows

TODO: Need to figure out how install goes on Windows

### Install cmake

Windows installer can be found at https://cmake.org/download/

### Create Visual Studio Project project with cmake

```
?
```

### Build & Run

Open Visual Studio Project and run 