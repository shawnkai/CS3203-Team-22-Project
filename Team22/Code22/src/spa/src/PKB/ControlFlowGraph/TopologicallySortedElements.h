//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_TOPOLOGICALLYSORTEDELEMENTS_H
#define SPA_TOPOLOGICALLYSORTEDELEMENTS_H

#include <iostream>
#include <vector>

using namespace std;

class TopologicallySortedElements {
    vector<int> topologicallySortedElementsDatabase;

public:
    explicit TopologicallySortedElements(vector<int> topologicallySortedElementsDatabase);
    explicit TopologicallySortedElements();

    void addElement(int element);
    void copyTopologicallySortedElementsDatabase(vector<int> topologicallySortedElements);
    vector<int> getTopologicallySortedElementsDatabase();
    void clearDatabase();
};

#endif //SPA_TOPOLOGICALLYSORTEDELEMENTS_H
