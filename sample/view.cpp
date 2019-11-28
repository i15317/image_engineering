#include"stdafx.h"
#include"MainViewModel.hpp"
#include"view.hpp"


void View::show_message(const std::string& message) {
	std::cout << message << br;
}

void View::show_message(const std::vector<std::string>&messages) {
	for (auto message : messages) {
		show_message(message);
	}
}
