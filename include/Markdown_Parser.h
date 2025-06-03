// Markdown_Parser.h���﷨��������

#pragma once
#include <string>
#include <vector>
#include "Markdown_BlockElement.h"
#include "Markdown_InlineElement.h"

class Markdown_Parser {
public:
	std::vector<std::vector<std::string>> RawBlock;
	void split(const std::string& RawText);
	std::vector<Markdown_InlineElement> inline_parse(const std::string& RawText, std::string& ResText, size_t begin_ins, size_t end_ins);
	// std::vector<Markdown_BlockElement> block_parse();
};