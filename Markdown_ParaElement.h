//块元素Markdown语法定义
#pragma once
#include<string>
enum class ParaType {

};
class Markdown_ParaElement {
private:
	ParaType type;
	std::string text;
public:
	Markdown_ParaElement(ParaType T, const std::string& t);
	ParaType getType()const;
	const std::string& getText()const;
};