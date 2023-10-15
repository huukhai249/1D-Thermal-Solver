#include"parameters.h"
#include "solveM.h"


int main () {
    parameters p1;
    p1.readingParameters();
    solveM s(p1);
    s.createMesh();
    return 0;
}