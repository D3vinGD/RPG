#include <iostream>
#include "Character/Character.h"

int main() {
    Character mage = Character("Mage", 100, 10, 5, 20);

    cout << mage.toString() << endl;
    return 0;
}
