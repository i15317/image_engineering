/* copyimage.c  ���̃v���O�����̖��O */
#include "../stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include"mypgm.h"

void copy_image( )
/* image1 �̃f�[�^�����̂܂� image2 �� */
{
    int x, y;    /* ����ϐ� */

    printf("�摜���R�s�[���܂��D\n");
    x_size2 = x_size1;  /* ����f�� */
    y_size2 = y_size1;  /* �c��f�� */
    for ( y = 0; y < y_size2; y ++ ){
        for ( x = 0; x < x_size2; x ++ ){
            image2[y][x] = image1[y][x];
        }
    }
}

int main( )
{
    load_image_data( );	/* �摜�f�[�^�� image1 �ɓǂݍ��� */
    copy_image( ); 		/* image1 �̃f�[�^�����̂܂� image2 �� */
    save_image_data( );	/* image2 ��ۑ����� */
    return 0;
}