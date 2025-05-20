// Markdown_InlineElement.h：行内元素语法定义

#pragma once
#include <string>

enum class InlineType {
	Bold,
	Italic,
	BoldItalic,
	EscapingBackticks
};

class Markdown_InlineElement {
private:
	InlineType type;
	std::string text;
public:
	Markdown_InlineElement(InlineType T, const std::string& t);
	InlineType getType()const;
	const std::string& getText()const;
};