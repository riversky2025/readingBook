#pragma once
#include <iostream>
#include <thread>
#include "AbstrctDemo.h"
using namespace std;
class Listing11 :
	public Demo {
public:
	void hello() {
		cout << "hello Concurrent world" << endl;
	}
	void run() override {
		thread t([this]() {
			this->hello();
		});
		t.join();
	}
};
