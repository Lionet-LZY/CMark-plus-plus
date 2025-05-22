// Markdown_Parser.cpp：语法解析实现

#include "Markdown_Parser.h"
#include <sstream>
#include <regex>
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
			if (space_count <= 2) { BufText += RawText[ins]; }
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