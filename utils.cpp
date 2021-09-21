#include <Windows.h>
typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

#define global_variable static
#define internal static

inline int
clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

double PCFreq = 0.0;
__int64 CounterStart = 0;
DWORD_PTR old_mask;

void StartCounter() {
    LARGE_INTEGER li2;
    QueryPerformanceFrequency(&li2);
        

    PCFreq = double(li2.QuadPart)*1000;

    QueryPerformanceCounter(&li2);
    CounterStart = li2.QuadPart;
}

double GetCounter() {
    LARGE_INTEGER li2;
    QueryPerformanceCounter(&li2);
    return double(li2.QuadPart - CounterStart) / PCFreq;
}
