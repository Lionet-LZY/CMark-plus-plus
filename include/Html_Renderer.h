// html 标签渲染定义
#pragma once

#include <string>
#include "Markdown_BlockElement.h"
#include "Markdown_InlineElement.h"

class Html_Renderer {
private:
	std::string HtmlText = "";
	std::string Style_css;
public:
	void SetStyle(std::string filename);
	void Init();
	void Tail();
	// 为块元素语法部分渲染 html 标签
	void BlockHtml(Markdown_BlockElement BlockElem);
	// 为行内元素语法部分渲染 html 标签
	std::string InlineHtml(LineElement Line);
	std::string getHtml() const;
};