// main.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib>
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
	ifile.close();
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
	ofile.close();
    std::cout << "Generate succeed.\n";
    system("start resources/test.html");
    return 0;
}