#include "TextRendererHUDComponent.h"
#include "../../App/app.h"

TextRendererHUDComponent::TextRendererHUDComponent() : m_text(), m_color(RGBColor::White), m_font(GLUT_BITMAP_HELVETICA_18)
{
}

void TextRendererHUDComponent::Render()
{
	App::Print(GetPosition().x, GetPosition().y, m_text.c_str(), m_color.R, m_color.G, m_color.B, m_font);
}