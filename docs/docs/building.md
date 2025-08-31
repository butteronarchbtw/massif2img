# Building

This project uses CMake (sorry.).

To just build the executable, run

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

to configure the project and

```sh
cmake --build build
```

to build the executable.

## Tests

This project includes tests, which are controlled by the `BUILD_TESTS` CMake option.
To compile them on build configure the project using

```sh
cmake -B build -DBUILD_TESTS=ON
```

