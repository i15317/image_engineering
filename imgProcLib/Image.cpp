#include"pch.h"
#include"Constant.h"
#include"Image.h"


using namespace ImgProcLib;
void Image::load_image_data(std::string file_name)
/* pgm 画像，横画素数，縦画素数のデータをファイルから読み込み，*/
/* image1[ ][ ]，__x_size1，__y_size1 にそれぞれ代入する．         */
{
	char buffer[MAX_BUFFERSIZE];  /* データ読み込み用作業変数 */
	FILE* fp; /* ファイルポインタ */
	int max_gray; /* 最大階調値 */
	int x, y; /* ループ変数 */

	/* 入力ファイルのオープン */
	printf("-----------------------------------------------------\n");
	printf("  モノクロ階調画像入力ルーチン\n");
	printf("-----------------------------------------------------\n");
	printf("ファイル形式は pgm, バイナリ形式とします．\n");
	printf("入力ファイル名 (lecture1/girl.pgm) : ");
	//scanf("%s", file_name);
	fp = fopen(file_name.c_str(), "rb");
	if (NULL == fp) {
		printf("その名前のファイルは存在しません．\n");
		exit(1);
	}
	/* ファイルタイプ(=P5)の確認 */
	fgets(buffer, MAX_BUFFERSIZE, fp);
	if (buffer[0] != 'P' || buffer[1] != '5') {
		printf("ファイルのフォーマットが P5 とは異なります．\n");
		exit(1);
	}
	/* __x_size1, __y_size1 の代入（#から始まるコメントは読み飛ばす） */
	m_imageWidth = 0;
	m_imageHeight = 0;
	while (m_imageWidth == 0 || m_imageHeight == 0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			auto x = sscanf(buffer, "%d %d", &m_imageWidth, &m_imageHeight);
		}
	}

	//配列領域の確保
	alloc_vector(m_imageWidth, m_imageHeight);

	/* max_gray の代入（#から始まるコメントは読み飛ばす） */
	max_gray = 0;
	while (max_gray == 0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			auto x = sscanf(buffer, "%d", &max_gray);
		}
	}
	/* パラメータの画面への表示 */
	printf("横の画素数 = %d, 縦の画素数 = %d\n", m_imageWidth, m_imageHeight);
	printf("最大階調値 = %d\n", max_gray);
	if (m_imageWidth > MAX_IMAGESIZE || m_imageHeight > MAX_IMAGESIZE) {
		printf("想定値 %d x %d を超えています．\n",
			MAX_IMAGESIZE, MAX_IMAGESIZE);
		printf("もう少し小さな画像を使って下さい．\n");
		exit(1);
	}
	if (max_gray != MAX_BRIGHTNESS) {
		printf("最大階調値が不適切です．\n");
		exit(1);
	}
	/* 画像データを読み込んで画像用配列に代入する */
	for (y = 0; y < m_imageHeight; y++) {
		for (x = 0; x < m_imageWidth; x++) {
			image[y][x] = (unsigned char)fgetc(fp);
		}
	}
	printf("データは正しく読み込まれました．\n");
	printf("-----------------------------------------------------\n");
	fclose(fp);
}

void Image::alloc_vector(int x_size, int y_size) {
	//範囲チェック
	if ((x_size < 0 || x_size > MAX_IMAGESIZE) || (y_size < 0 || y_size > MAX_IMAGESIZE)) {
		//強制終了
		abort();
	}
	else {
		image.clear();
		image.shrink_to_fit();
		//軸方向の領域確保
		image.resize(y_size);
		for (auto& y : image) {
			//x軸方向の領域確保
			y.resize(x_size);
		}
	}
}