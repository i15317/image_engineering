#define _CRT_SECURE_NO_WARNINGS
#include"stdafx.h"
#include"class.hpp"

void mImage::load_image_data()
/* pgm �摜�C����f���C�c��f���̃f�[�^���t�@�C������ǂݍ��݁C*/
/* image1[ ][ ]�Cx_size1�Cy_size1 �ɂ��ꂼ��������D         */
{
	char file_name[MAX_FILENAME] = "lecture1/girl.pgm"; /* �t�@�C�����p�̕����z�� */
	char buffer[MAX_BUFFERSIZE];  /* �f�[�^�ǂݍ��ݗp��ƕϐ� */
	FILE *fp; /* �t�@�C���|�C���^ */
	int max_gray; /* �ő�K���l */
	int x, y; /* ���[�v�ϐ� */
			  /* ���̓t�@�C���̃I�[�v�� */
	printf("-----------------------------------------------------\n");
	printf("  ���m�N���K���摜���̓��[�`��\n");
	printf("-----------------------------------------------------\n");
	printf("�t�@�C���`���� pgm, �o�C�i���`���Ƃ��܂��D\n");
	printf("���̓t�@�C���� (lecture1/girl.pgm) : ");
	//scanf("%s", file_name);
	fp = fopen(file_name, "rb");
	if (NULL == fp) {
		printf("���̖��O�̃t�@�C���͑��݂��܂���D\n");
		exit(1);
	}
	/* �t�@�C���^�C�v(=P5)�̊m�F */
	fgets(buffer, MAX_BUFFERSIZE, fp);
	if (buffer[0] != 'P' || buffer[1] != '5') {
		printf("�t�@�C���̃t�H�[�}�b�g�� P5 �Ƃ͈قȂ�܂��D\n");
		exit(1);
	}
	/* x_size1, y_size1 �̑���i#����n�܂�R�����g�͓ǂݔ�΂��j */
	x_size1 = 0;
	y_size1 = 0;
	while (x_size1 == 0 || y_size1 == 0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			sscanf(buffer, "%d %d", &x_size1, &y_size1);
		}
	}
	/* max_gray �̑���i#����n�܂�R�����g�͓ǂݔ�΂��j */
	max_gray = 0;
	while (max_gray == 0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			sscanf(buffer, "%d", &max_gray);
		}
	}
	/* �p�����[�^�̉�ʂւ̕\�� */
	printf("���̉�f�� = %d, �c�̉�f�� = %d\n", x_size1, y_size1);
	printf("�ő�K���l = %d\n", max_gray);
	if (x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE) {
		printf("�z��l %d x %d �𒴂��Ă��܂��D\n",
			MAX_IMAGESIZE, MAX_IMAGESIZE);
		printf("�������������ȉ摜���g���ĉ������D\n");
		exit(1);
	}
	if (max_gray != MAX_BRIGHTNESS) {
		printf("�ő�K���l���s�K�؂ł��D\n");
		exit(1);
	}
	/* �摜�f�[�^��ǂݍ���ŉ摜�p�z��ɑ������ */
	for (y = 0; y < y_size1; y++) {
		for (x = 0; x < x_size1; x++) {
			image1[y][x] = (unsigned char)fgetc(fp);
		}
	}
	printf("�f�[�^�͐������ǂݍ��܂�܂����D\n");
	printf("-----------------------------------------------------\n");
	fclose(fp);
}
void mImage::add_image() {
	int x, y, wk, a;//����ϐ�
	std::cout << "�摜�ɉ��Z���܂�" << std::endl;
	std::cout << "���Z�l = ";
	std::cin >> a;
	this->x_size2 = x_size1;
	this->y_size2 = y_size1;
	for (y = 0; y < y_size2; y++) {
		for (x = 0; x < x_size2; x++) {
			wk = image1[y][x] + a;
			if (wk > 255)wk = 255;
			else if (wk < 0)wk = 0;
			image2[y][x] = (unsigned char)wk;
		}
	}
}
void mImage::save_image_data()
/* image2[ ][ ], x_size2, y_size2 �̃f�[�^���C���ꂼ�� pgm �摜�C*/
/* ����f���C�c��f���Ƃ��ăt�@�C���ɕۑ�����D                  */
{
	char file_name[MAX_FILENAME]; /* �t�@�C�����p�̕����z�� */
	FILE *fp; /* �t�@�C���|�C���^ */
	int x, y; /* ���[�v�ϐ� */

			  /* �o�̓t�@�C���̃I�[�v�� */
	printf("-----------------------------------------------------\n");
	printf("  ���m�N���K���摜�ipgm�`���j�o�̓��[�`��\n");
	printf("-----------------------------------------------------\n");
	printf("�o�̓t�@�C���� (*.pgm) : ");
	scanf("%s", file_name);
	fp = fopen(file_name, "wb");
	/* �t�@�C�����ʎq "P5" ��擪�ɏo�͂��� */
	fputs("P5\n", fp);
	/* # �Ŏn�܂�R�����g�s�i�ȗ��\�j */
	fputs("# Created by Image Processing\n", fp);
	/* �摜�̉����C�c���̏o�� */
	fprintf(fp, "%d %d\n", x_size2, y_size2);
	/* �ő�K���l�̏o�� */
	fprintf(fp, "%d\n", MAX_BRIGHTNESS);
	/* �摜�f�[�^�̏o�� */
	for (y = 0; y < y_size2; y++) {
		for (x = 0; x < x_size2; x++) {
			fputc(image2[y][x], fp);
		}
	}
	printf("�f�[�^�͐������o�͂���܂����D\n");
	printf("-----------------------------------------------------\n");
	fclose(fp);
}

void mImage::copy_image()
/* image1 �̃f�[�^�����̂܂� image2 �� */
{
	int x, y;    /* ����ϐ� */

	printf("�摜���R�s�[���܂��D\n");
	x_size2 = x_size1;  /* ����f�� */
	y_size2 = y_size1;  /* �c��f�� */
	for (y = 0; y < y_size2; y++) {
		for (x = 0; x < x_size2; x++) {
			image2[y][x] = image1[y][x];
		}
	}
}