#include"pch.h"

#include"Image.h"
#include"Constant.h"
#include"imgProcLibIO.h"
#define _CRT_SECURE_NO_WARNINGS

namespace ImgProcLib {

	void save_image_data(Image& img)
		/* image2[ ][ ], __getColsSize()2, __getRowsSize()2 のデータを，それぞれ pgm 画像，*/
		/* 横画素数，縦画素数としてファイルに保存する．                  */
	{
		char file_name[MAX_FILENAME]; /* ファイル名用の文字配列 */
		FILE* fp; /* ファイルポインタ */
		int x, y = 0; /* ループ変数 */
				  /* 出力ファイルのオープン */
		printf("-----------------------------------------------------\n");
		printf("  モノクロ階調画像（pgm形式）出力ルーチン\n");
		printf("-----------------------------------------------------\n");
		printf("出力ファイル名 (*.pgm) : ");
		scanf("%s", file_name);
		fp = fopen(file_name, "wb");
		/* ファイル識別子 "P5" を先頭に出力する */
		fputs("P5\n", fp);
		/* # で始まるコメント行（省略可能） */
		fputs("# Created by Image Processing\n", fp);
		/* 画像の横幅，縦幅の出力 */
		fprintf(fp, "%d %d\n", img.getColsSize(), img.getRowsSize());
		/* 最大階調値の出力 */
		fprintf(fp, "%d\n", MAX_BRIGHTNESS);
		/* 画像データの出力 */
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				fputc(img[y][x], fp);
			}
		}
		printf("データは正しく出力されました．\n");
		printf("-----------------------------------------------------\n");
		fclose(fp);

	}

	void save_image_data(Image& img, std::string filename)
		/* image2[ ][ ], __getColsSize()2, __getRowsSize()2 のデータを，それぞれ pgm 画像，*/
		/* 横画素数，縦画素数としてファイルに保存する．                  */
	{
		FILE* fp; /* ファイルポインタ */
		int x, y; /* ループ変数 */
				  /* 出力ファイルのオープン */
		printf("-----------------------------------------------------\n");
		printf("  モノクロ階調画像（pgm形式）出力ルーチン\n");
		printf("-----------------------------------------------------\n");
		std::cout << ("出力ファイル名 (" + filename + ") : ");

		fp = fopen(filename.c_str(), "wb");
		/* ファイル識別子 "P5" を先頭に出力する */
		fputs("P5\n", fp);
		/* # で始まるコメント行（省略可能） */
		fputs("# Created by Image Processing\n", fp);
		/* 画像の横幅，縦幅の出力 */
		fprintf(fp, "%d %d\n", img.getColsSize(), img.getRowsSize());
		/* 最大階調値の出力 */
		fprintf(fp, "%d\n", MAX_BRIGHTNESS);
		/* 画像データの出力 */
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				fputc(img[y][x], fp);
			}
		}
		printf("データは正しく出力されました．\n");
		printf("-----------------------------------------------------\n");
		fclose(fp);
	}


	//Todo 遅くなる原因かもねｗ
	Image imageRead(std::string filename)
		/* pgm 画像，横画素数，縦画素数のデータをファイルから読み込み，*/
		/* image1[ ][ ]，__getColsSize()1，__getRowsSize()1 にそれぞれ代入する．         */
	{
		Image result;
		result.load_image_data(filename);
		return result;
	}

}