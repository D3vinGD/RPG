//
// Created by Victor Navarro on 26/02/24.
//

#ifndef RPG_ACTION_H
#define RPG_ACTION_H

struct Action {
    int speed = 0;
    std::function<void(void)> action = nullptr;

    Action(std::function<void(void)> _action, int _speed) {
        action = _action;
        speed = _speed;
    }
    Action(){};

    bool operator<(const Action& p) const
    {
        return this->speed < p.speed;
    }
};

#endif //RPG_ACTION_H
