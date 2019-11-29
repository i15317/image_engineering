#pragma once
#include<vector>
#include<string>
//�摜�N���X
namespace ImgProcLib {

	class Image {
	public:
		Image(int width, int height) :m_imageWidth(width), m_imageHeight(height) {
			//�z�񏉊���
			alloc_vector(width, height);
		}
		
		//�f�t�H���g�R���X�g���N�^
		Image() :Image(1024, 1024) {}
		void load_image_data(std::string filename); /* �摜�ǂݍ��ݗp�֐� */

		int getColsSize()const { return m_imageWidth; }
		int getRowsSize() const { return m_imageHeight; }

		//���Z�q�I�[�o�[���[�h
		std::vector<unsigned char>& operator[](std::size_t n)& { return image[n]; }
		const std::vector<unsigned char>& operator[](std::size_t n) const& { return image[n]; }
		unsigned char& operator()(std::size_t x, std::size_t y)& { return image[y][x]; }
		const unsigned char& operator()(std::size_t x, std::size_t y) const& { return image[y][x]; }

	private:
		std::vector<std::vector<unsigned char>>image;
		void alloc_vector(int x_size, int y_size);
		int m_imageWidth = 0;
		int m_imageHeight = 0; /* image1 �̉���f���C�c��f�� */

	};

}