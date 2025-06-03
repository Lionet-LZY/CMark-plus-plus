//打入html标签实现

#include "Html_Renderer.h"

std::string html::codetype(Markdown_BlockElement a) {
	std::string ctype, text;
	text = a.getText();
	for (size_t i = 0;; i++) {
		if (text[i] == '\r') { break; }
		ctype[i] = text[i];
	}
	return ctype;
}

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
	else if (a.getType() == BlockType::CodeBlocks) {
		if (codetype(a) == "'''cpp" || codetype(a) == "'''c++") {
			htext = "<pre class=\"language - cpp\"><code>" + a.getText() + "</code></pre>";
		}
		else if (codetype(a) == "'''python" || codetype(a) == "'''py") {
			htext = "<pre class=\"language - python\"><code>" + a.getText() + "</code></pre>";
		}
		else if (codetype(a) == "'''c") {
			htext = "<pre class=\"language - c\"><code>" + a.getText() + "</code></pre>";
		}
		else if (codetype(a) == "'''java") {
			htext = "<pre class=\"language - java\"><code>" + a.getText() + "</code></pre>";
		}
		else {
			htext = "<pre class=\"language - text\"><code>" + a.getText() + "</code></pre>";
		}
	}
	else if (a.getType() == BlockType::OrderedList) {
		htext = "<ol>" + a.getText() + "</ol>";
	}
	else if (a.getType() == BlockType::UnorderedList) {
		htext = "<ul>" + a.getText() + "</ul>";
	}
	else if (a.getType() == BlockType::BlockQuote) {
		htext = "<blockquote>" + a.getText() + "</blockquote>";
	}
}