#include <immintrin.h>

#include <chrono>
#include <iostream>
#include <vector>

constexpr size_t N = 1 << 28; 
void add_plain(const float* a, const float* b, float* result, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] + b[i];
    }
}

void add_avx2(const float* a, const float* b, float* result, size_t n) {
    size_t i = 0;
    size_t simd_end = n - (n % 8);
    for (; i < simd_end; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(result + i, vr);
    }
    for (; i < n; ++i) {
        result[i] = a[i] + b[i];
    }
}

void mul_plain(const float* a, const float* b, float* result, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        result[i] = a[i] * b[i];
    }
}

void mul_avx2(const float* a, const float* b, float* result, size_t n) {
    size_t i = 0;
    size_t simd_end = n - (n % 8);
    for (; i < simd_end; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 vr = _mm256_mul_ps(va, vb);
        _mm256_storeu_ps(result + i, vr);
    }
    for (; i < n; ++i) {
        result[i] = a[i] * b[i];
    }
}

float dot_plain(const float* a, const float* b, size_t n) {
    float sum = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

float dot_avx2(const float* a, const float* b, size_t n) {
    __m256 vsum = _mm256_setzero_ps();
    size_t i = 0;
    size_t simd_end = n - (n % 8);
    for (; i < simd_end; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 vmul = _mm256_mul_ps(va, vb);
        vsum = _mm256_add_ps(vsum, vmul);
    }
    float sum[8];
    _mm256_storeu_ps(sum, vsum);
    float total = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
    for (; i < n; ++i) {
        total += a[i] * b[i];
    }
    return total;
}

int main() {
    std::vector<float> a(N, 1.0f), b(N, 2.0f), result(N);
    constexpr int num_trials = 30;

    // Addition
    double add_plain_total = 0.0, add_avx2_total = 0.0;
    for (int t = 0; t < num_trials; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        add_plain(a.data(), b.data(), result.data(), N);
        auto end = std::chrono::high_resolution_clock::now();
        add_plain_total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "Addition (Plain C++):      " << add_plain_total / num_trials << " ms (avg over " << num_trials << " runs)\n";

    for (int t = 0; t < num_trials; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        add_avx2(a.data(), b.data(), result.data(), N);
        auto end = std::chrono::high_resolution_clock::now();
        add_avx2_total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "Addition (AVX2):           " << add_avx2_total / num_trials << " ms (avg over " << num_trials << " runs)\n";

    // Multiplication
    double mul_plain_total = 0.0, mul_avx2_total = 0.0;
    for (int t = 0; t < num_trials; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        mul_plain(a.data(), b.data(), result.data(), N);
        auto end = std::chrono::high_resolution_clock::now();
        mul_plain_total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "Multiplication (Plain C++): " << mul_plain_total / num_trials << " ms (avg over " << num_trials << " runs)\n";

    for (int t = 0; t < num_trials; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        mul_avx2(a.data(), b.data(), result.data(), N);
        auto end = std::chrono::high_resolution_clock::now();
        mul_avx2_total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "Multiplication (AVX2):      " << mul_avx2_total / num_trials << " ms (avg over " << num_trials << " runs)\n";

    // Dot product
    double dot_plain_total = 0.0, dot_avx2_total = 0.0;
    float dot1 = 0.0f, dot2 = 0.0f;
    for (int t = 0; t < num_trials; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        dot1 = dot_plain(a.data(), b.data(), N);
        auto end = std::chrono::high_resolution_clock::now();
        dot_plain_total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "Dot Product (Plain C++):    " << dot_plain_total / num_trials << " ms (avg over " << num_trials << " runs)\n";
    std::cout << "Dot Product value (Plain C++): " << dot1 << std::endl;

    for (int t = 0; t < num_trials; ++t) {
        auto start = std::chrono::high_resolution_clock::now();
        dot2 = dot_avx2(a.data(), b.data(), N);
        auto end = std::chrono::high_resolution_clock::now();
        dot_avx2_total += std::chrono::duration<double, std::milli>(end - start).count();
    }
    std::cout << "Dot Product (AVX2):         " << dot_avx2_total / num_trials << " ms (avg over " << num_trials << " runs)\n";
    std::cout << "Dot Product value (AVX2): " << dot2 << std::endl;

    // Prevent optimization
    std::cout << "Result[0]: " << result[0] << std::endl;
    std::cout << "Dot Product: " << dot2 << std::endl;
    return 0;
}
