#pragma once

//�摜�̕ϊ�����
class mLogic {
public:
	mLogic() {}
	///* �֐��̃v���g�^�C�v�錾 */
	void save_image_data(Image& instance); /* �摜�������ݗp�֐� */
	void save_image_data(Image& instance, std::string filename);
	Image copy_image(Image instance);
	Image add_image(Image instance);
	//�摜�̔��]
	Image inverseImage(Image instance);
	//�摜�T�C�Y�̕ύX
	//Image resizeImage(Image instance);
	//���U�C�N
	Image convertResolution(Image& instance, int magnificationValue);
	Image resizeImage(Image& instance, double mag);
	Image linearResize(Image& instance, double mag);
	Image neighborMethod(Image& instance, double mag);
	//�K�����ϊ��i�f�t�H���g�j
	Image convertTone(Image& instance) { return convertTone(instance, 4); }
	Image convertTone(Image& instance, int n);
	//���`�q�X�g�O����
	Image convertLinearHist(Image& instance);
	Image convertNonLinearHist(Image& instance);
	Image transHistgram(Image& instance);
	Image normalizeFilter(Image&);
	Image median_filter(Image& instance);
	//�A�t�B���ϊ�
	//Image affineTransform(Image & instance);
	//Image affineTransform(Image & instance, long double angle);
	//Image affineTransform(Image & instance, long float mag);
	//Image affineTransform(Image & instance, long double angle, long double mag);

	//�����t�B���^
	Image affectSobelFilter(Image& instance);
	Image affectLaplacianFilter(Image& instance);
	Image affectRadicalizeFilter(Image& image);

	//��l��
	Image threshold(Image& instance, int thresh);
	Image adaptiveThreshold(Image& instance, int blockSize, int thresh);

	Image expansion(Image& instance);
	Image contraction(Image& instance);


};


