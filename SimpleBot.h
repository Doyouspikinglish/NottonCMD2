#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <sstream>

void BOTmain() {
	std::unordered_map<std::string, std::string> botansw{
		{"hi", "hello"},
		{"what is your name", "my name is restricted SimpleBot"},
		{"how are you","im good, thanks"},
		{"are you an A.I ?","kind of but i am a restricted Bot"},
		{"what are you ?","A restricted AI (Bot)"},
		{"doner","kebap"},
		{"what's 1 + 1", "2"},
		{"kebap","doner"},
		{"what is C++","it is a complex (low-level) programming language"},
		{"123","456"},
		{"what is Windows","an OS, popular one"},
		{"what", "what"},
		{"no", "ok"},
		{"yes", "ok"},
		{"is this in english ?", "01111001 01100101 01110011"},
		{"how can i quit ?", "Type quit"},
		{"how to quit ?", "Type quit"}
	};

	std::string rrcc;
	while (true) {
		std::cout << "you:";
		std::getline(std::cin, rrcc);
		std::transform(rrcc.begin(), rrcc.end(), rrcc.begin(), ::tolower);

		if (rrcc == "quit") { break; }

		if (botansw.count(rrcc)) {
			std::cout << "bot: " << botansw[rrcc] << "\n";
		}
		else {
			std::cout << "bot: " << "what\n";
		}
		
	}
	
}