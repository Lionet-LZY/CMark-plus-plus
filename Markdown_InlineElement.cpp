// Markdown_InlineElement.cpp：行内元素语法实现

#include"Markdown_InlineElement.h"

Markdown_InlineElement::Markdown_InlineElement(InlineType T,const std::string& t):type(T),text(t){}
InlineType Markdown_InlineElement::getType()const {
	return type;
}
const std::string& Markdown_InlineElement::getText()const {
	return text;
}