#pragma once
#include"pch.h"

namespace ImgProcLib {
	//�O���錾
	class Image;

	///* �֐��̃v���g�^�C�v�錾 */
	void save_image_data(Image& instance); /* �摜�������ݗp�֐� */
	void save_image_data(Image& instance, std::string filename);
	Image imageRead(std::string filename);
}