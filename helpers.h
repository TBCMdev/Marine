#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "lexertk.hpp"
#include "Base.h"
namespace marine {
#pragma region helpers
	static bool isOp(lexertk::token& t) {
		if (t.value == "+" ||
			t.value == "-" ||
			t.value == "*" ||
			t.value == "/" ||
			t.value == "%" ||
			t.value == "+=" ||
			t.value == "-=" ||
			t.value == "*=" ||
			t.value == "/=" ||
			t.value == "%=") return true;
		else {
			return false;
		}
	}
	static bool isLogicalOp(lexertk::token& t) {
		if (t.value == "==" ||
			t.value == "!=" ||
			t.value == ">=" ||
			t.value == "<=") return true;
		else return false;
	}
	static bool isAndOrOp(lexertk::token& t) {
		if (t.value == "and" || t.value == "or" || t.value == "&&" || t.value == "||") return true;
		return false;
	}
	static bool isFloat(lexertk::token& t) {
		bool dec = false;
		for (char c : t.value) {
			if (std::string("0123456789").find(c) == std::string::npos) return false;
			if (!dec && c == '.') dec = true;
			else if (dec) return false;
		}
		if (!dec) return false;
		return true;
	}
	static bool isString(lexertk::token& s) {
		std::cout << "first:" << s.value[0] << "last: " << s.value.back() << std::endl;
		if ((s.value[0] != '"' && s.value[0] != '\'') || (s.value.back() != '"' && s.value.back() != '\'')) return false;
		return true;
	}
	static bool isBool(lexertk::token& t) {
		if (t.value == "true" || t.value == "false") return true;
	}
	static bool isInt(lexertk::token& t) {
		for (char c : t.value) {
			if (std::string("0123456789").find(c) == std::string::npos) return false;
			if (c == '.') return false;
		}
		return true;
	}
	namespace out {
		enum class STATUS {
			ERR,
			WARN,
			GOOD
		};

		/*
		#define color_black      0
		#define color_dark_blue  1
		#define color_dark_green 2
		#define color_light_blue 3
		#define color_dark_red   4
		#define color_magenta    5
		#define color_orange     6
		#define color_light_gray 7
		#define color_gray       8
		#define color_blue       9
		#define color_green     10
		#define color_cyan      11
		#define color_red       12
		#define color_pink      13
		#define color_yellow    14
		#define color_white     15
		*/
		static void WINDCol(STATUS s) {
			static HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (s) {
			case STATUS::ERR:
				SetConsoleTextAttribute(hwnd, 12);
			case STATUS::WARN:
				SetConsoleTextAttribute(hwnd, 14);
			case STATUS::GOOD:
				SetConsoleTextAttribute(hwnd, 10);

			}
		}
		static void WINDReset() {
			static HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hwnd, 15);
		}
		static void stpr(const char* c, STATUS s) {
			WINDCol(s);
			std::cout << c << std::endl;
			WINDReset();
		}
		static void st_spr(std::string& c, STATUS s) {
			WINDCol(s);
			std::cout << c << std::endl;
			WINDReset();
		}
	};
#pragma endregion
}