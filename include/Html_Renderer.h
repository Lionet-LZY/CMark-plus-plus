//����html��ǩ����
#pragma once

#include <string>
#include "Markdown_BlockElement.h"

class html {
private:
	std::string htext;
public:
	//Ϊ��Ԫ���﷨���ִ���html��ǩ
	void input_htext(Markdown_BlockElement a);
	//�жϴ�����������
	std::string codetype(Markdown_BlockElement a);
};