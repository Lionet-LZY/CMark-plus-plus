// Markdown_Parser.h£ºÓï·¨½âÎö

#pragma once
#include <string>
#include <vector>
#include "Markdown_BlockElement.h"
#include "Markdown_InlineElement.h"

class Markdown_Parser {
public:
	std::vector<Markdown_BlockElement> parse(const std::string md_text);
};