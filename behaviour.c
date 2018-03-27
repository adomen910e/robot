#include "api.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.c"

struct Interval calcGoalIntervalProtectedByDefender(struct Config * config, struct Ball * ball, struct Robot defender)
{
    double distance_ball_defender = distance(defender.x, defender.y, ball.x, ball.y);
    // Angle entre l'axe des abscisses et la droite ball-defenser
    float alpha0 = asin((defender.y - ball.y) / distance_ball_defender);
    // Angle entre la droite ball-defenser et la droite passant par la balle et tangente au robot
    float alpha1 = atan(defender.radius / distance_ball_defender);
    float y1 = config.width / 2 * tan(alpha0 + alpha1);
    float y2 = config.width / 2 * tan(alpha0 - alpha1);
    return {y1, y2};
}

struct Action getGoalAction(
    struct Config * config,
    struct Robot * robots,
    int nb_robots,
    struct Ball * ball,
    int robot_id
) {
    double r = config->goal_size / 2;
    int goal_side = (robots[robot_id].team == 2 ? 1 : -1);
    double distance_ball_goal = calcDistance(ball.x, ball.y, goal_side * config->width / 2, 0);

    struct Action action;
    if (robots[robot_id].team == 2)
    {
        action.x = config->width / 2 - r * (config->width / 2 - ball->x) / distance_ball_goal;
    } else {
        action.x = - config->width / 2 + r * (config->width / 2 + ball->x) / distance_ball_goal;
    }
    action.y = r * ball->y / distance_ball_goal;
    action.t = asin(ball->y / distance_ball_goal);
    return action;
}

struct Action getBehaviour(
    struct Config * config,
    struct Robot * robots,
    int nb_robots,
    struct Ball * ball,
    int robot_id
) {
    if (strcmp(robots[robot_id].behaviour, GOAL_KEEPER)) {
        return getGoalAction(config, robots, nb_robots, ball, robot_id);
    }
}
