#include "Sort.h"

void Sort::sortByIncreasingPerimeter(std::list<Shape*>* shapeList)
{
	auto increasingOrder = [](Shape* a, Shape* b) {return a->perimeter() < b->perimeter(); };
	shapeList->sort(increasingOrder);
}

void Sort::sortByDecreasingPerimeter(std::list<Shape*>* shapeList)
{
	auto decreasingOrder = [](Shape* a, Shape* b) {return a->perimeter() > b->perimeter(); };
	shapeList->sort(decreasingOrder);
}

void Sort::sortByIncreasingArea(std::list<Shape*>* shapeList)
{
	auto increasingOrder = [](Shape* a, Shape* b) {return a->area() < b->area(); };
	shapeList->sort(increasingOrder);
}

void Sort::sortByDecreasingArea(std::list<Shape*>* shapeList)
{
	auto decreasingOrder = [](Shape* a, Shape* b) {return a->area() > b->area(); };
	shapeList->sort(decreasingOrder);
}

void Sort::sortByIncreasingCompactness(std::list<Shape*>* shapeList)
{
	auto compactness = [](Shape* shape) {
		return 4 * M_PI*shape->area() / (pow(shape->perimeter(), 2));
	};

	auto increasingOrder = [&](Shape* a, Shape* b) {return (compactness(a)) < (compactness(b)); };
	shapeList->sort(increasingOrder);
}
