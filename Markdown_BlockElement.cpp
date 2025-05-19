//块元素 Markdown 语法实现

#include"Markdown_BlockElement.h"

Markdown_BlockElement::Markdown_BlockElement(BlockType T, const std::string& t) :type(T), text(t) {};
BlockType Markdown_BlockElement::getType()const {
	return type;
}