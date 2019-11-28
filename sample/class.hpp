#pragma once

class mImage {
public:
	mImage() {}
public:
	///* 関数のプロトタイプ宣言 */
	void load_image_data(); /* 画像読み込み用関数 */
	void save_image_data(); /* 画像書き込み用関数 */
	void copy_image();
	void add_image();

private:
	/* 大域変数の宣言 */
	/* 画像用配列１，画像用配列２ */
	std::array<std::array<unsigned char, MAX_IMAGESIZE/2>, MAX_IMAGESIZE/2>image1;
	std::array<std::array<unsigned char, MAX_IMAGESIZE / 2>, MAX_IMAGESIZE / 2>image2;

	int x_size1=0, y_size1=0, /* image1 の横画素数，縦画素数 */
		x_size2=0, y_size2=0; /* image2 の横画素数，縦画素数 */
};