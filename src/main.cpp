/*#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	window.show();
	return QApplication::exec();
}*/

// main.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include "Markdown_Parser.h"
#include "Markdown_InlineElement.h"
#include "Html_Renderer.h"

int main()
{
    std::ifstream ifile("resources/test.md");
    if (!ifile.is_open()) {
        std::cerr << "Failed to open: resources/test.md" << std::endl;
        return 1;
    }
    std::ostringstream oss;
    oss << ifile.rdbuf();
    std::string md_text = oss.str();
    Markdown_Parser parser;
    std::vector<Markdown_BlockElement> blocks;
    parser.block_parse(md_text, blocks);
    Html_Renderer html;
    html.SetStyle("style.css");
    html.Init();
    for (size_t i = 0; i < blocks.size(); i++) {
        html.BlockHtml(blocks[i]);
    }
    html.Tail();
    std::ofstream ofile("resources/test.html");
    if (!ofile.is_open()) {
        std::cerr << "Failed to open: resources/test.html" << std::endl;
        return 1;
    }
    ofile << html.getHtml();
    /*for (size_t i = 0; i < blocks.size(); i++) {
		std::cout << "Block #" << i << "  ";
        switch (blocks[i].getType()) {
            case BlockType::Paragraph:
                std::cout << "Paragraph: \n";
                break;
            case BlockType::Headinglevel1:
                std::cout << "Head 1: \n";
                break;
            case BlockType::Headinglevel2:
                std::cout << "Head 2: \n";
                break;
            case BlockType::Headinglevel3:
                std::cout << "Head 3: \n";
                break;
            case BlockType::BlockQuote:
                std::cout << "Quote: \n";
                break;
            case BlockType::CodeBlocks:
                std::cout << "Code: \n";
                break;
            case BlockType::HorizontalRules:
                std::cout << "HorizontalRules\n";
                break;
            case BlockType::OrderedList:
                std::cout << "Ordered List: \n";
				break;
            case BlockType::UnorderedList:
                std::cout << "Unordered List: \n";
                break;
        }
        for (size_t j = 0; j < blocks[i].getText().size(); j++) {
			std::cout << "  Line " << j << '\t' << blocks[i].getText()[j].text << '\n';
            for(size_t k = 0; k < blocks[i].getText()[j].InlineElement.size(); k++) {
                std::string type_str;
                switch (blocks[i].getText()[j].InlineElement[k].getType()) {
                    case InlineType::Bold:   type_str = "Bold"; break;
                    case InlineType::Italic: type_str = "Italic"; break;
                    case InlineType::Code:   type_str = "Code"; break;
                }
                std::cout << "\tInline Element: " << type_str 
                          << " [" << blocks[i].getText()[j].InlineElement[k].getBegin()
                          << ", " << blocks[i].getText()[j].InlineElement[k].getEnd() << "]\n";
			}
        }
    }
    
    parser.split(md_text);
    for (int i = 0; i < parser.RawBlock.size(); i++) {
        std::cout << "Block #" << i << '\n';
        for (int j = 0; j < parser.RawBlock[i].size(); j++) {
            std::cout << "\tLine " << j << '\t' << parser.RawBlock[i][j] << '\n';
        }
    }
    Markdown_Parser parser;
    std::string raw = "  **bold**,      *Ita   lic* and `code`.";
    std::string resultText;

    auto elems = parser.inline_parse(raw, resultText);

    std::cout << "Result Text: " << resultText << "\n";
    std::cout << "Inline Elements:\n";
    for (const auto& elem : elems) {
        std::string type_str;
        switch (elem.getType()) {
        case InlineType::Bold:       type_str = "Bold"; break;
        case InlineType::Italic:     type_str = "Italic"; break;
        case InlineType::Code:       type_str = "Code"; break;
        }
        std::cout << type_str << " [" << elem.getBegin() << ", " << elem.getEnd() << "]\n";
    }*/
}