// Markdown_Parser.cpp：语法解析实现

#include "Markdown_Parser.h"
#include <sstream>
#include <regex>
#include <iostream>
#include <vector>
#include "Markdown_InlineElement.h"

void Markdown_Parser::split(const std::string& RawText) {
	RawBlock.clear();
	std::istringstream iss(RawText);
	std::vector<std::string> RawLine;
	std::string LineText;
	while (std::getline(iss, LineText)) {
		RawLine.push_back(LineText);
	}

	std::vector<std::string> BlockText;
	size_t ins = 0;
	bool Code_flag = false;
	bool OrderedLists_flag = false;
	bool UnorderedList_flag = false;
	bool BlockQuote_flag = false;

	while(ins < RawLine.size()) {
		const std::string* prev = (ins > 0) ? &RawLine[ins - 1] : nullptr;
		const std::string& curr = RawLine[ins];
		const std::string* next = (ins + 1 < RawLine.size()) ? &RawLine[ins + 1] : nullptr;
		std::cout << "test\t" << curr << '\n';
		if (curr.empty()) {
			BlockText.push_back(curr);
			ins++;
			continue;
		}
		// 代码块
		if (curr.rfind("```", 0) == 0 || Code_flag) {
			if (curr.rfind("```", 0) == 0 && !Code_flag) {
				if (!BlockText.empty()) {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
			}
			BlockText.push_back(curr);
			if (curr.rfind("```", 0) == 0) {
				if (Code_flag) {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
				Code_flag = !Code_flag;
			}
			ins++;
			continue;
		}

		// 有序列表
		if (curr.size() >= 3 && std::isdigit(curr[0]) && curr[1] == '.' && curr[2] == ' ') {
			if (!OrderedLists_flag) {
				if (!BlockText.empty()) {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
				OrderedLists_flag = true;
			}
			BlockText.push_back(curr);
			if (!next || next->empty()) OrderedLists_flag = false;
			ins++;
			continue;
		}
		// 无序列表
		if (curr.size() >= 2 && curr[0] == '-' && curr[1] == ' ') {
			if (!UnorderedList_flag) {
				if (!BlockText.empty()) {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
				UnorderedList_flag = true;
			}
			BlockText.push_back(curr);
			if (!next || next->empty()) UnorderedList_flag = false;
			ins++;
			continue;
		}
		// 引用
		if (curr.size() >= 2 && curr[0] == '>' && curr[1] == ' ') {
			if (!BlockQuote_flag) {
				if (!BlockText.empty()) {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
				BlockQuote_flag = true;
			}
			BlockText.push_back(curr);
			if (!next || next->empty()) BlockQuote_flag = false;
			ins++;
			continue;
		}
		// 标题
		if ((curr.size() >= 2 && curr[0] == '#' && curr[1] == ' ') ||
			(curr.size() >= 3 && curr[0] == '#' && curr[1] == '#' && curr[2] == ' ') ||
			(curr.size() >= 4 && curr[0] == '#' && curr[1] == '#' && curr[2] == '#' && curr[3] == ' ')) {
			if (!BlockText.empty()) {
				RawBlock.push_back(BlockText);
				BlockText.clear();
			}
			BlockText.push_back(curr);
			RawBlock.push_back(BlockText);
			BlockText.clear();
			ins++;
			continue;
		}
		// 分割线
		if (curr == "---" && prev && prev->empty()) {
			if (!BlockText.empty()) {
				RawBlock.push_back(BlockText);
				BlockText.clear();
			}
			BlockText.push_back(curr);
			RawBlock.push_back(BlockText);
			BlockText.clear();
			ins++;
			continue;
		}
		// 正文
		if (!curr.empty()) {
			if (prev && prev->empty()) {
				if (!BlockText.empty()) {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
			}
			BlockText.push_back(curr);
			ins++;
			continue;
		}
		// 空行
		BlockText.push_back(curr);
		ins++;
	}
	if (!BlockText.empty()) {
		RawBlock.push_back(BlockText);
	}
}

std::vector<Markdown_InlineElement> Markdown_Parser::inline_parse(const std::string& RawText, std::string& ResText) {
	std::string BufText = "";
	ResText = "";
	std::vector<Markdown_InlineElement> ResElem;
	
	bool space = false;
	for (size_t i = 0; i < RawText.size(); i++) {
		std::string token(1, RawText[i]);
		if (BufText.empty() && token == " ") { continue; }
		if (token == " ") {
			if (!space) { space = true; }
			continue;
		}
		if (token != " ") {
			if (space) { BufText += " "; space = false; }
			BufText += token;
		}
	}

	bool Bold_flag = false;
	bool Italic_flag = false;
	bool Code_flag = false;
	size_t begin = 0;
	size_t i = 0;
	size_t ins = 0;

	while (i < BufText.size()) {
		std::string token(1, BufText[i]);
		if (token == "`" || Code_flag) {
			if (token == "`" && (!Code_flag)) {
				Code_flag = true;
				begin = ins;
				i++;
				continue;
			}
			if (token == "`" && Code_flag) {
				Code_flag = false;
				ResElem.push_back(Markdown_InlineElement(InlineType::Code, begin, ins - 1));
				i++;
				continue;
			}
		}

		if ((token == "*" || Bold_flag || Italic_flag) && !Code_flag) {
			if (token == "*" && (!Bold_flag) && (!Italic_flag)) {
				std::string token_next(1, BufText[i + 1]);
				if (token_next != "*") {
					Italic_flag = true;
					begin = ins;
					i++; continue;
				}
				else {
					Bold_flag = true;
					begin = ins;
					i += 2; continue;
				}
			}
			if(token == "*" && Bold_flag && !Italic_flag) {
				Bold_flag = false;
				ResElem.push_back(Markdown_InlineElement(InlineType::Bold, begin, ins - 1));
				i += 2; continue;
			}
			if(token == "*" && Italic_flag && !Bold_flag) {
				Italic_flag = false;
				ResElem.push_back(Markdown_InlineElement(InlineType::Italic, begin, ins - 1));
				i++; continue;
			}
		}
		ResText += token;
		i++;
		ins++;
	}
	return ResElem;
}