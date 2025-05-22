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
	std::vector<Markdown_InlineElement> inline_parse(const std::string& RawText, std::string& ResText, size_t begin_ins, size_t end_ins);
};