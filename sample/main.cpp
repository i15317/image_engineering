// sample.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include"class.hpp"
#include"Image.h"
#include"mLogic.h"

int main()
{
	/*
	�����H�����B���̂������W�b�N�ƃr���[��؂藣���܂��B
	Flux�I�ȃf�[�^�t���[��������
	C++�ŃI�u�W�F�N�g�w���������̂͂炢�E�E�E�E�E
	*/
	Image instance;
	mLogic logic;
	instance.load_image_data();	/* �摜�f�[�^�� image1 �ɓǂݍ��� */
	//Image hoge1 = logic.convertResolution(instance, 3); 		/* image1 �̃f�[�^�����̂܂� image2 �� */
	//Image hoge2 = logic.convertTone(instance, 2);
	//Image hoge3 = logic.neighborMethod(instance, 2);
	//Image hoge4 = logic.linearResize(instance, 2);
//	Image hoge = logic.adaptiveThreshold(instance, 3, 16);
	//Image hoge = logic.expansion(instance);
	Image hoge = logic.contraction(instance);
//Image hoge = logic.threshold(instance, 96);
	//logic.save_image_data(hoge1);	/* image2 ��ۑ����� */
	//logic.save_image_data(hoge2);	/* image2 ��ۑ����� */
	//logic.save_image_data(hoge3);	/* image2 ��ۑ����� */
	//logic.save_image_data(hoge4);	/* image2 ��ۑ����� */
	logic.save_image_data(hoge);
	return 0;
}