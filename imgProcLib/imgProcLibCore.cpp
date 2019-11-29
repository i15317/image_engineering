#include"pch.h"
#include"Image.h"
#include"Constant.h"
#include"algorithm.hpp"
#include"imgProcLibCore.h"
#include<omp.h>
////
////
#define _CRT_SECURE_NO_WARNINGS

////
////

namespace ImgProcLib {

	Image add_image(Image mInstance) {
		//���ʂ��i�[����C���X�^���X
		Image img(mInstance.getColsSize(), mInstance.getRowsSize());
		int x, y, wk, a;//����ϐ�
		std::cout << "�摜�ɉ��Z���܂�" << std::endl;
		std::cout << "���Z�l = ";
		std::cin >> a;
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				wk = mInstance[y][x] + a;
				if (wk > 255)wk = 255;
				else if (wk < 0)wk = 0;
				img[y][x] = (unsigned char)wk;
			}
		}
		return img;
	}

	Image copy_image(Image mInstance)
		/* image1 �̃f�[�^�����̂܂� image2 �� */
	{
		Image img(mInstance.getColsSize(), mInstance.getRowsSize());
		int x, y;    /* ����ϐ� */

		printf("�摜���R�s�[���܂��D\n");
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				img[y][x] = mInstance[y][x];
			}
		}
		return img;
	}

	Image inverseImage(Image mInstance) {
		Image img(mInstance.getColsSize(), mInstance.getRowsSize());
		/* ���摜 image1 �𔽓]������ image2 �ɑ������ */
		int x, y;    /* ����ϐ� */

		printf("���]�摜���쐬���܂��D\n");
		for (y = 0; y < img.getRowsSize(); y++) {
			for (x = 0; x < img.getColsSize(); x++) {
				img[y][x] = (unsigned char)
					(MAX_BRIGHTNESS - mInstance[y][x]);
			}
		}
		return img;
	}

	/*
	�K�����ϊ��in�i�K�ɗʎq���j
	*/
	Image convertTone(Image& src_image, int n) {
		Image result_image(src_image.getColsSize(), src_image.getRowsSize());
		//�����ʓ|������K�����e�[�u�������O�ɍ쐬����
		std::vector<double> table(256, 0.0);
		//�X�e�b�v�֐��i�O�̎��͐�΂O�j
		auto step = [](int n) {return n == 0 ? 0 : 1; };
		int tmp = 255 / n;
		int num = 1;
		for (int i = 0; i < 255; i += tmp + 1) {
			for (int j = i; j < i + tmp; j++) {
				//���I�Ƀo�b�t�@�[�I�[�o�[�������m���ɋN�������ǑΉ����鎞�Ԃ͂Ȃ��̂ŕt���Đn�őΉ�
				table[forceRangeAdjust(255, j)] = tmp * num * step(i);
			}
			num++;

		}
		//�������烁�C������
		for (int i = 0; i < result_image.getRowsSize(); i++) {
			for (int j = 0; j < result_image.getColsSize(); j++) {
				//�ʎq������
				result_image[i][j] = table[src_image[i][j]];
			}
		}
		return result_image;
	}

	Image convertTone(Image& src_image) {
		return convertTone(src_image, 4);
	}

	Image linearResize(Image& image, double scale) {
		Image image2(image.getColsSize() * scale + 1, image.getRowsSize() * scale + 1);

		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				int x0 = (int)(x / scale);
				int y0 = (int)(y / scale);

				if (x0 < (image.getColsSize() - 1) && y0 < (image.getRowsSize() - 1)) {
					// ����̉�f�Ƃ̋���
					double a = x / scale - x0;
					double b = y / scale - y0;

					int newcolor = 0;
					int* color;
					color = new int[4];
					color[0] = image[x0][y0];
					color[1] = image[x0 + 1][y0];
					color[2] = image[x0][y0 + 1];
					color[3] = image[x0 + 1][y0 + 1];

					int* c_element;
					c_element = new int[4];

					for (int k = 0; k < 3; k++) {
						for (int i = 0; i < 4; i++) {
							c_element[i] = (color[i] >> 8 * k) & 0x00ff;
						}

						// X�̋����~Y�̋������e��f�̏d�݂Ƃ���
						int new_element = (int)std::round((1 - a) * (1 - b) * c_element[0]
							+ a * (1 - b) * c_element[1]
							+ (1 - a) * b * c_element[2]
							+ a * b * c_element[3]);
						newcolor += (int)(new_element << 8 * k);
					}
					image2[x][y] = newcolor;
					delete color;
					delete c_element;
				}
			}
		}
		return image2;
	}

	Image convertResolution(Image& src_image, int magValue) {
		Image result_image(src_image.getColsSize(), src_image.getRowsSize());
		//�u���b�N�T�C�Y�̌v�Z
		double x_block = result_image.getColsSize() * (magValue / 100.0);
		double y_block = result_image.getRowsSize() * (magValue / 100.0);
		//�摜���u���b�N�ɕ������ĐV�����摜���\�z����

		//4�d���[�v�ɂȂ��Ă�̂Ō���������
		int _y = 0;
		std::cout << (result_image.getColsSize() / x_block) << std::endl;
		for (int i = 1; i < (result_image.getRowsSize() / y_block) - 1; i++) {
			int tmp_y = _y + y_block + checkMemoryRange(result_image.getRowsSize(), _y + y_block);
			int _x = 0;
			for (int j = 1; j < result_image.getColsSize() / x_block - 1; j++) {
				int tmp_x = _x + x_block + checkMemoryRange(result_image.getColsSize(), _x + x_block);
				//��f�l
				double pixel = 0.0f;
				for (int ly = _y; ly < tmp_y; ly++) {
					for (int lx = _x; lx < tmp_x; lx++) {
						pixel += static_cast<long double>(src_image[ly][lx]);
					}
				}
				//���ϒl���v�Z
				pixel = pixel / (x_block * y_block);
				//���̃s�N�Z���l����荞��ł���
				for (int ly = _y; ly < tmp_y; ly++) {
					for (int lx = _x; lx < tmp_x; lx++) {
						result_image[ly][lx] = static_cast<unsigned char>(pixel);
					}
				}
				_x = tmp_x;

			}
			_y = tmp_y;

		}

		return result_image;

	}

	Image neighborMethod(Image& image, double scale) {
		Image image2(image.getColsSize() * scale, image.getRowsSize() * scale);
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				int xp = (int)std::round(x / scale);
				int yp = (int)std::round(y / scale);

				if (xp < image.getColsSize() && yp < image.getRowsSize()) {
					int color = image[xp][yp];
					image2[x][y] = color;
				}
			}
		}
		return image2;
	}
	Image resizeImage(Image& instance, double mag) {
		// �g���񂷕ϐ��͍ŏ��ɏ������Ă���
		/*
		�o�C�L���[�r�b�N�@�ɂ�����
		�Q�l�Fhttp://www7a.biglobe.ne.jp/~fairytale/article/program/graphics.html#bi_cubic
		*/
		double parameter[5];
		parameter[0] = RESIZE_PARAMATER + 3.0;
		parameter[1] = RESIZE_PARAMATER + 2.0;
		parameter[2] = -RESIZE_PARAMATER * 4.0;
		parameter[3] = RESIZE_PARAMATER * 8.0;
		parameter[4] = RESIZE_PARAMATER * 5.0;
		Image image2(instance.getColsSize() * mag + 1, instance.getRowsSize() * 2 + 1);
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				// ���摜�ɂ������f�̑Ή�����ꏊ
				double x0 = x / mag;
				double y0 = y / mag;

				// ��_�Ƃ����f
				int xBase = (int)x0;
				int yBase = (int)y0;
				int color = 0;  // ��Ԃ����f
				if (xBase >= 1 && xBase < instance.getColsSize() - 2 && yBase >= 1 && yBase < instance.getRowsSize() - 2) {
					double color_element = 0;
					for (int i = -1; i <= 2; i++) {
						for (int j = -1; j <= 2; j++) {
							// ���ۂɏ��������f��ݒ�
							int xCurrent = xBase + i;
							int yCurrent = yBase + j;

							// ��������
							double distX = std::abs(xCurrent - x0);
							double distY = std::abs(yCurrent - y0);
							// �d�ݕt��
							double weight = 0.0;  // �d�ݕϐ�
												  // �܂���X���W�̋����ŏd�݂�ݒ�
												  // 1�ȉ��A2�ȉ��̂Ƃ��A���ꂼ��d�ݕt��
							if (distX <= 1.0) {
								weight = 1.0 - parameter[0] * distX * distX + parameter[1] * distX * distX * distX;
							}
							else if (distX <= 2.0) {
								weight = parameter[2] + parameter[3] * distX - parameter[4] * distX * distX + RESIZE_PARAMATER * distX * distX * distX;
							}
							else {
								continue;  // �����������Ȃ��̂ŁA���̃��[�v��
							}

							// Y���W�̋����ŏd�݂�ݒ�
							if (distY <= 1.0) {
								weight *= 1.0 - parameter[0] * distY * distY + parameter[1] * distY * distY * distY;
							}
							else if (distY <= 2.0) {
								weight *= parameter[2] + parameter[3] * distY - parameter[4] * distY * distY + RESIZE_PARAMATER * distY * distY * distY;
							}
							else {
								continue;
							}
							// ���ۂɉ�f���擾
							int color_process = instance[yCurrent][xCurrent];

							// ��f��RGB�������A�d�݂������đ������킹��
							color_element += ((color_process >> 0 * 8) & 0xff)* weight;

						}
						// ��f����������
						color_element = (color_element > 255) ? 255
							: (color_element < 0) ? 0
							: color_element;
						color += (int)color_element << i * 8;

					}
				}
				image2[y][x] = color;
			}
		}
		return image2;
	}


	Image convertLinearHist(Image& image1) {
		int a = 255;
		int b = 0;
		int hist[256];
		for (int i = 0; i < 256; i++) {
			hist[i] = 0;
		}
		Image image2(image1.getColsSize(), image1.getRowsSize());

		for (int y = 0; y < image1.getRowsSize(); y++) {
			for (int x = 0; x < image1.getColsSize(); x++) {
				hist[image1[y][x]] ++;
				if (a > image1[y][x])
					a = image1[y][x];
				if (b < image1[y][x])
					b = image1[y][x];
			}
		}
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				image2[y][x] = 0;
				if (image1[y][x] < a) {
					image2[y][x] = 0;
				}
				else if (image1[y][x] > b) {
					image2[y][x] = MAX_BRIGHTNESS;
				}
				else {
					image2[y][x] = (unsigned char)(MAX_BRIGHTNESS * (image1[y][x] - a) / (double)(b - a));
				}
			}
		}
		return image2;
	}

	Image  convertNonLinearHist(Image& image1) {
		/* ���摜 image1 �̃q�X�g�O���������摜�Ƃ���image2 �ɑ�� */
		long int histogram[GRAYLEVEL]; /* �q�X�g�O�����p�z�� */
		long int max_frequency; /* �p�x�̍ő�l */
		int data; /* �p�x��\���O���t�̒��� */
		int a = 255, b = 0;
		int wk[256][256];
		Image image2(image1.getColsSize(), image1.getRowsSize());
		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				image2[y][x] = 0;
				if (image1[y][x] <= MAX_BRIGHTNESS / 2) {
					image2[y][x] = (unsigned char)(2 * MAX_BRIGHTNESS * ((double)image1[y][x] / MAX_BRIGHTNESS) * ((double)image1[y][x] / MAX_BRIGHTNESS));
				}
				else if (image1[y][x] > MAX_BRIGHTNESS / 2) {
					image2[y][x] = (unsigned char)((MAX_BRIGHTNESS / 2) * (1 + sqrt((double)(2 * image1[y][x] - MAX_BRIGHTNESS) / MAX_BRIGHTNESS)));
				}
			}
		}
		return image2;
	}


	Image transHistgram(Image& image1) {
		long int histogram[GRAYLEVEL]; /* �q�X�g�O�����p�z�� */
		long int max_frequency; /* �p�x�̍ő�l */
		int a = 255, b = 0;
		Image image2(image1.getColsSize(), image1.getRowsSize());
		int data; /* �p�x��\���O���t�̒��� */
		int mean = 0, g = 0, flag = 1000000, sub = 0;
		int level[256], value[256];

		/* ���摜�̃q�X�g�O���������߂� */
		for (int i = 0; i < GRAYLEVEL; i++) {
			histogram[i] = 0;
			value[i] = 0;
			level[i] = 0;
		}

		for (int y = 0; y < image1.getRowsSize(); y++) {
			for (int x = 0; image1.getColsSize(); x++) {
				histogram[image1[y][x]] ++;
				if (image1[y][x] == 0)
				{
					//�������Ȃ��Ă悭�ˁH
				}
			}
		}
		g = 256 * 256 / 256;
		int j = 0;
		int k = 0;
		for (int i = 0; i < GRAYLEVEL; i++) {   //�����������Ȃ�����
			mean += histogram[i];
			sub = abs(mean - g);
			if (i == 255) {
				level[j] = i;
				k++;
				break;
			}
			if (flag >= sub) {
				flag = sub;
			}
			else {
				level[j] = i - 1;
				j++;
				mean = 0;
				flag = 1000000;
				k++;
			}
		}

		mean = (int)(256 / (double)k);
		g = mean;
		for (int i = 1; i < k; i++) {
			value[i] = g;
			g += mean;
		}

		for (int y = 0; y < image2.getRowsSize(); y++) {
			for (int x = 0; x < image2.getColsSize(); x++) {
				for (int i = 0; i < k; i++) {
					if (level[i] >= image1[y][x]) { //���R��
						image2[y][x] = value[i];
						break;
					}
				}
			}
		}
		return image2;
	}

	Image normalizeFilter(Image& image) {
		Image result(image.getColsSize(), image.getRowsSize());
		/* �K�p����t�B���^�̒�`�i3x3��8�ߖT���`������) */
		int weight[3][3] = {
			{ 1,  1,  1 },
			{ 1,  2,  1 },
			{ 1,  1,  1 } };
		double div_const = 10.0; /* <== �Ō�Ɋ���l */
		double new_value;        /* ������̊K���l */
		/* image2[y][x] �̏����� */
		for (int y = 0; y < image.getRowsSize(); y++)
			for (int x = 0; x < image.getColsSize(); x++)
				result[y][x] = result[y][x];
		/* �t�B���^�����O���s�� */
		for (int y = 1; y < image.getRowsSize() - 1; y++)
			for (int x = 1; x < image.getColsSize() - 1; x++) {
				new_value = 0.0;
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
						new_value = new_value +
						weight[i + 1][j + 1] * image[y + i][x + j];
				result[y][x] = (unsigned char)(new_value / div_const);
			}

		return result;

	}

	int sort(int* work) {
		int l, z, k, z1;

		for (k = 1; k < 9; k++) {
			z = work[k];
			for (l = k; l > 0; l--) {
				if (z < work[l - 1]) {
					z1 = work[l - 1];
					work[l - 1] = z;
					work[l] = z1;
				}
			}
		}
		return (unsigned char)work[4];
	}



	Image median_filter(Image& image)
	{
		Image result(image.getColsSize(), image.getRowsSize());
		/* �K�p����t�B���^�̒�`�i3x3��8�ߖT���`������) */
		int work[9];
		/* image2[y][x] �̏����� */
		for (int y = 0; y < image.getRowsSize(); y++)
			for (int x = 0; x < image.getColsSize(); x++)
				result[y][x] = image[y][x];
		/* �t�B���^�����O���s�� */
		for (int y = 1; y < image.getRowsSize() - 1; y++)
			for (int x = 1; x < image.getColsSize() - 1; x++) {

				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
						work[(j + 1) + (i + 1) * 3] = image[y + i][x + j];
				result[y][x] = sort(work);
			}
		return result;
	}


	Image affectSobelFilter(Image& image) {

		Image result(image.getColsSize(), image.getRowsSize());
		//�\�[�x���t�B���^�̃J�[�l��

		//�ꉞ�|���̂ŏ�����
		for (int y = 0; y < result.getRowsSize(); y++)
			for (int x = 0; x < result.getColsSize(); x++)
				result[y][x] = 0;

		//��������
		int sobel[][3] = {
			{-1,0,1},
			{-2,0,2},
			{-1,0,1}
		};

		//��������
		//int sobel[][3] = {
		//{-1,-2,-1},
		//{0,0,0},
		//{1,2,1}
		//};

		for (int y = 1; y < image.getRowsSize() - 1; y++) {
			for (int x = 1; x < image.getColsSize() - 1; x++) {
				//index�G���[���p
				constexpr int bias = 1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						result[y][x] += sobel[i + bias][j + bias] * image[y + i][x + j];
					}
				}
			}
		}
		return result;
	}

	Image affectLaplacianFilter(Image& image) {

		Image result(image.getColsSize(), image.getRowsSize());
		//�\�[�x���t�B���^�̃J�[�l��

		//�ꉞ�|���̂ŏ�����
		for (int y = 0; y < result.getRowsSize(); y++)
			for (int x = 0; x < result.getColsSize(); x++)
				result[y][x] = 0;

		int laplacian[][3] = {
			{0,1,0},
			{1,-4,1},
			{0,1,0}
		};

		for (int y = 1; y < image.getRowsSize() - 1; y++) {
			for (int x = 1; x < image.getColsSize() - 1; x++) {

				//index�G���[���p
				constexpr int bias = 1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						result[y][x] += laplacian[i + bias][j + bias] * image[y + i][x + j];
					}
				}
			}
		}
		return result;
	}


	Image affectRadicalizeFilter(Image& image) {

		Image result(image.getColsSize(), image.getRowsSize());
		//�\�[�x���t�B���^�̃J�[�l��

		//�ꉞ�|���̂ŏ�����
		for (int y = 0; y < result.getRowsSize(); y++)
			for (int x = 0; x < result.getColsSize(); x++)
				result[y][x] = 0;

		int radicalize[][3] = {
			{0,-1,0},
			{-1,5,-1},
			{0,-1,0}
		};

		for (int y = 1; y < image.getRowsSize() - 1; y++) {
			for (int x = 1; x < image.getColsSize() - 1; x++) {

				//index�G���[���p
				constexpr int bias = 1;
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						result[y][x] += radicalize[i + bias][j + bias] * image[y + i][x + j];
					}
				}
			}
		}
		return result;
	}

	Image threshold(Image& instance, int thresh)
	{
		Image result(instance.getColsSize(), instance.getRowsSize());

		//thresh�̗̈�`�F�b�N
		thresh = thresh < 0 ? 0 : thresh > 255 ? 255 : thresh;
		int x, y = 0;
#pragma omp parallel for private(y,x)
		for (y = 0; y < instance.getRowsSize(); y++)
		{
			for (x = 0; x < instance.getColsSize(); x++)
			{
				if (instance[y][x] < thresh)
				{
					result[y][x] = 0;
				}
				else
				{
					result[y][x] = 255;
				}
			}
		}
		return result;
	}

	Image adaptiveThreshold(Image& instance, int blockSize, int bias)
	{
		Image result(instance.getColsSize(), instance.getRowsSize());
		double ave = 0.0;
		int x, y = 0;
#pragma omp parallel for private(y,x)
		for (y = blockSize; y < result.getRowsSize() - blockSize; y++)
		{
			for (x = blockSize; x < result.getColsSize() - blockSize; x++)
			{
				ave = 0.0;
				for (int i = y - blockSize; i < y + blockSize; i++)
				{
					for (int j = x - blockSize; j < x + blockSize; j++)
					{
						if (i == y && j == x)continue;
						ave += instance[i][j];
					}
				}

				auto tmp = std::pow((2 * blockSize + 1), 2) - 1;
				ave /= static_cast<int>(tmp);

				ave = instance[y][x] - ave <= 0 ?
					(ave - bias >= 0 ? ave - bias : ave)
					:
					(ave + bias < 256 ? ave + bias : ave);

				if (instance[y][x] < ave)
				{
					result[y][x] = 0;
				}
				else
				{
					result[y][x] = 255;
				}
			}
		}

		return result;
	}

	Image expansion(Image& instance)
	{
		auto binary = threshold(instance, 96);
		Image result(instance.getColsSize(), instance.getRowsSize());

		int x, y = 0;
#pragma omp parallel for private(y,x)
		for (y = 1; y < result.getRowsSize() - 1; y++)
		{
			for (x = 1; x < result.getColsSize() - 1; x++)
			{

				for (int i = y - 1; i < y + 2; i++)
				{
					for (int j = x - 1; j < x + 2; j++)
					{

						if (binary[y][x] != 0 && !(i == x && j == y))
						{
							result[y][x] = 255;
							break;
						}
					}
				}
			}
		}
		return result;
	}

	Image contraction(Image& instance)
	{
		auto binary = threshold(instance, 100);
		Image result(binary.getColsSize(), binary.getRowsSize());

		int x, y = 0;

#pragma omp parallel for private(y,x)
		for (y = 1; y < result.getRowsSize() - 1; y++)
		{
			for (x = 1; x < result.getColsSize() - 1; x++)
			{
				result[y][x] = 255;
				for (int i = y - 1; i < y + 2; i++)
				{
					for (int j = x - 1; j < x + 2; j++)
					{
						if (binary[y][x] == 0 && !(i == x && j == y))
						{
							result[y][x] = 0;
							break;
						}
					}
				}
			}
		}
		return result;
	}

}