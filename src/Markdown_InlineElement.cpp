// Markdown_InlineElement.cpp：行内元素语法实现

#include "Markdown_InlineElement.h"

Markdown_InlineElement::Markdown_InlineElement()
	: type(InlineType::Null), begin(0), end(0) {
}
Markdown_InlineElement::Markdown_InlineElement(InlineType T, size_t b, size_t e)
	: type(T), begin(b), end(e) {}
InlineType Markdown_InlineElement::getType() const {
	return type;
}
size_t Markdown_InlineElement::getBegin() const { 
	return begin; 
}
