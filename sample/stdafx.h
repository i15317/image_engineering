// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once
/* �萔�錾 */
constexpr int  MAX_IMAGESIZE = 1024;/* �z�肷��c�E���̍ő��f�� */
constexpr int  MAX_BRIGHTNESS = 255; /* �z�肷��ő�K���l */
constexpr int  GRAYLEVEL = 256; /* �z�肷��K����(=�ő�K���l+1) */
constexpr int  MAX_FILENAME = 256; /* �z�肷��t�@�C�����̍ő咷 */
constexpr int  MAX_BUFFERSIZE = 256; /* ���p����o�b�t�@�ő咷 */
constexpr double  RESIZE_PARAMATER = -1;

//���s����
constexpr char br = '\n';
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include<cstdlib>
#include"observe.hpp"
#include<cmath>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������
#include<limits>
#include<iostream>
#include<memory>
#include<array>
#include<thread>
#include<string>
#include<vector>
#include<thread>
#include<algorithm>
#include<queue>
#include<stack>
#include<functional>
#include<complex>
#include<numeric>
