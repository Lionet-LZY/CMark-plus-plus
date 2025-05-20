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

	while(ins < RawLine.size()) {
		// const std::string* prev = (ins > 0) ? &RawLine[ins - 1] : nullptr;
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
			BlockText.push_back(curr);
			if (curr == "") {
				RawBlock.push_back(BlockText);
				BlockText.clear();
				OrderedLists_flag = 0;
				ins++; continue;
			}
			if (OrderedLists_flag == 0) { OrderedLists_flag = 1; }
			ins++; continue;
		}
		// 无序列表
		else if (curr[0] == '-' && curr[1] == ' ') {
			BlockText.push_back(curr);
			if (*next == "") {
				BlockText.push_back(*next);
				RawBlock.push_back(BlockText);
				BlockText.clear();
				ins += 2; continue;
			}
			ins++; continue;
		}
		// 引用
		else if (curr[0] == '>' && curr[1] == ' ') {
			BlockText.push_back(curr);
			if (*next == "") {
				BlockText.push_back(*next);
				RawBlock.push_back(BlockText);
				BlockText.clear();
				ins += 2; continue;
			}
			ins++; continue;
		}
		// 标题
		else if ((curr[0] == '#' && curr[1] == ' ')||
			(curr[0] == '#' && curr[1] == '#' && curr[2] == ' ')||
			(curr[0] == '#' && curr[1] == '#' && curr[2] == '#' && curr[3] == ' ')) {
			BlockText.push_back(curr);
			RawBlock.push_back(BlockText);
			BlockText.clear();
			ins++; continue;
		}
		// 空行 & 分割线
		else if (curr == "") {
			if (*next == "---") {
				BlockText.push_back(curr);
				BlockText.push_back(*next);
				RawBlock.push_back(BlockText);
				BlockText.clear();
				ins += 2; continue;
			}
			else {
				BlockText.push_back(curr);
				if (*next != "") {
					RawBlock.push_back(BlockText);
					BlockText.clear();
				}
				ins++; continue;
			}
		}
		// 正文
		else {
			BlockText.push_back(curr);
			if (*next == "") {
				BlockText.push_back(*next);
				RawBlock.push_back(BlockText);
				BlockText.clear();
				ins += 2; continue;
			}
			ins++; continue;
		}
	}
}