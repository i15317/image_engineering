/* copyimage.c  ���̃v���O�����̖��O */
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
/* image1 �̃f�[�^�����̂܂� image2 �� */
{
    int x, y,wk,a;    /* ����ϐ� */

    printf("�摜���R�s�[���܂��D\n");
	printf("���Z=");
	scanf("%d", &a);
    x_size2 = x_size1;  /* ����f�� */
    y_size2 = y_size1;  /* �c��f�� */
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
    load_image_data( );	/* �摜�f�[�^�� image1 �ɓǂݍ��� */
    add_image( ); 		/* image1 �̃f�[�^�����̂܂� image2 �� */
    save_image_data( );	/* image2 ��ۑ����� */
    return 0;
}
