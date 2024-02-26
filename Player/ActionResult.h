//
// Created by Victor Navarro on 26/02/24.
//

#ifndef RPG_ACTIONRESULT_H
#define RPG_ACTIONRESULT_H
#include "../Character/Character.h"

struct ActionResult {
    Character *target = nullptr;
    bool fleed = false;

    ActionResult(Character *_target, bool _fleed) {
        target = _target;
        fleed = _fleed;
    }
};

#endif //RPG_ACTIONRESULT_H
