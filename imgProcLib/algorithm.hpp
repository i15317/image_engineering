#pragma once
//////
//////
/*
�A���S���Y���܂Ƃ�
*/
//////
//////

//�o�b�t�@�I�[�o�[�����΍�
int checkMemoryRange(int x, int y);
//��苭�͂ȃo�b�t�@�I�[�o�[�����΍�
int forceRangeAdjust(int n, int index);
////////////////////
////////////////////
//�𑜓x�ϊ�
////////////////////
////////////////////

//�摜�z��̕��ϒl���v�Z
long double caculateAveragePixels(std::vector<std::vector<unsigned char>>data);

//�ʎq��
int quantizeNum(int binds, int num, int value);



//�A�t�B���ϊ��̕\���s���Ԃ�
std::vector < std::vector< long double >> affineMatrix(long double angle, long double mag);