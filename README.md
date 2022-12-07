# RayTracer

## Abstract

- My personal practice in ray tracer
- Add some new features: multithreading, thread-safe std::ostream class, cmake build, etc
- Preview

![](./bin/image.png)

## Reference

- https://github.com/RayTracing/raytracing.github.io

## Usage

```shell
cmake -D CMAKE_BUILD_TYPE=Release --build build 
cmake -B build
cd bin
# single-threading render
./OneWeekendApplication.exe > image.ppm 
# multithreading render by input number of threads as you wish
./OneWeekendApplication.exe number > image.ppm
```