// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once
/* 定数宣言 */
constexpr int  MAX_IMAGESIZE = 1024;/* 想定する縦・横の最大画素数 */
constexpr int  MAX_BRIGHTNESS = 255; /* 想定する最大階調値 */
constexpr int  GRAYLEVEL = 256; /* 想定する階調数(=最大階調値+1) */
constexpr int  MAX_FILENAME = 256; /* 想定するファイル名の最大長 */
constexpr int  MAX_BUFFERSIZE = 256; /* 利用するバッファ最大長 */
constexpr double  RESIZE_PARAMATER = -1;

//改行文字
constexpr char br = '\n';
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include<cstdlib>
#include"observe.hpp"
#include<cmath>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください
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
