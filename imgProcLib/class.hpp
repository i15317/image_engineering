#pragma once

class mImage {
public:
	mImage() {}
public:
	///* �֐��̃v���g�^�C�v�錾 */
	void load_image_data(); /* �摜�ǂݍ��ݗp�֐� */
	void save_image_data(); /* �摜�������ݗp�֐� */
	void copy_image();
	void add_image();

private:
	/* ���ϐ��̐錾 */
	/* �摜�p�z��P�C�摜�p�z��Q */
	std::array<std::array<unsigned char, MAX_IMAGESIZE/2>, MAX_IMAGESIZE/2>image1;
	std::array<std::array<unsigned char, MAX_IMAGESIZE / 2>, MAX_IMAGESIZE / 2>image2;

	int x_size1=0, y_size1=0, /* image1 �̉���f���C�c��f�� */
		x_size2=0, y_size2=0; /* image2 �̉���f���C�c��f�� */
};