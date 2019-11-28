#pragma once
#include<vector>
#include<string>
//画像クラス
namespace ImgProcLib {

	class Image {
	public:
		Image(int width, int height) :x_size(width), y_size(height) {
			//配列初期化
			alloc_vector();
		}
		//デフォルトコンストラクタ
		Image() :Image(1024, 1024) {}
		void load_image_data(std::string filename); /* 画像読み込み用関数 */
		/**
		プロパティを公開することはあまりよろしくない
		*/
		int x_size = 0, y_size = 0; /* image1 の横画素数，縦画素数 */
		int getColsSize()const { return x_size; }
		int getRowsSize() const { return y_size; }
		//演算子オーバーロード
		std::vector<unsigned char>& operator[](std::size_t n)& { return image[n]; }
		const std::vector<unsigned char>& operator[](std::size_t n) const& { return image[n]; }
	private:
		/* 大域変数の宣言 */
		/* 画像用配列１，画像用配列２ */
		std::vector<std::vector<unsigned char>>image;
		void alloc_vector();
	};

}