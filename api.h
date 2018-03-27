#ifndef __API__
#define __API__

#define GOAL_KEEPER "goal_keeper"
#define DEFENDER "defender"
#define STRIKER "striker"

struct Config {
    float width, height;
    float goal_size;
};

struct Robot
{
    float radius;
    float x, y, t;
    float vx, vy, vt;
    int team;
    char * behaviour;
};

struct Ball {
    float radius;
    float x, y, vx, vy;
};

struct Action
{
    float x, y, t;
};

struct Action getBehaviour(
    struct Config * config,
    struct Robot * robots,
    int nb_robots,
    struct Ball * ball,
    int robot_id
);

void setBehaviour(
    struct Config * config,
    struct Robot * robots,
    int nb_robots,
    int team
);

#endif
