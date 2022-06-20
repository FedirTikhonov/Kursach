#include "lib.h"

int main() {
    newVector v;
    v.inputWorkers();
    v.output();
    std::cout << "Yearly cost of all workers' wages: " << v.countYearly() << std::endl;
    return 0;
}
