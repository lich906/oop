#include "ShapeService.h"

int main()
{
	ShapeService shapeService;

	if (!shapeService.ReadShapeData(std::cin))
	{
		std::cout << "Error was occured while reading shape data. Exiting..." << std::endl;
		return 1;
	}

	std::cout << "====  Max Area Shape  ====" << std::endl;
	shapeService.PrintShapeInfo(std::cout, shapeService.FindMaxAreaShape());
	std::cout << std::endl;
	std::cout << "====  Min Perimeter Shape  ====" << std::endl;
	shapeService.PrintShapeInfo(std::cout, shapeService.FindMinPerimeterShape());

	return 0;
}
