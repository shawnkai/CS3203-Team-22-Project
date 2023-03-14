//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "TopologicallySortedElements.h"

using namespace std;

TopologicallySortedElements::TopologicallySortedElements(vector<int> topologicallySortedElementsDatabase) {
    this->topologicallySortedElementsDatabase = topologicallySortedElementsDatabase;
}

TopologicallySortedElements::TopologicallySortedElements() {
    this->topologicallySortedElementsDatabase = vector<int> {};
}

void TopologicallySortedElements::addElement(int element) {
    this->topologicallySortedElementsDatabase.push_back(element);
}

void TopologicallySortedElements::copyTopologicallySortedElementsDatabase(vector<int> topologicallySortedElements) {
    this->topologicallySortedElementsDatabase = topologicallySortedElements;
}

vector<int> TopologicallySortedElements::getTopologicallySortedElementsDatabase() {
    return this->topologicallySortedElementsDatabase;
}

void TopologicallySortedElements::clearDatabase() {
    destroy(this->topologicallySortedElementsDatabase.begin(), this->topologicallySortedElementsDatabase.end());
}
