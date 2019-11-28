#pragma once
#include<vector>
#include<string>
//�摜�N���X
namespace ImgProcLib {

	class Image {
	public:
		Image(int width, int height) :x_size(width), y_size(height) {
			//�z�񏉊���
			alloc_vector();
		}
		//�f�t�H���g�R���X�g���N�^
		Image() :Image(1024, 1024) {}
		void load_image_data(std::string filename); /* �摜�ǂݍ��ݗp�֐� */
		/**
		�v���p�e�B�����J���邱�Ƃ͂��܂��낵���Ȃ�
		*/
		int x_size = 0, y_size = 0; /* image1 �̉���f���C�c��f�� */
		int getColsSize()const { return x_size; }
		int getRowsSize() const { return y_size; }
		//���Z�q�I�[�o�[���[�h
		std::vector<unsigned char>& operator[](std::size_t n)& { return image[n]; }
		const std::vector<unsigned char>& operator[](std::size_t n) const& { return image[n]; }
	private:
		/* ���ϐ��̐錾 */
		/* �摜�p�z��P�C�摜�p�z��Q */
		std::vector<std::vector<unsigned char>>image;
		void alloc_vector();
	};

}