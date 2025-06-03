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

int main()
{
    std::ifstream file("resources/test.md");
    if (!file.is_open()) {
        std::cerr << "Failed to open: resources/test.md" << std::endl;
        return 1;
    }
    std::ostringstream oss;
    oss << file.rdbuf();
    std::string md_text = oss.str();
    Markdown_Parser parser;
    parser.split(md_text);
    for (int i = 0; i < parser.RawBlock.size(); i++) {
        std::cout << "Block #" << i << '\n';
        for (int j = 0; j < parser.RawBlock[i].size(); j++) {
            std::cout << "\tLine " << j << '\t' << parser.RawBlock[i][j] << '\n';
        }
    }
}