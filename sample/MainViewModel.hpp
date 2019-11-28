#pragma once
//https://qiita.com/a-beco/items/717d6dff5355776e3702

class MainViewModel : public Observer::Observer<ImageDispatcher, ImageDispatcher::key1>
{
public:
	//コンストラクタでインスタンスを注入
	MainViewModel(ImageDispatcher &dispatcher);
	//画像データ
	Image image;
	//C++で非同期処理は悲しいことになるので同期処理で実装
	//Image image = dispatcher.onLoadImage();

	const std::string ImageDispatcher::key1 = "key1";
	const std::string ImageDispatcher::key2 = "key2";


	// 通知を受け取ると呼ばれる
	void update(ImageDispatcher* sender, const std::string& key) override {
		std::cout << "received!" << std::endl;
	}
private:


};