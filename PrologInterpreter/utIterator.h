#pragma once
#include "Iterator.h"
#include "Number.h"
#include "Atom.h"
#include "Variable.h"
#include "List.h"
#include "Struct.h"
#include "Scanner.h"
#include "Parser.h"

TEST(iterator, Number)
{
	Number one(1);
	Iterator<Term*> *iterator = one.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}

TEST(iterator, Atom)
{
	Atom tom("tom");
	Iterator<Term*> *iterator = tom.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}

TEST(iterator, Variable)
{
	Variable X("X");
	Iterator<Term*> *iterator = X.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}

//s(1,t(X,2),Y).
TEST(iterator, first) {
	Number one(1);
	Variable X("X");
	Variable Y("Y");
	Number two(2);
	Struct t(Atom("t"), { &X, &two });
	Struct s(Atom("s"), { &one, &t, &Y });
	// StructIterator it(&s);
	Iterator<Term*>* itStruct = s.createIterator();
	// Iterator& itStruct = it;
	// ASSERT_EQ(it.first()->symbol());
	itStruct->first();
	ASSERT_EQ("1", itStruct->currentItem()->symbol());
	ASSERT_FALSE(itStruct->isDone());
	itStruct->next();
	ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
	ASSERT_FALSE(itStruct->isDone());
	itStruct->next();
	ASSERT_EQ("Y", itStruct->currentItem()->symbol());
	itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, List) {
	Variable X("X");
	Variable Y("Y");
	vector<Term*> v = { &X,&Y };
	List list(v);
	Iterator<Term*> *iterator = list.createIterator();
	iterator->first();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("X", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("Y", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

TEST(iterator, Struct) {
	Variable X("X");
	Variable Y("Y");
	vector<Term*> v = { &X,&Y };
	Struct s(Atom("tom"), v);
	Iterator<Term*> *iterator = s.createIterator();
	iterator->first();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("X", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("Y", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//root(X0(X00,X01),X1(X1,X0));
TEST(iterator, StructDFS1)
{
	Scanner scanner("root(x0(x00, x01), x1(x10, x11))");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("root(x0(x00, x01), x1(x10, x11))", root->symbol());
	Iterator<Term*> *iterator = root->createDFSIterator();
	iterator->first();
	ASSERT_EQ("x0(x00, x01)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x1(x10, x11)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//[[x00, x01], [x10, x11]]
TEST(iterator, ListDFS1)
{
	Scanner scanner("[[x00, x01], [x10, x11]]");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("[[x00, x01], [x10, x11]]", root->symbol());
	Iterator<Term*> *iterator = root->createDFSIterator();
	iterator->first();
	ASSERT_EQ("[x00, x01]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("[x10, x11]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//root(X0(X00,X01),X1(X1,X0));
TEST(iterator, StructBFS1)
{
	Scanner scanner("root(x0(x00, x01), x1(x10, x11))");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("root(x0(x00, x01), x1(x10, x11))", root->symbol());
	Iterator<Term*> *iterator = root->createBFSIterator();
	iterator->first();
	ASSERT_EQ("x0(x00, x01)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x1(x10, x11)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();	
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//[[x00, x01], [x10, x11]]
TEST(iterator, ListBFS1)
{
	Scanner scanner("[[x00, x01], [x10, x11]]");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("[[x00, x01], [x10, x11]]", root->symbol());
	Iterator<Term*> *iterator = root->createBFSIterator();
	iterator->first();
	ASSERT_EQ("[x00, x01]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("[x10, x11]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());	
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}


//root(X0(X00,X01),X1(X1,X0));
TEST(iterator, StructDFS2)
{
	Scanner scanner("root([x00, x01], [x10, x11])");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("root([x00, x01], [x10, x11])", root->symbol());
	Iterator<Term*> *iterator = root->createDFSIterator();
	iterator->first();
	ASSERT_EQ("[x00, x01]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("[x10, x11]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//[[x00, x01], [x10, x11]]
TEST(iterator, ListDFS2)
{
	Scanner scanner("[x0(x00, x01), x1(x10, x11)]");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("[x0(x00, x01), x1(x10, x11)]", root->symbol());
	Iterator<Term*> *iterator = root->createDFSIterator();
	iterator->first();
	ASSERT_EQ("x0(x00, x01)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x1(x10, x11)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//root(X0(X00,X01),X1(X1,X0));
TEST(iterator, StructBFS2)
{
	Scanner scanner("root([x00, x01], [x10, x11])");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("root([x00, x01], [x10, x11])", root->symbol());
	Iterator<Term*> *iterator = root->createBFSIterator();
	iterator->first();
	ASSERT_EQ("[x00, x01]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("[x10, x11]", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

//[[x00, x01], [x10, x11]]
TEST(iterator, ListBFS2)
{
	Scanner scanner("[x0(x00, x01), x1(x10, x11)]");
	Parser parser(scanner);
	Term* root = parser.createTerm();
	ASSERT_EQ("[x0(x00, x01), x1(x10, x11)]", root->symbol());
	Iterator<Term*> *iterator = root->createBFSIterator();
	iterator->first();
	ASSERT_EQ("x0(x00, x01)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x1(x10, x11)", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x00", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x01", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x10", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_EQ("x11", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}