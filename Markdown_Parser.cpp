// Markdown_Parser.cpp：语法解析实现

#include "Markdown_Parser.h"
#include <sstream>

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
	int Code_flag = 0;
	int OrderedLists_flag = 0;
	int UnorderedList_flag = 0;
	int BlockQuote_flag = 0;

	while(ins < RawLine.size()) {
		const std::string* prev = (ins > 0) ? &RawLine[ins - 1] : nullptr;
		const std::string& curr = RawLine[ins];
		const std::string* next = (ins + 1 < RawLine.size()) ? &RawLine[ins + 1] : nullptr;
		// 代码块
		if ((curr[0] == '`' && curr[1] == '`' && curr[2] == '`') || Code_flag == 1) {
			BlockText.push_back(curr);
			if (curr[0] == '`' && curr[1] == '`' && curr[2] == '`' && Code_flag == 1) {
				RawBlock.push_back(BlockText);
				BlockText.clear();
				Code_flag = 0;
				ins++; continue;
			}
			if (Code_flag == 0) { Code_flag = 1; }
			ins++; continue;
		}
		// 有序列表
		else if ((curr[0] == '1' && curr[1] == '.' && curr[2] == ' ') || OrderedLists_flag == 1) {
			if (curr[0] == '1' && curr[1] == '.' && curr[2] == ' ' && OrderedLists_flag == 0) {
				RawBlock.push_back(BlockText);
				BlockText.clear();
				OrderedLists_flag = 1;
			}
			if (curr == "") {
				OrderedLists_flag = 0;
			}
			BlockText.push_back(curr);
			ins++; continue;
		}
		// 无序列表
		else if (curr[0] == '-' && curr[1] == ' ') {
			if (curr[0] == '-' && curr[1] == ' ' && UnorderedList_flag == 0) {
				RawBlock.push_back(BlockText);
				BlockText.clear();
				UnorderedList_flag = 1;
			}
			BlockText.push_back(curr);
			if (*next == "") {
				UnorderedList_flag == 0;
			}
			ins++; continue;
		}
		// 引用
		else if (curr[0] == '>' && curr[1] == ' ') {
			if (curr[0] == '>' && curr[1] == ' ' && BlockQuote_flag == 0) {
				RawBlock.push_back(BlockText);
				BlockText.clear();
				BlockQuote_flag = 1;
			}
			BlockText.push_back(curr);
			if (*next == "") {
				BlockQuote_flag == 0;
			}
			ins++; continue;
		}
		// 标题
		else if ((curr[0] == '#' && curr[1] == ' ') ||
				 (curr[0] == '#' && curr[1] == '#' && curr[2] == ' ') ||
				 (curr[0] == '#' && curr[1] == '#' && curr[2] == '#' && curr[3] == ' ')) {
			RawBlock.push_back(BlockText);
			BlockText.clear();
			BlockText.push_back(curr);
			ins++; continue;
		}
		// 分割线
		else if (prev && *prev == "" && curr == "---") {
			RawBlock.push_back(BlockText);
			BlockText.clear();
			BlockText.push_back(curr);
			ins++; continue;
		}
		// 正文
		else if (curr != "") {
			if (prev && *prev == "") {
				RawBlock.push_back(BlockText);
				BlockText.clear();
			}
			BlockText.push_back(curr);
			ins++; continue;
		}
		// 空行
		else {
			BlockText.push_back(curr);
			ins++; continue;
		}
	}
}