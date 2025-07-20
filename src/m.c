#include <xmmintrin.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

// Conslusion: This gives u the same performance since the compiler already simds the loop
#define SIZE (2048 * 1000) * 10

void vec_add_sse_simd(float *a, float *b, float *result)
{
	printf("[INFO]: Using simd to process %i of data\n", SIZE);
    for (int i = 0; i < SIZE; i += 4)
        _mm_storeu_ps(&result[i], _mm_add_ps(_mm_load_ps(&a[i]), _mm_load_ps(&b[i])));
}

void vec_add_sse(float *a, float *b, float *result)
{
	printf("[INFO]: Using normal calc to process %i of data\n", SIZE);
    for (int i = 0; i < SIZE; i++)
        result[i] = a[i] + b[i];
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int main()
{
    float a[SIZE];
    float b[SIZE];
    float res[SIZE];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() / RAND_MAX;
        b[i] = rand() / RAND_MAX;
    }
    long s = get_timestamp();
	vec_add_sse_simd(a, b, res);
    printf("Took %ldms: simd\n", (get_timestamp() - s));


    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() / RAND_MAX;
        b[i] = rand() / RAND_MAX;
    }
	s = get_timestamp();
	vec_add_sse(a, b, res);
    printf("Took %ldms: No simd\n", (get_timestamp() - s));
    return (0);
}
