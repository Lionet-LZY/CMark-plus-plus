//打入html标签实现

#include"Html_Renderer.h"

void html::input_htext(Markdown_BlockElement a) {
	if (a.getType() == BlockType::Headinglevel1) {
		htext = "<h1>" + a.getText() + "</h1>";
	}
	else if (a.getType() == BlockType::Headinglevel2) {
		htext = "<h2>" + a.getText() + "</h2>";
	}
	else if (a.getType() == BlockType::Headinglevel3) {
		htext = "<h3>" + a.getText() + "</h3>";
	}
	else if (a.getType() == BlockType::Paragraph) {
		htext = "<p>" + a.getText() + "</p>";
	}
	else if (a.getType() == BlockType::HorizontalRules) {
		htext = "<hr>" + a.getText() + "</hr>";
	}
}