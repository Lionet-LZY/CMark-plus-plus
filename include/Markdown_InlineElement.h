// Markdown_InlineElement.h������Ԫ���﷨����

#pragma once
#include <string>

enum class InlineType {
	Bold,
	Italic,
	BoldItalic,
	Code
};

class Markdown_InlineElement {
private:
	InlineType type;
	size_t begin;
	size_t end;
public:
	Markdown_InlineElement(InlineType T, size_t b, size_t e);
	InlineType getType() const;
	size_t getBegin() const;
};