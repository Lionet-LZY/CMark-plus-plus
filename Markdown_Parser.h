// Markdown_Parser.h：语法解析定义

#pragma once
#include <string>
#include <vector>
#include "Markdown_BlockElement.h"
#include "Markdown_InlineElement.h"

class Markdown_Parser {
private:
	std::vector<std::vector<std::string>> RawBlock;
public:
	void split(const std::string& RawText);
};