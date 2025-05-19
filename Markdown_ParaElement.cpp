//块元素Markdown语法实现
#include"Markdown_ParaElement.h"
Markdown_ParaElement::Markdown_ParaElement(ParaType T,const std::string&t):type(T),text(t){}
ParaType Markdown_ParaElement::getType()const {
	return type;
}
const std::string& Markdown_ParaElement::getText()const {
	return text;
}