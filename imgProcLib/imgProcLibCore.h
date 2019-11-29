#pragma once

//画像の変換処理

namespace ImgProcLib {
	//前方宣言
	class Image;

	/*
	Imageクラス内部に取り込みたい機能
	*/

	//画像のコピー Todo: 非推奨だよこいつ
	Image copy_image(Image instance);
	//画像に任意の量を加算する
	Image add_image(Image instance);
	//画像の反転
	Image inverseImage(Image instance);
	//画像のリサイズ
	Image resizeImage(Image& instance, double mag);
	//画像のリサイズ
	Image linearResize(Image& instance, double mag);
	////////////////////////////////////////////////////////////////////////////////////////////////

	//モザイク
	Image convertResolution(Image& instance, int magnificationValue);
	//何だこれ？
	Image neighborMethod(Image& instance, double mag);

	//階調数変換
	Image convertTone(Image& instance, int n);
	//階調数変換（デフォルト）
	Image convertTone(Image& instance);

	//線形ヒストグラム
	Image convertLinearHist(Image& instance);
	//非線形ヒストグラム変換
	Image convertNonLinearHist(Image& instance);
	//何だこれ？
	Image transHistgram(Image& instance);
	//正規化フィルタ
	Image normalizeFilter(Image&);
	Image median_filter(Image& instance);

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
