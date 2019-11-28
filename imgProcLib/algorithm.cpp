#include"pch.h"
#include"Constant.h"
#include"algorithm.hpp"
#define _CRT_SECURE_NO_WARNINGS

inline long double caculateAveragePixels(std::vector<std::vector<unsigned char>>data) {
	long double result = 0.0f;
	//高速化のために参照渡しで
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
		//こいつ参照できる最大値
		return n - 1;
	}
	else {
		return index;
	}
}
int checkMemoryRange(int original_size, int index) {
	//インデックスが超えた場合は差分値を返す
	if (index < original_size) {
		return 0;
	}
	else {
		return index - original_size - 1;
	}
}
/*
bandsをｎ等分してvalueがどこに属しているかを計算する
*/
//とりあえず放置
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