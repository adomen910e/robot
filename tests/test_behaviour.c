#include "../api.h"
#include "../behaviour.c"
#include <stdio.h>
#include <assert.h>

void test_getGoalAction()
{
    struct Config config = {100., 50., 5.};
    struct Ball ball = {1., 0., 0., 0., 0.};
    struct Robot robots[12];
    robots[0].x = 50.;
    robots[0].y = 0.;
    robots[0].t = 0.;
    robots[0].team = 1;
    robots[0].behaviour = GOAL_KEEPER;

    struct Action action = getGoalAction(&config, robots, 12, &ball, 0);
    assert(action.x == 47.5 && action.y == 0. && action.t == 0.);

    robots[0].team = 2;
    action = getGoalAction(&config, robots, 12, &ball, 0);
    assert(action.x == -47.5 && action.y == 0. && action.t == 0.);

    robots[0].team = 1;
    ball.y = 20;
    action = getGoalAction(&config, robots, 12, &ball, 0);
    assert(action.x >= -47.5 && action.y >= 0. && action.t >= 0.);

    ball.y = -20;
    struct Action action2 = getGoalAction(&config, robots, 12, &ball, 0);
    assert(action2.x == action.x && action2.y == -action.y && action2.t == -action.t);

    // printf("%f %f %f\n", action.x, action.y, action.t);
}

int main(int argc, char const *argv[])
{
    test_getGoalAction();
    return 0;
}
