// Markdown_Parser.h：语法解析定义

#pragma once
#include <string>
#include <vector>
#include "Markdown_BlockElement.h"
#include "Markdown_InlineElement.h"

class Markdown_Parser {
public:
	std::vector<std::vector<std::string>> RawBlock;
	void split(const std::string& RawText);
	std::vector<Markdown_InlineElement> inline_parse(const std::string& RawText, std::string& ResText);
	// std::vector<Markdown_BlockElement> block_parse();
};