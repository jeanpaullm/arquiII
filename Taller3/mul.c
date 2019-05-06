// SSE headers
#include <emmintrin.h> //v3
#include <smmintrin.h> //v4
#include <stdio.h>

int main(){

    __m128 a1 = _mm_setr_ps(1.0,   2.0,  3.0,  4.0);
    __m128 a2 = _mm_setr_ps(5.0,   6.0,  7.0,  8.0);
    __m128 a3 = _mm_setr_ps(9.0,  10.0, 11.0, 12.0);
    __m128 a4 = _mm_setr_ps(13.0, 14.0, 15.0, 16.0);

    __m128 b1 = _mm_setr_ps(1.0, 5.0,  9.0, 13.0);
    __m128 b2 = _mm_setr_ps(2.0, 6.0, 10.0, 14.0);
    __m128 b3 = _mm_setr_ps(3.0, 7.0, 11.0, 15.0);
    __m128 b4 = _mm_setr_ps(4.0, 8.0, 12.0, 16.0);

    __m128 tmp11 = _mm_dp_ps(a1, b1, 0xff);
    __m128 tmp12 = _mm_dp_ps(a1, b2, 0xff);
    __m128 tmp13 = _mm_dp_ps(a1, b3, 0xff);
    __m128 tmp14 = _mm_dp_ps(a1, b4, 0xff);

    __m128 tmp21 = _mm_dp_ps(a2, b1, 0xff);
    __m128 tmp22 = _mm_dp_ps(a2, b2, 0xff);
    __m128 tmp23 = _mm_dp_ps(a2, b3, 0xff);
    __m128 tmp24 = _mm_dp_ps(a2, b4, 0xff);

    __m128 tmp31 = _mm_dp_ps(a3, b1, 0xff);
    __m128 tmp32 = _mm_dp_ps(a3, b2, 0xff);
    __m128 tmp33 = _mm_dp_ps(a3, b3, 0xff);
    __m128 tmp34 = _mm_dp_ps(a3, b4, 0xff);

    __m128 tmp41 = _mm_dp_ps(a4, b1, 0xff);
    __m128 tmp42 = _mm_dp_ps(a4, b2, 0xff);
    __m128 tmp43 = _mm_dp_ps(a4, b3, 0xff);
    __m128 tmp44 = _mm_dp_ps(a4, b4, 0xff);

    __m128 c1 = _mm_setr_ps(_mm_cvtss_f32(tmp11), _mm_cvtss_f32(tmp12), _mm_cvtss_f32(tmp13), _mm_cvtss_f32(tmp14));
    __m128 c2 = _mm_setr_ps(_mm_cvtss_f32(tmp21), _mm_cvtss_f32(tmp22), _mm_cvtss_f32(tmp23), _mm_cvtss_f32(tmp24));
    __m128 c3 = _mm_setr_ps(_mm_cvtss_f32(tmp31), _mm_cvtss_f32(tmp32), _mm_cvtss_f32(tmp33), _mm_cvtss_f32(tmp34));
    __m128 c4 = _mm_setr_ps(_mm_cvtss_f32(tmp41), _mm_cvtss_f32(tmp42), _mm_cvtss_f32(tmp43), _mm_cvtss_f32(tmp44)); 


    //Vector Printing
    printf("Matrix A\n");

    printf("%f, %f, %f, %f\n", a1[0], a1[1], a1[2], a1[3]);
    printf("%f, %f, %f, %f\n", a2[0], a2[1], a2[2], a2[3]);
    printf("%f, %f, %f, %f\n", a3[0], a3[1], a3[2], a3[3]);
    printf("%f, %f, %f, %f\n", a4[0], a4[1], a4[2], a4[3]);

    printf("\nMatrix B\n");

    printf("%f, %f, %f, %f\n", b1[0], b2[0], b3[0], b4[0]);
    printf("%f, %f, %f, %f\n", b1[1], b2[1], b3[1], b4[1]);
    printf("%f, %f, %f, %f\n", b1[2], b2[2], b3[2], b4[2]);
    printf("%f, %f, %f, %f\n", b1[3], b2[3], b3[3], b4[3]);

    printf("\nMatrix AxB\n");

    printf("%f, %f, %f, %f\n", c1[0], c1[1], c1[2], c1[3]);
    printf("%f, %f, %f, %f\n", c2[0], c2[1], c2[2], c2[3]);
    printf("%f, %f, %f, %f\n", c3[0], c3[1], c3[2], c3[3]);
    printf("%f, %f, %f, %f\n", c4[0], c4[1], c4[2], c4[3]);


    return 1;

}