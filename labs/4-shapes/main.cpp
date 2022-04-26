#include "ShapeService.h"
#include "Canvas.h"

int main()
{
	ShapeService shapeService;

	if (!shapeService.ReadShapeData(std::cin))
	{
		std::cout << "Error was occured while reading shape data. Exiting..." << std::endl;
		return 1;
	}

	std::cout << "====  Max Area Shape  ====" << std::endl;
	shapeService.PrintMaxAreaShapeInfo(std::cout);
	std::cout << std::endl;
	std::cout << "====  Min Perimeter Shape  ====" << std::endl;
	shapeService.PrintMinPerimeterShapeInfo(std::cout);

	Canvas canvas(800, 600, "Malov die balls");
	shapeService.DrawAll(canvas);

	canvas.RenderAll();

	canvas.HoldWindow();

	return 0;
}
