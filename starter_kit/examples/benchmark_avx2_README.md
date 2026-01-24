# AVX2 Benchmark Example

This example demonstrates the performance difference between plain C++ and AVX2 intrinsics for several vector operations.

## File
- benchmark_avx2.cpp

## How It Works


Performs a comprehensive set of operations on very large float arrays (e.g., 128M elements or more) and repeats each operation many times to simulate a huge computational workload:

1. Vector addition (a + b)
2. Vector multiplication (a * b)
3. Dot product (sum(a[i] * b[i]))
4. Fused multiply-add (a[i] * b[i] + c[i])
5. Scalar reduction (sum of all elements)

Each operation is implemented twice:
- Plain C++ for-loop
- AVX2 SIMD intrinsics

The benchmark runs each operation for multiple iterations (e.g., 10-100 times) to stress the CPU and memory subsystem, and prints the average execution time for each method and operation.

This setup is designed to highlight the performance difference for massive jobs and real-world workloads.

## Build Instructions

### Using g++ (with AVX2 support)
```
g++ -O2 -mavx2 benchmark_avx2.cpp -o benchmark_avx2
```

### Using clang++
```
clang++ -O2 -mavx2 benchmark_avx2.cpp -o benchmark_avx2
```

## Run
```
./benchmark_avx2
```

## Output Example
```

Addition (Plain C++):      1200 ms (avg over 10 runs)
Addition (AVX2):           400 ms (avg over 10 runs)
Multiplication (Plain C++): 1300 ms (avg over 10 runs)
Multiplication (AVX2):      450 ms (avg over 10 runs)
Dot Product (Plain C++):    1100 ms (avg over 10 runs)
Dot Product (AVX2):         350 ms (avg over 10 runs)
Fused Multiply-Add (Plain C++): 1400 ms (avg over 10 runs)
Fused Multiply-Add (AVX2):      500 ms (avg over 10 runs)
Scalar Reduction (Plain C++):   900 ms (avg over 10 runs)
Scalar Reduction (AVX2):        300 ms (avg over 10 runs)
Result[0]: 3
Dot Product: 500000000
```

## Notes
- Requires a CPU with AVX2 support.
- The result value is printed to prevent compiler optimization from removing the computation.
