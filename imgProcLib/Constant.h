#pragma once
/* 定数宣言 */
constexpr int  MAX_IMAGESIZE = 1024;/* 想定する縦・横の最大画素数 */
constexpr int  MAX_BRIGHTNESS = 255; /* 想定する最大階調値 */
constexpr int  GRAYLEVEL = 256; /* 想定する階調数(=最大階調値+1) */
constexpr int  MAX_FILENAME = 256; /* 想定するファイル名の最大長 */
constexpr int  MAX_BUFFERSIZE = 256; /* 利用するバッファ最大長 */
constexpr double  RESIZE_PARAMATER = -1;
constexpr char br = '\n';