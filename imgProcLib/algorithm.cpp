#include"pch.h"
#include"Constant.h"
#include"algorithm.hpp"
#define _CRT_SECURE_NO_WARNINGS

inline long double caculateAveragePixels(std::vector<std::vector<unsigned char>>data) {
	long double result = 0.0f;
	//�������̂��߂ɎQ�Ɠn����
	for (auto &x : data) {
		for (auto &y : x) {
			result += static_cast<double>(y);
		}
	}
	return result;
}

int forceRangeAdjust(int n, int index) {
	if (n < 0) {
		return 0;
	}
	else if (n <= index) {
		//�����Q�Ƃł���ő�l
		return n - 1;
	}
	else {
		return index;
	}
}
int checkMemoryRange(int original_size, int index) {
	//�C���f�b�N�X���������ꍇ�͍����l��Ԃ�
	if (index < original_size) {
		return 0;
	}
	else {
		return index - original_size - 1;
	}
}
/*
bands������������value���ǂ��ɑ����Ă��邩���v�Z����
*/
//�Ƃ肠�������u
int quantizeNum(int bands, int n, int value) {

	return 0;
}

inline std::vector<std::vector<long double>> affineMatrix(long double angle, long double mag) {
	std::vector<std::vector<long double>> array(2, std::vector<long double>(2, 0.0));
	array[0][0] = mag * std::cos(angle);
	array[0][1] = mag * (0 - std::sin(angle));
	array[1][0] = mag * std::sin(angle);
	array[1][1] = mag * std::cos(angle);
	return array;
}