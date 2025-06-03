// Markdown_Parser.cpp：语法解析实现

#include "Markdown_Parser.h"
#include <sstream>
#include <regex>
#include <iostream>
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

std::vector<Markdown_InlineElement> Markdown_Parser::inline_parse(const std::string& RawText, std::string& ResText, size_t begin_ins, size_t end_ins) {
	std::string BufText;
	std::vector<Markdown_InlineElement> ResElem;
	std::vector<std::tuple<size_t, size_t, std::string>> TextSegments;
	ResText = "";
	size_t ins = begin_ins;
	size_t space_count = 0;
	while (ins <= end_ins) {
		if (RawText[ins] == ' ') {
			space_count++;
			if (space_count <= 1) { BufText += RawText[ins]; }
		}
		else { space_count = 0; BufText += RawText[ins]; }
		ins++;
	}
	std::vector<std::pair<InlineType, std::regex>> patterns = {
		{InlineType::BoldItalic, std::regex(R"(\*\*\*(.+?)\*\*\*)")},
		{InlineType::Bold,       std::regex(R"(\*\*(.+?)\*\*)")},
		{InlineType::Italic,     std::regex(R"(\*(?!\*)(.+?)\*)")},
		{InlineType::Code,       std::regex(R"(`(.+?)`)")}
	};
	for (const auto& [type, pattern] : patterns) {
		for (auto buf = std::sregex_iterator(BufText.begin(), BufText.end(), pattern); buf != std::sregex_iterator(); buf++) {
			std::smatch match = *buf;
			ResElem.push_back(Markdown_InlineElement(type, 
												     static_cast<size_t>(match.position()), 
													 static_cast<size_t>(match.position() + match.length() - 1)));
			TextSegments.push_back({ static_cast<size_t>(match.position()),
									 static_cast<size_t>(match.position() + match.length() - 1),
									 match[1].str() });
		}
	}
	std::sort(TextSegments.begin(), TextSegments.end(), [](const auto& a, const auto& b) {
		return std::get<0>(a) < std::get<0>(b);
	});
	std::sort(ResElem.begin(), ResElem.end(), [](const Markdown_InlineElement& a, const Markdown_InlineElement& b) {
		return a.getBegin() < b.getBegin();
	});
	size_t curr = 0;
	for (const auto& [start, end, inner] : TextSegments) {
		if (start > curr) {
			ResText += BufText.substr(curr, start - curr);
		}
		ResText += inner;
		curr = end;
	}
	if (curr < BufText.size()) {
		ResText += BufText.substr(curr);
	}
	return ResElem;
}
