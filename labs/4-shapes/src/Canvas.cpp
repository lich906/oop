#include "Canvas.h"

void Canvas::DrawLine(const Point& from, const Point& to, uint32_t lineColor)
{
	sf::VertexArray* line = new sf::VertexArray(sf::Lines, 2);

	(*line)[0].position = sf::Vector2f(from.x, from.y);
	(*line)[0].color = sf::Color(lineColor);
	(*line)[1].position = sf::Vector2f(to.x, to.y);
	(*line)[1].color = sf::Color(lineColor);

	m_drawBuffer.push(std::unique_ptr<sf::Drawable>(line));
}

void Canvas::FillPolygon(const std::vector<Point>& points, uint32_t fillColor)
{
	sf::ConvexShape* polygon = new sf::ConvexShape(points.size());

	for (size_t index = 0; index < polygon->getPointCount(); ++index)
	{
		polygon->setPoint(index, sf::Vector2f(points[index].x, points[index].y));
	}
	polygon->setFillColor(sf::Color(fillColor));
	polygon->setOutlineThickness(0);

	m_drawBuffer.push(std::unique_ptr<sf::Drawable>(polygon));
}

void Canvas::DrawCircle(const Point& center, double radius, uint32_t lineColor)
{
	sf::CircleShape* circle = new sf::CircleShape(radius);

	circle->setOrigin(sf::Vector2f(radius, radius));
	circle->setOutlineColor(sf::Color(lineColor));
	circle->setOutlineThickness(outlineThickness);
	circle->setFillColor(sf::Color(0x00000000));
	circle->setPosition(center.x, center.y);

	m_drawBuffer.push(std::unique_ptr<sf::Drawable>(circle));
}

void Canvas::FillCircle(const Point& center, double radius, uint32_t fillColor)
{
	sf::CircleShape* circle = new sf::CircleShape(radius);

	circle->setOrigin(sf::Vector2f(radius, radius));
	circle->setOutlineThickness(0);
	circle->setFillColor(sf::Color(fillColor));
	circle->setPosition(center.x, center.y);

	m_drawBuffer.push(std::unique_ptr<sf::Drawable>(circle));
}

void Canvas::RenderAll()
{
	while (!m_drawBuffer.empty())
	{
		m_window.draw(*m_drawBuffer.front());
		m_drawBuffer.pop();
	}

	m_window.display();
}

void Canvas::HoldWindow()
{
	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}
	}
}
