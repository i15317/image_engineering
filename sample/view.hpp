#pragma once

//view�R���g���[���N���X�i�R���\�[���Łj
class View {
public:
	//�R���X�g���N�^
	View() {};
	void show_message(const std::string& message);
	void show_message(const std::vector < std::string > &message);
	std::string inputFromConsole();
	//�f�[�^�R���o�[�^�[
	MainViewModel model;
private:
	std::string __input_data;
};