#pragma once
class MainActionCreator {
public:
	//�C���X�^���X�͊O������
	MainActionCreator(ImageDispatcher &dispatcher) {
		__mDispatcher = dispatcher;
	}
	void loadImage();
private:
	ImageDispatcher __mDispatcher;
};