/*
Определить глубину дерева.
*/

#include <iostream>
#include <Windows.h>
#include "CTree.h"

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    CTree* tr = new CTree("file.txt", "tr");

    tr->view_all();

    printf("\n\n\n %i", tr->depth_tree());

    delete tr;
    tr = NULL;
}