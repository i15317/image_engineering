#pragma once

//画像の変換処理

namespace ImgProcLib {
	//前方宣言
	class Image;


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
	Image convertTone(Image& instance, int n);
	Image convertTone(Image& instance);

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

}
