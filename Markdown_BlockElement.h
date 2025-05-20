// Markdown_BlockElement.h：块元素语法定义

#pragma once
#include <string>

// 枚举语法类型
enum class BlockType {
	Paragraph,
	Headinglevel1,
	Headinglevel2,
	Headinglevel3,
	HorizontalRules
};

class Markdown_BlockElement {
private:
	BlockType type;
	std::string text;
public:
	Markdown_BlockElement(BlockType T, const std::string& t);
	BlockType getType()const;
	const std::string& getText()const;
};
