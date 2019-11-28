#pragma once

//viewコントロールクラス（コンソール版）
class View {
public:
	//コンストラクタ
	View() {};
	void show_message(const std::string& message);
	void show_message(const std::vector < std::string > &message);
	std::string inputFromConsole();
	//データコンバーター
	MainViewModel model;
private:
	std::string __input_data;
};