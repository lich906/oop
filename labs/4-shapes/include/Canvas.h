#pragma once
#include "ICanvas.h"
#include <SFML\Graphics.hpp>
#include <queue>
#include <memory>

constexpr float outlineThickness = 3;

class Canvas : public ICanvas
{
public:
	Canvas(unsigned width, unsigned height, const sf::String& title)
		: m_window(sf::VideoMode(width, height), title)
	{}

	void DrawLine(const Point& from, const Point& to, uint32_t lineColor) override;
	void FillPolygon(const std::vector<Point>& points, uint32_t fillColor) override;
	void DrawCircle(const Point& center, double radius, uint32_t lineColor) override;
	void FillCircle(const Point& center, double radius, uint32_t fillColor) override;

	void RenderAll();
	void HoldWindow();

private:
	std::queue<std::unique_ptr<sf::Drawable>> m_drawBuffer;
	sf::RenderWindow m_window;
};
