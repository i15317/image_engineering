#pragma once
class MainActionCreator {
public:
	//インスタンスは外部注入
	MainActionCreator(ImageDispatcher &dispatcher) {
		__mDispatcher = dispatcher;
	}
	void loadImage();
private:
	ImageDispatcher __mDispatcher;
};