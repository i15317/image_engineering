#pragma once

//https://qiita.com/a-beco/items/717d6dff5355776e3702

class ImageDispatcher : public Observer::observable<ImageDispatcher> {
public:
	void dispatch();
	// Sender‚Íkey1‚Ækey2‚Ì2Ží—Þ‚Ì’Ê’m‚ð‚·‚é
	static const std::string key1;
	static const std::string key2;

	// doSomething()‚Å’Ê’m
	void doSomething() {
		notify(key1);
		notify(key2);
	}
};