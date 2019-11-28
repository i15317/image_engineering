/* copyimage.c  このプログラムの名前 */
#include<stdio.h>
#include<stdlib.h>
#include"mypgm.h"

void add_image();
int main()
{
	load_image_date();
	add_image();
	save_image_data();
	return 0;
}
void add_image( )
/* image1 のデータをそのまま image2 へ */
{
    int x, y,wk,a;    /* 制御変数 */

    printf("画像をコピーします．\n");
	printf("加算=");
	scanf("%d", &a);
    x_size2 = x_size1;  /* 横画素数 */
    y_size2 = y_size1;  /* 縦画素数 */
    for ( y = 0; y < y_size2; y ++ ){
        for ( x = 0; x < x_size2; x ++ ){
			wk = image1[y][x] - a;
			if (wk > 255) wk = 255;
			if (wk < 0) wk = 0;
            image2[y][x] = (unsigned char)wk;
        }
    }
}

int main()
{
    load_image_data( );	/* 画像データを image1 に読み込む */
    add_image( ); 		/* image1 のデータをそのまま image2 へ */
    save_image_data( );	/* image2 を保存する */
    return 0;
}
