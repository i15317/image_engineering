#include"pch.h"
#include"Image.h"
#include"Constant.h"
#include"algorithm.hpp"
#include"imgProcLibCore.h"
#include<omp.h>
////
////
#define _CRT_SECURE_NO_WARNINGS

////
////

namespace ImgProcLib {

	Image add_image(Image mInstance) {
		//結果を格納するインスタンス
		Image img(mInstance.getColsSize(), mInstance.getRowsSize());
		int x, y, wk, a;//制御変数
		std::cout << "画像に加算します" << std::endl;
		std::cout << "加算値 = ";
		std::cin >> a;
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				wk = mInstance[y][x] + a;
				if (wk > 255)wk = 255;
				else if (wk < 0)wk = 0;
				img[y][x] = (unsigned char)wk;
			}
		}
		return img;
	}

	Image copy_image(Image mInstance)
		/* image1 のデータをそのまま image2 へ */
	{
		Image img(mInstance.getColsSize(), mInstance.getRowsSize());
		int x, y;    /* 制御変数 */

		printf("画像をコピーします．\n");
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				img[y][x] = mInstance[y][x];
			}
		}
		return img;
	}

	Image inverseImage(Image mInstance) {
		Image img(mInstance.getColsSize(), mInstance.getRowsSize());
		/* 原画像 image1 を反転させて image2 に代入する */
		int x, y;    /* 制御変数 */

		printf("反転画像を作成します．\n");
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				img[y][x] = (unsigned char)
					(MAX_BRIGHTNESS - mInstance[y][x]);
			}
		}
		return img;
	}

	/*
	階調数変換（n段階に量子化）
	*/
	Image convertTone(Image& src_image, int n) {
		Image result_image(src_image.getColsSize(), src_image.getRowsSize());
		//実装面倒だから階調数テーブルを事前に作成する
		std::vector<double> table(256, 0.0);
		//ステップ関数（０の時は絶対０）
		auto step = [](int n) {return n == 0 ? 0 : 1; };
		int tmp = 255 / n;
		int num = 1;
		for (int i = 0; i < 255; i += tmp + 1) {
			for (int j = i; j < i + tmp; j++) {
				//式的にバッファーオーバーランを確実に起こすけど対応する時間はないので付け焼刃で対応
				table[forceRangeAdjust(255, j)] = tmp * num * step(i);
			}
			num++;

		}
		//ここからメイン処理
		for (int i = 0; i < result_image.getRowsSize(); i++) {
			for (int j = 0; j < result_image.getColsSize(); j++) {
				//量子化する
				result_image[i][j] = table[src_image[i][j]];
			}
		}
		return result_image;
	}

	Image convertTone(Image& src_image) {
		return convertTone(src_image, 4);
	}

	Image linearResize(Image& image, double scale) {
		Image image2(image.getColsSize() * scale + 1, image.getRowsSize() * scale + 1);

		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				int x0 = (int)(x / scale);
				int y0 = (int)(y / scale);

				if (x0 < (image.getColsSize() - 1) && y0 < (image.getRowsSize() - 1)) {
					// 左上の画素との距離
					double a = x / scale - x0;
					double b = y / scale - y0;

					int newcolor = 0;
					int* color;
					color = new int[4];
					color[0] = image[x0][y0];
					color[1] = image[x0 + 1][y0];
					color[2] = image[x0][y0 + 1];
					color[3] = image[x0 + 1][y0 + 1];

					int* c_element;
					c_element = new int[4];

					for (int k = 0; k < 3; k++) {
						for (int i = 0; i < 4; i++) {
							c_element[i] = (color[i] >> 8 * k) & 0x00ff;
						}

						// Xの距離×Yの距離を各画素の重みとする
						int new_element = (int)std::round((1 - a) * (1 - b) * c_element[0]
							+ a * (1 - b) * c_element[1]
							+ (1 - a) * b * c_element[2]
							+ a * b * c_element[3]);
						newcolor += (int)(new_element << 8 * k);
					}
					image2[x][y] = newcolor;
					delete color;
					delete c_element;
				}
			}
		}
		return image2;
	}

	Image convertResolution(Image& src_image, int magValue) {
		Image result_image(src_image.getColsSize(), src_image.getRowsSize());
		//ブロックサイズの計算
		double x_block = result_image.getColsSize() * (magValue / 100.0);
		double y_block = result_image.getRowsSize() * (magValue / 100.0);
		//画像をブロックに分割して新しい画像を構築する

		//4重ループになってるので効率悪そう
		int _y = 0;
		std::cout << (result_image.getColsSize() / x_block) << std::endl;
		for (int i = 1; i < (result_image.getRowsSize() / y_block) - 1; i++) {
			int tmp_y = _y + y_block + checkMemoryRange(result_image.getRowsSize(), _y + y_block);
			int _x = 0;
			for (int j = 1; j < result_image.getColsSize() / x_block - 1; j++) {
				int tmp_x = _x + x_block + checkMemoryRange(result_image.getColsSize(), _x + x_block);
				//画素値
				double pixel = 0.0f;
				for (int ly = _y; ly < tmp_y; ly++) {
					for (int lx = _x; lx < tmp_x; lx++) {
						pixel += static_cast<long double>(src_image[ly][lx]);
					}
				}
				//平均値を計算
				pixel = pixel / (x_block * y_block);
				//このピクセル値を放り込んでいく
				for (int ly = _y; ly < tmp_y; ly++) {
					for (int lx = _x; lx < tmp_x; lx++) {
						result_image[ly][lx] = static_cast<unsigned char>(pixel);
					}
				}
				_x = tmp_x;

			}
			_y = tmp_y;

		}

		return result_image;

	}

	Image neighborMethod(Image& image, double scale) {
		Image image2(image.getColsSize() * scale, image.getRowsSize() * scale);
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				int xp = (int)std::round(x / scale);
				int yp = (int)std::round(y / scale);

				if (xp < image.getColsSize() && yp < image.getRowsSize()) {
					int color = image[xp][yp];
					image2[x][y] = color;
				}
			}
		}
		return image2;
	}
	Image resizeImage(Image& instance, double mag) {
		// 使い回す変数は最初に処理しておく
		/*
		バイキュービック法による実装
		参考：http://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html#bi_cubic
		*/
		double parameter[5];
		parameter[0] = RESIZE_PARAMATER + 3.0;
		parameter[1] = RESIZE_PARAMATER + 2.0;
		parameter[2] = -RESIZE_PARAMATER * 4.0;
		parameter[3] = RESIZE_PARAMATER * 8.0;
		parameter[4] = RESIZE_PARAMATER * 5.0;
		Image image2(instance.getColsSize() * mag + 1, instance.getRowsSize() * 2 + 1);
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				// 元画像における画素の対応する場所
				double x0 = x / mag;
				double y0 = y / mag;

				// 基点とする画素
				int xBase = (int)x0;
				int yBase = (int)y0;
				int color = 0;  // 補間する画素
				if (xBase >= 1 && xBase < instance.getColsSize() - 2 && yBase >= 1 && yBase < instance.getRowsSize() - 2) {
					double color_element = 0;
					for (int i = -1; i <= 2; i++) {
						for (int j = -1; j <= 2; j++) {
							// 実際に処理する画素を設定
							int xCurrent = xBase + i;
							int yCurrent = yBase + j;

							// 距離決定
							double distX = std::abs(xCurrent - x0);
							double distY = std::abs(yCurrent - y0);
							// 重み付け
							double weight = 0.0;  // 重み変数
												  // まずはX座標の距離で重みを設定
												  // 1以下、2以下のとき、それぞれ重み付け
							if (distX <= 1.0) {
								weight = 1.0 - parameter[0] * distX * distX + parameter[1] * distX * distX * distX;
							}
							else if (distX <= 2.0) {
								weight = parameter[2] + parameter[3] * distX - parameter[4] * distX * distX + RESIZE_PARAMATER * distX * distX * distX;
							}
							else {
								continue;  // 何も処理しないので、次のループへ
							}

							// Y座標の距離で重みを設定
							if (distY <= 1.0) {
								weight *= 1.0 - parameter[0] * distY * distY + parameter[1] * distY * distY * distY;
							}
							else if (distY <= 2.0) {
								weight *= parameter[2] + parameter[3] * distY - parameter[4] * distY * distY + RESIZE_PARAMATER * distY * distY * distY;
							}
							else {
								continue;
							}
							// 実際に画素を取得
							int color_process = instance[yCurrent][xCurrent];

							// 画素をRGB分割し、重みをかけて足し合わせる
							color_element += ((color_process >> 0 * 8) & 0xff)* weight;

						}
						// 画素を結合する
						color_element = (color_element > 255) ? 255
							: (color_element < 0) ? 0
							: color_element;
						color += (int)color_element << i * 8;

					}
				}
				image2[y][x] = color;
			}
		}
		return image2;
	}


	Image convertLinearHist(Image& image1) {
		int a = 255;
		int b = 0;
		int hist[256];
		for (int i = 0; i < 256; i++) {
			hist[i] = 0;
		}
		Image image2(image1.getColsSize(), image1.getRowsSize());

		for (int y = 0; y < image1.getRowsSize(); y++) {
			for (int x = 0; x < image1.getColsSize(); x++) {
				hist[image1[y][x]] ++;
				if (a > image1[y][x])
					a = image1[y][x];
				if (b < image1[y][x])
					b = image1[y][x];
			}
		}
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				image2[y][x] = 0;
				if (image1[y][x] < a) {
					image2[y][x] = 0;
				}
				else if (image1[y][x] > b) {
					image2[y][x] = MAX_BRIGHTNESS;
				}
				else {
					image2[y][x] = (unsigned char)(MAX_BRIGHTNESS * (image1[y][x] - a) / (double)(b - a));
				}
			}
		}
		return image2;
	}

	Image  convertNonLinearHist(Image& image1) {
		/* 原画像 image1 のヒストグラムを作り画像としてimage2 に代入 */
		long int histogram[GRAYLEVEL]; /* ヒストグラム用配列 */
		long int max_frequency; /* 頻度の最大値 */
		int data; /* 頻度を表すグラフの長さ */
		int a = 255, b = 0;
		int wk[256][256];
		Image image2(image1.getColsSize(), image1.getRowsSize());
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				image2[y][x] = 0;
				if (image1[y][x] <= MAX_BRIGHTNESS / 2) {
					image2[y][x] = (unsigned char)(2 * MAX_BRIGHTNESS * ((double)image1[y][x] / MAX_BRIGHTNESS) * ((double)image1[y][x] / MAX_BRIGHTNESS));
				}
				else if (image1[y][x] > MAX_BRIGHTNESS / 2) {
					image2[y][x] = (unsigned char)((MAX_BRIGHTNESS / 2) * (1 + sqrt((double)(2 * image1[y][x] - MAX_BRIGHTNESS) / MAX_BRIGHTNESS)));
				}
			}
		}
		return image2;
	}


	Image transHistgram(Image& image1) {
		long int histogram[GRAYLEVEL]; /* ヒストグラム用配列 */
		long int max_frequency; /* 頻度の最大値 */
		int a = 255, b = 0;
		Image image2(image1.getColsSize(), image1.getRowsSize());
		int data; /* 頻度を表すグラフの長さ */
		int mean = 0, g = 0, flag = 1000000, sub = 0;
		int level[256], value[256];

		/* 原画像のヒストグラムを求める */
		for (int i = 0; i < GRAYLEVEL; i++) {
			histogram[i] = 0;
			value[i] = 0;
			level[i] = 0;
		}

		for (int y = 0; y < image1.getRowsSize(); y++) {
			for (int x = 0; image1.getColsSize(); x++) {
				histogram[image1[y][x]] ++;
				if (image1[y][x] == 0)
				{
					//何もしなくてよくね？
				}
			}
		}
		g = 256 * 256 / 256;
		int j = 0;
		int k = 0;
		for (int i = 0; i < GRAYLEVEL; i++) {   //分割数を少なくする
			mean += histogram[i];
			sub = abs(mean - g);
			if (i == 255) {
				level[j] = i;
				k++;
				break;
			}
			if (flag >= sub) {
				flag = sub;
			}
			else {
				level[j] = i - 1;
				j++;
				mean = 0;
				flag = 1000000;
				k++;
			}
		}

		mean = (int)(256 / (double)k);
		g = mean;
		for (int i = 1; i < k; i++) {
			value[i] = g;
			g += mean;
		}

		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				for (int i = 0; i < k; i++) {
					if (level[i] >= image1[y][x]) { //平坦化
						image2[y][x] = value[i];
						break;
					}
				}
			}
		}
		return image2;
	}

	Image normalizeFilter(Image& image) {
		Image result(image.getColsSize(), image.getRowsSize());
		/* 適用するフィルタの定義（3x3の8近傍線形平滑化) */
		int weight[3][3] = {
			{ 1,  1,  1 },
			{ 1,  2,  1 },
			{ 1,  1,  1 } };
		double div_const = 10.0; /* <== 最後に割る値 */
		double new_value;        /* 処理後の階調値 */
		/* image2[y][x] の初期化 */
		for (int y = 0; y < image.getRowsSize(); y++)
			for (int x = 0; x < image.getColsSize(); x++)
				result[y][x] = result[y][x];
		/* フィルタリングを行う */
		for (int y = 1; y < image.getRowsSize() - 1; y++)
			for (int x = 1; x < image.getColsSize() - 1; x++) {
				new_value = 0.0;
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
						new_value = new_value +
						weight[i + 1][j + 1] * image[y + i][x + j];
				result[y][x] = (unsigned char)(new_value / div_const);
			}

		return result;

	}

	int sort(int* work) {
		int l, z, k, z1;

		for (k = 1; k < 9; k++) {
			z = work[k];
			for (l = k; l > 0; l--) {
				if (z < work[l - 1]) {
					z1 = work[l - 1];
					work[l - 1] = z;
					work[l] = z1;
				}
			}
		}
		return (unsigned char)work[4];
	}



	Image median_filter(Image& image)
	{
		Image result(image.getColsSize(), image.getRowsSize());
		/* 適用するフィルタの定義（3x3の8近傍線形平滑化) */
		int work[9];
		/* image2[y][x] の初期化 */
		for (int y = 0; y < image.getRowsSize(); y++)
			for (int x = 0; x < image.getColsSize(); x++)
				result[y][x] = image[y][x];
		/* フィルタリングを行う */
		for (int y = 1; y < image.getRowsSize() - 1; y++)
			for (int x = 1; x < image.getColsSize() - 1; x++) {

				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
						work[(j + 1) + (i + 1) * 3] = image[y + i][x + j];
				result[y][x] = sort(work);
			}
		return result;
	}


	Image affectSobelFilter(Image& image) {

		Image result(image.getColsSize(), image.getRowsSize());
		//ソーベルフィルタのカーネル

		//一応怖いので初期化
		for (int y = 0; y < result.getRowsSize(); y++)
			for (int x = 0; x < result.getColsSize(); x++)
				result[y][x] = 0;

		//水平方向
		int sobel[][3] = {
			{-1,0,1},
			{-2,0,2},
			{-1,0,1}
		};

		//垂直方向
		//int sobel[][3] = {
		//{-1,-2,-1},
		//{0,0,0},
		//{1,2,1}
		//};

		for (int y = 1; y < image.getRowsSize() - 1; y++) {
			for (int x = 1; x < image.getColsSize() - 1; x++) {
				//indexエラー回避用
				constexpr int bias = 1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						result[y][x] += sobel[i + bias][j + bias] * image[y + i][x + j];
					}
				}
			}
		}
		return result;
	}

	Image affectLaplacianFilter(Image& image) {

		Image result(image.getColsSize(), image.getRowsSize());
		//ソーベルフィルタのカーネル

		//一応怖いので初期化
		for (int y = 0; y < result.getRowsSize(); y++)
			for (int x = 0; x < result.getColsSize(); x++)
				result[y][x] = 0;

		int laplacian[][3] = {
			{0,1,0},
			{1,-4,1},
			{0,1,0}
		};

		for (int y = 1; y < image.getRowsSize() - 1; y++) {
			for (int x = 1; x < image.getColsSize() - 1; x++) {

				//indexエラー回避用
				constexpr int bias = 1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						result[y][x] += laplacian[i + bias][j + bias] * image[y + i][x + j];
					}
				}
			}
		}
		return result;
	}


	Image affectRadicalizeFilter(Image& image) {

		Image result(image.getColsSize(), image.getRowsSize());
		//ソーベルフィルタのカーネル

		//一応怖いので初期化
		for (int y = 0; y < result.getRowsSize(); y++)
			for (int x = 0; x < result.getColsSize(); x++)
				result[y][x] = 0;

		int radicalize[][3] = {
			{0,-1,0},
			{-1,5,-1},
			{0,-1,0}
		};

		for (int y = 1; y < image.getRowsSize() - 1; y++) {
			for (int x = 1; x < image.getColsSize() - 1; x++) {

				//indexエラー回避用
				constexpr int bias = 1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						result[y][x] += radicalize[i + bias][j + bias] * image[y + i][x + j];
					}
				}
			}
		}
		return result;
	}

	Image threshold(Image& instance, int thresh)
	{
		Image result(instance.getColsSize(), instance.getRowsSize());

		//threshの領域チェック
		thresh = thresh < 0 ? 0 : thresh > 255 ? 255 : thresh;
		int x, y = 0;
#pragma omp parallel for private(y,x)
		for (y = 0; y < instance.getRowsSize(); y++)
		{
			for (x = 0; x < instance.getColsSize(); x++)
			{
				if (instance[y][x] < thresh)
				{
					result[y][x] = 0;
				}
				else
				{
					result[y][x] = 255;
				}
			}
		}
		return result;
	}

	Image adaptiveThreshold(Image& instance, int blockSize, int bias)
	{
		Image result(instance.getColsSize(), instance.getRowsSize());
		double ave = 0.0;
		int x, y = 0;
#pragma omp parallel for private(y,x)
		for (y = blockSize; y < result.getRowsSize() - blockSize; y++)
		{
			for (x = blockSize; x < result.getColsSize() - blockSize; x++)
			{
				ave = 0.0;
				for (int i = y - blockSize; i < y + blockSize; i++)
				{
					for (int j = x - blockSize; j < x + blockSize; j++)
					{
						if (i == y && j == x)continue;
						ave += instance[i][j];
					}
				}

				auto tmp = std::pow((2 * blockSize + 1), 2) - 1;
				ave /= static_cast<int>(tmp);

				ave = instance[y][x] - ave <= 0 ?
					(ave - bias >= 0 ? ave - bias : ave)
					:
					(ave + bias < 256 ? ave + bias : ave);

				if (instance[y][x] < ave)
				{
					result[y][x] = 0;
				}
				else
				{
					result[y][x] = 255;
				}
			}
		}

		return result;
	}

	Image expansion(Image& instance)
	{
		auto binary = threshold(instance, 96);
		Image result(instance.getColsSize(), instance.getRowsSize());

		int x, y = 0;
#pragma omp parallel for private(y,x)
		for (y = 1; y < result.getRowsSize() - 1; y++)
		{
			for (x = 1; x < result.getColsSize() - 1; x++)
			{

				for (int i = y - 1; i < y + 2; i++)
				{
					for (int j = x - 1; j < x + 2; j++)
					{

						if (binary[y][x] != 0 && !(i == x && j == y))
						{
							result[y][x] = 255;
							break;
						}
					}
				}
			}
		}
		return result;
	}

	Image contraction(Image& instance)
	{
		auto binary = threshold(instance, 100);
		Image result(binary.getColsSize(), binary.getRowsSize());

		int x, y = 0;

#pragma omp parallel for private(y,x)
		for (y = 1; y < result.getRowsSize() - 1; y++)
		{
			for (x = 1; x < result.getColsSize() - 1; x++)
			{
				result[y][x] = 255;
				for (int i = y - 1; i < y + 2; i++)
				{
					for (int j = x - 1; j < x + 2; j++)
					{
						if (binary[y][x] == 0 && !(i == x && j == y))
						{
							result[y][x] = 0;
							break;
						}
					}
				}
			}
		}
		return result;
	}

}