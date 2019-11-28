#pragma once

//画像の変換処理
class mLogic {
public:
	mLogic() {}
	///* 関数のプロトタイプ宣言 */
	void save_image_data(Image& instance); /* 画像書き込み用関数 */
	void save_image_data(Image& instance, std::string filename);
	Image copy_image(Image instance);
	Image add_image(Image instance);
	//画像の反転
	Image inverseImage(Image instance);
	//画像サイズの変更
	//Image resizeImage(Image instance);
	//モザイク
	Image convertResolution(Image& instance, int magnificationValue);
	Image resizeImage(Image& instance, double mag);
	Image linearResize(Image& instance, double mag);
	Image neighborMethod(Image& instance, double mag);
	//階調数変換（デフォルト）
	Image convertTone(Image& instance) { return convertTone(instance, 4); }
	Image convertTone(Image& instance, int n);
	//線形ヒストグラム
	Image convertLinearHist(Image& instance);
	Image convertNonLinearHist(Image& instance);
	Image transHistgram(Image& instance);
	Image normalizeFilter(Image&);
	Image median_filter(Image& instance);
	//アフィン変換
	//Image affineTransform(Image & instance);
	//Image affineTransform(Image & instance, long double angle);
	//Image affineTransform(Image & instance, long float mag);
	//Image affineTransform(Image & instance, long double angle, long double mag);

	//微分フィルタ
	Image affectSobelFilter(Image& instance);
	Image affectLaplacianFilter(Image& instance);
	Image affectRadicalizeFilter(Image& image);

	//二値化
	Image threshold(Image& instance, int thresh);
	Image adaptiveThreshold(Image& instance, int blockSize, int thresh);

	Image expansion(Image& instance);
	Image contraction(Image& instance);


};


