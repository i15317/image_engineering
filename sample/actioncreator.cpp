#include"stdafx.h"
#include"Image.h"
#include"imageDispatcher.h"
#include"actioncreator.hpp"


void MainActionCreator::loadImage() {
	//アクションを発火する
	__mDispatcher.dispatch();
}