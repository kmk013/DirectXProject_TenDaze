#include "Text.h"

Text::Text(std::string font, unsigned int size, unsigned int weight)
{
	name = "text";

	text = AttachComponent<Components::TextRenderer>();
	text->SetFont(font, size, weight); // �ݵ�� ���־�� ��
}
Text::~Text()
{
}
