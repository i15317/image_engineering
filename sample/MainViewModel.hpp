#pragma once
//https://qiita.com/a-beco/items/717d6dff5355776e3702

class MainViewModel : public Observer::Observer<ImageDispatcher, ImageDispatcher::key1>
{
public:
	//�R���X�g���N�^�ŃC���X�^���X�𒍓�
	MainViewModel(ImageDispatcher &dispatcher);
	//�摜�f�[�^
	Image image;
	//C++�Ŕ񓯊������͔߂������ƂɂȂ�̂œ��������Ŏ���
	//Image image = dispatcher.onLoadImage();

	const std::string ImageDispatcher::key1 = "key1";
	const std::string ImageDispatcher::key2 = "key2";


	// �ʒm���󂯎��ƌĂ΂��
	void update(ImageDispatcher* sender, const std::string& key) override {
		std::cout << "received!" << std::endl;
	}
private:


};