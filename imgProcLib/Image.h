#pragma once
#include<vector>
#include<string>
//画像クラス
namespace ImgProcLib {

	class Image {
	public:
		Image(int width, int height) :m_imageWidth(width), m_imageHeight(height) {
			//配列初期化
			alloc_vector(width, height);
		}

		//デフォルトコンストラクタ
		Image() :Image(1024, 1024) {}
		void load_image_data(std::string filename); /* 画像読み込み用関数 */

		int getColsSize()const { return m_imageWidth; }
		int getRowsSize() const { return m_imageHeight; }

		//演算子オーバーロード

		/*
		配列演算子 [y座標][x座標]としてアクセスする
		*/
		std::vector<unsigned char>& operator[](std::size_t n)& { return image[n]; }
		const std::vector<unsigned char>& operator[](std::size_t n) const& { return image[n]; }

		/*
		括弧演算子でも画素へアクセスすることが可能
		(x座標,y座標)と指定することで対応する画素にアクセスすることが出来る
		*/

		unsigned char& operator()(std::size_t x, std::size_t y)& { return image[y][x]; }
		const unsigned char& operator()(std::size_t x, std::size_t y) const& { return image[y][x]; }



		//四則演算のオーバーロード
		
		/*
		画素の加算（safeAddは使わない）
		*/
		Image operator+(Image image) {
			Image result(this->getColsSize(), this->getRowsSize());
			for (int x = 0; x < image.getColsSize(); x++) {
				for (int y = 0; y < image.getRowsSize(); y++) {
					result(x, y) = this->image[y][x] + image(x, y);
				}
			}
		}


	private:
		std::vector<std::vector<unsigned char>>image;
		void alloc_vector(int x_size, int y_size);
		int m_imageWidth = 0;
		int m_imageHeight = 0; /* image1 の横画素数，縦画素数 */

	};

}