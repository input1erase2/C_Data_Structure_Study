#include <stdio.h>

// 분할정복을 이용하면 재귀를 사용하지 않고 
// n번째 피보나치를 O(2^n)에서 O(log_2(N))에 구할 수 있다.

typedef unsigned long long ull;

typedef struct _Mat2x2 {
	ull data[2][2];	
} Mat2x2;

Mat2x2 mat2x2Mult(Mat2x2 lhs, Mat2x2 rhs) {
	Mat2x2 ret;
	ret.data[0][0] = lhs.data[0][0] * rhs.data[0][0] + lhs.data[0][0] * rhs.data[1][0];
	ret.data[0][1] = lhs.data[0][0] * rhs.data[1][0] + lhs.data[0][0] * rhs.data[1][1];
	ret.data[1][0] = lhs.data[1][0] * rhs.data[0][0] + lhs.data[1][1] * rhs.data[1][0];
	ret.data[1][1] = lhs.data[1][0] * rhs.data[1][0] + lhs.data[1][1] * rhs.data[1][1];
	return ret;
}

Mat2x2 mat2x2Pow(Mat2x2 mat, int n) {
	if (n > 1) {
		mat = mat2x2Pow(mat, n / 2);	// n제곱 = (n/2)제곱 * (n/2)제곱
		mat = mat2x2Mult(mat, mat);		// (n/2)제곱 * (n/2)제곱
		if (n & 1) {					// n이 홀수일 때
			Mat2x2 temp;
			temp.data[0][0] = 1;
			temp.data[0][1] = 1;
			temp.data[1][0] = 1;
			temp.data[1][1] = 0;
			mat = mat2x2Mult(mat, temp);// n/2를 할 때 잃은 하나를 마저 곱해준다.
		}
	}
	return mat;
}

ull getFibo(int n) {
	Mat2x2 temp;
	temp.data[0][0] = 1;
	temp.data[0][1] = 1;
	temp.data[1][0] = 1;
	temp.data[1][1] = 0;
	
	temp = mat2x2Pow(temp, n);
	
	return temp.data[0][1];
}

int main() {
	int n = 46;
	ull result = getFibo(n);
	
	printf("Fibonaccui(%d) = %lld\n\n", n, result);
	
	return 0;
}