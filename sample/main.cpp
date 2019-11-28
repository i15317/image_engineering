// sample.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include"ImgProcLib.h"

int main()
{
	using namespace ImgProcLib;

	Image readImage;
	readImage.load_image_data("lecture1/girl.pgm");


	auto thresholdImage = threshold(readImage, 80);
	auto adaptiveThresholdImage = adaptiveThreshold(readImage, 3, 0);
	auto expansionImage = expansion(thresholdImage);
	auto contractionImage = contraction(thresholdImage);

	save_image_data(thresholdImage, "threshold.pgm");
	save_image_data(adaptiveThresholdImage, "adaptive.pgm");
	save_image_data(expansionImage, "expansion.pgm");
	save_image_data(contractionImage,"contraction.pgm");

	return 0;
}