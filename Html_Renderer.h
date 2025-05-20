//打入html标签定义
#pragma once

#include<string>
#include"Markdown_BlockElement.h"

class html {
private:
	std::string htext;
public:
	//为块元素语法部分打入html标签
	void input_htext(Markdown_BlockElement a);
};