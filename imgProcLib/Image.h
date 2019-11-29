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

		/*
		�z�񉉎Z�q [y���W][x���W]�Ƃ��ăA�N�Z�X����
		*/
		std::vector<unsigned char>& operator[](std::size_t n)& { return image[n]; }
		const std::vector<unsigned char>& operator[](std::size_t n) const& { return image[n]; }

		/*
		���ʉ��Z�q�ł���f�փA�N�Z�X���邱�Ƃ��\
		(x���W,y���W)�Ǝw�肷�邱�ƂőΉ������f�ɃA�N�Z�X���邱�Ƃ��o����
		*/

		unsigned char& operator()(std::size_t x, std::size_t y)& { return image[y][x]; }
		const unsigned char& operator()(std::size_t x, std::size_t y) const& { return image[y][x]; }



		//�l�����Z�̃I�[�o�[���[�h
		
		/*
		��f�̉��Z�isafeAdd�͎g��Ȃ��j
		*/
		Image operator+(Image image) {
			Image result(this->getColsSize(), this->getRowsSize());
			for (int x = 0; x < image.getColsSize(); x++) {
				for (int y = 0; y < image.getRowsSize(); y++) {
					result(x, y) = this->image[y][x] + image(x, y);
				}
			}
		}


	private:
		std::vector<std::vector<unsigned char>>image;
		void alloc_vector(int x_size, int y_size);
		int m_imageWidth = 0;
		int m_imageHeight = 0; /* image1 �̉���f���C�c��f�� */

	};

}