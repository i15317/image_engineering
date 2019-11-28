/* copyimage.c  このプログラムの名前 */
#include "../stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include"mypgm.h"

void copy_image( )
/* image1 のデータをそのまま image2 へ */
{
    int x, y;    /* 制御変数 */

    printf("画像をコピーします．\n");
    x_size2 = x_size1;  /* 横画素数 */
    y_size2 = y_size1;  /* 縦画素数 */
    for ( y = 0; y < y_size2; y ++ ){
        for ( x = 0; x < x_size2; x ++ ){
            image2[y][x] = image1[y][x];
        }
    }
}

int main( )
{
    load_image_data( );	/* 画像データを image1 に読み込む */
    copy_image( ); 		/* image1 のデータをそのまま image2 へ */
    save_image_data( );	/* image2 を保存する */
    return 0;
}