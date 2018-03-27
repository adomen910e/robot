#include "api.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.c"

//cas ou un defenseur est sur la trajectoire initiale de la ball, [y1; y2] intervalle de protection du defenseur
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


//Cas ou le goal est seul
struct Action getGoalAction(struct Config * config, struct Robot * robots,int nb_robots, struct Ball * ball, int robot_id) {
   
    //r represente le rayon du cercle ayant pour diametre les cages de foot
    //ce sera le rayon d'action du robot
    double r = config->goal_size / 2;
    
    //la variable contiendra -1 si le robot est dans la team 2
    //la variable contiendra  1 si le robot est dans la team 1
    int goal_side = (robots[robot_id].team == 1 ? 1 : -1);
    
    //calcul de la distance entre la ball est le milieu de la cage
    double distance_ball_goal = calcDistance(ball.x, ball.y, goal_side * config->width / 2, 0);

    
    struct Action action;
    //On différencie les cas où on est sur la partie positive du terrainn ou sur la partie négative.
    if (robots[robot_id].team == 2) {
        action.x = config->width / 2 - r * (config->width / 2 - ball->x) / distance_ball_goal;
    } else {
        action.x = - config->width / 2 + r * (config->width / 2 + ball->x) / distance_ball_goal;
    }
    
    action.y = r * ball->y / distance_ball_goal;
    //le robot au aura comme t l'angle ball-cage-horizontal
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
