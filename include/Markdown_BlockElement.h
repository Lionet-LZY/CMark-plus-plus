// Markdown_BlockElement.h����Ԫ���﷨����

#pragma once
#include <string>
#include <vector>
#include "Markdown_InlineElement.h"

// ö���﷨����
enum class BlockType {
	Paragraph,
	Headinglevel1,
	Headinglevel2,
	Headinglevel3,
	HorizontalRules,
	CodeBlocks,
	BlockQuote,
	OrderedList,
	UnorderedList
};

class Markdown_BlockElement {
private:
	BlockType type;
	std::string text;
	std::vector<Markdown_InlineElement> InlineElement;
public:
	Markdown_BlockElement(BlockType T, const std::string& t, std::vector<Markdown_InlineElement> InlElem);
	BlockType getType() const;
	const std::string& getText() const;
};
