#pragma once
#ifndef EXP_H
#define EXP_H
#include "Shapes.h"
#include "Media.h"
#include "Sort.h"

using namespace std;
const double epsilon = 0.000001;

TEST(Sort, sortByIncreasingPerimeter)
{
	list<Shape*> shapes;
	Circle c(0, 0, 1);//6.28
	Rectangle r(0, 0, 1, 2);//6
	vertex t1 = { 0,0 }, t2 = { 1,1 }, t3 = { 2,0 };
	Triangle t(t1, t2, t3);//4.8
	shapes.push_back(&c);
	shapes.push_back(&r);
	shapes.push_back(&t);
	Sort::sortByIncreasingPerimeter(&shapes);
	string names[3] = { "t","r","c" };
	for (int i = 0; i < 3; i++)
	{
		auto shape = *next(shapes.begin(), i);
		ASSERT_EQ(names[i], shape->name);
	}
}

TEST(Sort, sortByDecreasingPerimeter) {
	list<Shape*> shapes;
	Circle c(0, 0, 1);//6.28
	Rectangle r(0, 0, 1, 2);//6
	vertex t1 = { 0,0 }, t2 = { 1,1 }, t3 = { 2,0 };
	Triangle t(t1, t2, t3);//4.8
	shapes.push_back(&t);
	shapes.push_back(&r);
	shapes.push_back(&c);
	Sort::sortByDecreasingPerimeter(&shapes);
	string names[3] = { "c","r","t" };
	for (int i = 0; i < 3; i++)
	{
		auto shape = *next(shapes.begin(), i);
		ASSERT_EQ(names[i], shape->name);
	}
}

TEST(Sort, sortByIncreasingArea) {
	list<Shape*> shapes;
	Circle c(0, 0, 1);//3.14
	Rectangle r(0, 0, 1, 2);//2
	vertex t1 = { 0,0 }, t2 = { 1,1 }, t3 = { 2,0 };
	Triangle t(t1, t2, t3);//1
	shapes.push_back(&c);
	shapes.push_back(&r);
	shapes.push_back(&t);
	Sort::sortByIncreasingArea(&shapes);
	string names[3] = { "t","r","c" };
	for (int i = 0; i < 3; i++)
	{
		auto shape = *next(shapes.begin(), i);
		ASSERT_EQ(names[i], shape->name);
	}
}

TEST(Sort, sortByDecreasingArea) {
	list<Shape*> shapes;
	Circle c(0, 0, 1);//3.14
	Rectangle r(0, 0, 1, 2);//2
	vertex t1 = { 0,0 }, t2 = { 1,1 }, t3 = { 2,0 };
	Triangle t(t1, t2, t3);//1
	shapes.push_back(&t);
	shapes.push_back(&r);
	shapes.push_back(&c);
	Sort::sortByDecreasingArea(&shapes);
	string names[3] = { "c","r","t" };
	for (int i = 0; i < 3; i++)
	{
		auto shape = *next(shapes.begin(), i);
		ASSERT_EQ(names[i], shape->name);
	}
}

TEST(Sort, sortByIncreasingCompactness) {
	list<Shape*> shapes;
	Circle c(0, 0, 1);//0.5
	Rectangle r(0, 0, 1, 2);//0.33
	vertex t1 = { 0,0 }, t2 = { 1,1 }, t3 = { 2,0 };
	Triangle t(t1, t2, t3);//0.207
	shapes.push_back(&c);
	shapes.push_back(&r);
	shapes.push_back(&t);
	Sort::sortByIncreasingCompactness(&shapes);
	string names[3] = { "t","r","c" };
	for (int i = 0; i < 3; i++)
	{
		auto shape = *next(shapes.begin(), i);
		ASSERT_EQ(names[i], shape->name);
	}
}

#endif
