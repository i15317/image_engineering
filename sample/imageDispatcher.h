#pragma once

//https://qiita.com/a-beco/items/717d6dff5355776e3702

class ImageDispatcher : public Observer::observable<ImageDispatcher> {
public:
	void dispatch();
	// Sender��key1��key2��2��ނ̒ʒm������
	static const std::string key1;
	static const std::string key2;

	// doSomething()�Œʒm
	void doSomething() {
		notify(key1);
		notify(key2);
	}
};