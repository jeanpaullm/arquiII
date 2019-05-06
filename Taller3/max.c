// SSE headers
#include <emmintrin.h> //v3
#include <smmintrin.h> //v4
#include <stdio.h>


int main(){

    int a1, a2, a3, a4, a5, a6, a7, a8;

    printf("Please input 8 integers:\n");
    scanf("%d", &a1);
    scanf("%d", &a2);
    scanf("%d", &a3);
    scanf("%d", &a4);
    scanf("%d", &a5);
    scanf("%d", &a6);
    scanf("%d", &a7);
    scanf("%d", &a8);
    
    __m128i v1 = _mm_setr_epi16(a1,a2,a3,a4,a5,a6,a7,a8);
    
    int b1, b2, b3, b4, b5, b6, b7, b8;

    printf("Please input 8 integers:\n");
    scanf("%d", &b1);
    scanf("%d", &b2);
    scanf("%d", &b3);
    scanf("%d", &b4);
    scanf("%d", &b5);
    scanf("%d", &b6);
    scanf("%d", &b7);
    scanf("%d", &b8);
    
    __m128i v2 = _mm_setr_epi16(b1,b2,b3,b4,b5,b6,b7,b8);

    __m128i v3 = _mm_max_epi16(v1, v2);

    //Vector Printing

    printf("first vector \n");
    printf("%d, %d, %d, %d, %d, %d, %d, %d\n", _mm_extract_epi16(v1,0), _mm_extract_epi16(v1,1), _mm_extract_epi16(v1,2), _mm_extract_epi16(v1,3), _mm_extract_epi16(v1,4), _mm_extract_epi16(v1,5), _mm_extract_epi16(v1,6), _mm_extract_epi16(v1,7));
    printf("second vector \n");
    printf("%d, %d, %d, %d, %d, %d, %d, %d\n", _mm_extract_epi16(v2,0), _mm_extract_epi16(v2,1), _mm_extract_epi16(v2,2), _mm_extract_epi16(v2,3), _mm_extract_epi16(v2,4), _mm_extract_epi16(v2,5), _mm_extract_epi16(v2,6), _mm_extract_epi16(v2,7));
    printf("bigger column value \n");
    printf("%d, %d, %d, %d, %d, %d, %d, %d\n", _mm_extract_epi16(v3,0), _mm_extract_epi16(v3,1), _mm_extract_epi16(v3,2), _mm_extract_epi16(v3,3), _mm_extract_epi16(v3,4), _mm_extract_epi16(v3,5), _mm_extract_epi16(v3,6), _mm_extract_epi16(v3,7));

    return 1;
}