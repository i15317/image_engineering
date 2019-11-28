#pragma once
//////
//////
/*
アルゴリズムまとめ
*/
//////
//////

//バッファオーバーラン対策
int checkMemoryRange(int x, int y);
//より強力なバッファオーバーラン対策
int forceRangeAdjust(int n, int index);
////////////////////
////////////////////
//解像度変換
////////////////////
////////////////////

//画像配列の平均値を計算
long double caculateAveragePixels(std::vector<std::vector<unsigned char>>data);

//量子化
int quantizeNum(int binds, int num, int value);



//アフィン変換の表現行列を返す
std::vector < std::vector< long double >> affineMatrix(long double angle, long double mag);