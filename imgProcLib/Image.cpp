#include"pch.h"
#include"Constant.h"
#include"Image.h"


using namespace ImgProcLib;
void Image::load_image_data(std::string file_name)
/* pgm �摜�C����f���C�c��f���̃f�[�^���t�@�C������ǂݍ��݁C*/
/* image1[ ][ ]�C__x_size1�C__y_size1 �ɂ��ꂼ��������D         */
{
	char buffer[MAX_BUFFERSIZE];  /* �f�[�^�ǂݍ��ݗp��ƕϐ� */
	FILE* fp; /* �t�@�C���|�C���^ */
	int max_gray; /* �ő�K���l */
	int x, y; /* ���[�v�ϐ� */

	/* ���̓t�@�C���̃I�[�v�� */
	printf("-----------------------------------------------------\n");
	printf("  ���m�N���K���摜���̓��[�`��\n");
	printf("-----------------------------------------------------\n");
	printf("�t�@�C���`���� pgm, �o�C�i���`���Ƃ��܂��D\n");
	printf("���̓t�@�C���� (lecture1/girl.pgm) : ");
	//scanf("%s", file_name);
	fp = fopen(file_name.c_str(), "rb");
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
	/* __x_size1, __y_size1 �̑���i#����n�܂�R�����g�͓ǂݔ�΂��j */
	m_imageWidth = 0;
	m_imageHeight = 0;
	while (m_imageWidth == 0 || m_imageHeight == 0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			auto x = sscanf(buffer, "%d %d", &m_imageWidth, &m_imageHeight);
		}
	}

	//�z��̈�̊m��
	alloc_vector(m_imageWidth, m_imageHeight);

	/* max_gray �̑���i#����n�܂�R�����g�͓ǂݔ�΂��j */
	max_gray = 0;
	while (max_gray == 0) {
		fgets(buffer, MAX_BUFFERSIZE, fp);
		if (buffer[0] != '#') {
			auto x = sscanf(buffer, "%d", &max_gray);
		}
	}
	/* �p�����[�^�̉�ʂւ̕\�� */
	printf("���̉�f�� = %d, �c�̉�f�� = %d\n", m_imageWidth, m_imageHeight);
	printf("�ő�K���l = %d\n", max_gray);
	if (m_imageWidth > MAX_IMAGESIZE || m_imageHeight > MAX_IMAGESIZE) {
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
	for (y = 0; y < m_imageHeight; y++) {
		for (x = 0; x < m_imageWidth; x++) {
			image[y][x] = (unsigned char)fgetc(fp);
		}
	}
	printf("�f�[�^�͐������ǂݍ��܂�܂����D\n");
	printf("-----------------------------------------------------\n");
	fclose(fp);
}

void Image::alloc_vector(int x_size, int y_size) {
	//�͈̓`�F�b�N
	if ((x_size < 0 || x_size > MAX_IMAGESIZE) || (y_size < 0 || y_size > MAX_IMAGESIZE)) {
		//�����I��
		abort();
	}
	else {
		image.clear();
		image.shrink_to_fit();
		//�������̗̈�m��
		image.resize(y_size);
		for (auto& y : image) {
			//x�������̗̈�m��
			y.resize(x_size);
		}
	}
}