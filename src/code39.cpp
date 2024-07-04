#include <string>
#include <iostream>
#include <unordered_map>
#include "code39.h"
#include "imgGenerator.h"

std::unordered_map<std::string, std::wstring> code39Encodeing = {
	{"1", L"▮| ||▮"},
	{"A", L"▮|| |▮"},
	{"K", L"▮||| ▮"},
	{"U", L"▮ |||▮"},
	{"2", L"|▮ ||▮"},
	{"B", L"|▮| |▮"},
	{"L", L"|▮|| ▮"},
	{"V", L"| ▮||▮"},
	{"3", L"▮▮ |||"},
	{"C", L"▮▮| ||"},
	{"M", L"▮▮|| |"},
	{"W", L"▮ ▮|||"},
	{"4", L"|| ▮|▮"},
	{"D", L"||▮ |▮"},
	{"N", L"||▮| ▮"},
	{"X", L"| |▮|▮"},
	{"5", L"▮| ▮||"},
	{"E", L"▮|▮ ||"},
	{"O", L"▮|▮| |"},
	{"Y", L"▮ |▮||"},
	{"6", L"|▮ ▮||"},
	{"F", L"|▮▮ ||"},
	{"P", L"|▮▮| |"},
	{"Z", L"| ▮▮||"},
	{"7", L"|| |▮▮"},
	{"G", L"||| ▮▮"},
	{"Q", L"|||▮ ▮"},
	{"-", L"| ||▮▮"},
	{"8", L"▮| |▮|"},
	{"H", L"▮|| ▮|"},
	{"R", L"▮||▮ |"},
	{".", L"▮ ||▮|"},
	{"9", L"|▮ |▮|"},
	{"I", L"|▮| ▮|"},
	{"S", L"|▮|▮ |"},
	{" ", L"| ▮|▮|"},
	{"0", L"|| ▮▮|"},
	{"J", L"||▮ ▮|"},
	{"T", L"||▮▮ |"},
	{"*", L"| |▮▮|"},
	{"$", L"| | | ||"},
	{"/", L"| | || |"},
	{"+", L"| || | |"},
	{"%", L"|| | | |"}
};

int Code39Standard(const std::string& input, const std::string& path) {
	std::wstring data = L"";
	data += code39Encodeing.at("*");
    for (char c : input) {
        try {
            data += code39Encodeing.at(std::string(1, c));
        } catch (const std::out_of_range& e) {
            std::cerr << "Invalid character: " << c << std::endl;
            return 1;
        }
    }
    data += code39Encodeing.at("*");
    generateCode39IMG(data, path, input);
    return 0;
}

int Code39Raw(const std::string& input, const std::string& path) {
	std::wstring data = L"";
    for (char c : input) {
        try {
            data += code39Encodeing.at(std::string(1, c));
        } catch (const std::out_of_range& e) {
            std::cerr << "Invalid character: " << c << std::endl;
            return 1;
        }
    }
    generateCode39IMG(data, path, input);
    return 0;
}