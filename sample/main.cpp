// sample.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include"class.hpp"
#include"Image.h"
#include"mLogic.h"

int main()
{
	/*
	只今工事中。そのうちロジックとビューを切り離します。
	Flux的なデータフローを実装中
	C++でオブジェクト指向を書くのはつらい・・・・・
	*/
	Image instance;
	mLogic logic;
	instance.load_image_data();	/* 画像データを image1 に読み込む */
	//Image hoge1 = logic.convertResolution(instance, 3); 		/* image1 のデータをそのまま image2 へ */
	//Image hoge2 = logic.convertTone(instance, 2);
	//Image hoge3 = logic.neighborMethod(instance, 2);
	//Image hoge4 = logic.linearResize(instance, 2);
//	Image hoge = logic.adaptiveThreshold(instance, 3, 16);
	//Image hoge = logic.expansion(instance);
	Image hoge = logic.contraction(instance);
//Image hoge = logic.threshold(instance, 96);
	//logic.save_image_data(hoge1);	/* image2 を保存する */
	//logic.save_image_data(hoge2);	/* image2 を保存する */
	//logic.save_image_data(hoge3);	/* image2 を保存する */
	//logic.save_image_data(hoge4);	/* image2 を保存する */
	logic.save_image_data(hoge);
	return 0;
}