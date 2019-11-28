#pragma once
#include"pch.h"

namespace ImgProcLib {
	//前方宣言
	class Image;

	///* 関数のプロトタイプ宣言 */
	void save_image_data(Image& instance); /* 画像書き込み用関数 */
	void save_image_data(Image& instance, std::string filename);
	Image imageRead(std::string filename);
}