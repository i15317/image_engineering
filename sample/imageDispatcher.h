#pragma once

//https://qiita.com/a-beco/items/717d6dff5355776e3702

class ImageDispatcher : public Observer::observable<ImageDispatcher> {
public:
	void dispatch();
	// Senderはkey1とkey2の2種類の通知をする
	static const std::string key1;
	static const std::string key2;

	// doSomething()で通知
	void doSomething() {
		notify(key1);
		notify(key2);
	}
};