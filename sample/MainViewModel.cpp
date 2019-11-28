#include"stdafx.h"
#include"Image.h"
#include"imageDispatcher.h"
#include"MainViewModel.hpp"


MainViewModel::MainViewModel(ImageDispatcher &dispatcher) {
	auto sender = dispatcher;
	sender.addObserver(this); // Observer“o˜^
	sender.doSomething();
};