// Markdown_BlockElement.cpp：块元素语法实现

#include"Markdown_BlockElement.h"

Markdown_BlockElement::Markdown_BlockElement(BlockType T, const std::string& t) :type(T), text(t) {};
BlockType Markdown_BlockElement::getType()const {
	return type;
}
const std::string& Markdown_BlockElement::getText()const {
	return text;
}