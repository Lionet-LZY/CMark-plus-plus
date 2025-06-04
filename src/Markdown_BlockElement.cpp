// Markdown_BlockElement.cpp：块元素语法实现

#include "Markdown_BlockElement.h"

Markdown_BlockElement::Markdown_BlockElement(BlockType t, std::vector<LineElement>T)
	: type(t), Text(T) {}

BlockType Markdown_BlockElement::getType() const {
	return type;
}

std::vector<LineElement> Markdown_BlockElement::getText() const {
	return Text;
}