#include<time.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
 
float slow_inverse_square(float x) {
    float result = (1 / sqrt(x));
    return result;
}

float fast_inverse_square(float x) {
    long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = x * 0.5F;
	y  = x;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

int main() {
    float error, slow, fast;
    char* txt = calloc(9, sizeof(char));
    // printf("%f\n", 1.5F);

    for(int i = 1; i < 30; i++) {
        sprintf(txt, "9e+%d", i);
        float input = atof(txt);
         
        slow = slow_inverse_square(input);
        fast = fast_inverse_square(input);
        error = (fabs(slow-fast) / slow) * 100;
        printf("%s \t%f\n", txt, input);    
        printf("fast:\t%.16f\n", fast);
        printf("slow:\t%.16f\n", slow);
        printf("error:\t%.2f%%\n\n", error);
    }

    return 0;    
}
    