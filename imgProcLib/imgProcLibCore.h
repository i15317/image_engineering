#pragma once

//�摜�̕ϊ�����

namespace ImgProcLib {
	//�O���錾
	class Image;

	/*
	Image�N���X�����Ɏ�荞�݂����@�\
	*/

	//�摜�̃R�s�[ Todo: �񐄏����悱����
	Image copy_image(Image instance);
	//�摜�ɔC�ӂ̗ʂ����Z����
	Image add_image(Image instance);
	//�摜�̔��]
	Image inverseImage(Image instance);
	//�摜�̃��T�C�Y
	Image resizeImage(Image& instance, double mag);
	//�摜�̃��T�C�Y
	Image linearResize(Image& instance, double mag);
	////////////////////////////////////////////////////////////////////////////////////////////////

	//���U�C�N
	Image convertResolution(Image& instance, int magnificationValue);
	//��������H
	Image neighborMethod(Image& instance, double mag);

	//�K�����ϊ�
	Image convertTone(Image& instance, int n);
	//�K�����ϊ��i�f�t�H���g�j
	Image convertTone(Image& instance);

	//���`�q�X�g�O����
	Image convertLinearHist(Image& instance);
	//����`�q�X�g�O�����ϊ�
	Image convertNonLinearHist(Image& instance);
	//��������H
	Image transHistgram(Image& instance);
	//���K���t�B���^
	Image normalizeFilter(Image&);
	Image median_filter(Image& instance);

	//�����t�B���^
	Image affectSobelFilter(Image& instance);
	Image affectLaplacianFilter(Image& instance);
	Image affectRadicalizeFilter(Image& image);

	//��l��
	Image threshold(Image& instance, int thresh);
	Image adaptiveThreshold(Image& instance, int blockSize, int thresh);

	Image expansion(Image& instance);
	Image contraction(Image& instance);

}
