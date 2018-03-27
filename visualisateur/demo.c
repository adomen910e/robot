#include <MLV/MLV_all.h>
#include <stddef.h>
#include <stdio.h>
#include "../api.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 940

#define MARGIN (WINDOW_WIDTH / 20)
#define FIELD_HEIGHT (WINDOW_HEIGHT - 2*MARGIN)
#define FIELD_WIDTH (WINDOW_WIDTH - 2*MARGIN)

#define BOT_NUMBER 2
#define TEAM_1 0
#define TEAM_2 1 

void draw_robot(struct Config *config, struct Robot *bot){
    float x = (bot->x + config->width/2)/config->width*WINDOW_WIDTH;
    float y = (bot->y + config->height/2)/config->height*WINDOW_HEIGHT;

    MLV_Color color = MLV_COLOR_BLUE;
    if (bot->team == TEAM_1)
        color = MLV_COLOR_RED;

    MLV_draw_filled_circle((int)(x), (int)(y), (int)(bot->radius), color);
}

void create_field(){
    MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_GREEN);
    MLV_draw_rectangle(MARGIN, MARGIN, FIELD_WIDTH, FIELD_HEIGHT, MLV_COLOR_WHITE);

    float goal_y = (7./20)*FIELD_HEIGHT + MARGIN;
    float goal_width = (1./18)*FIELD_WIDTH;
    float goal_height = (3./10)*FIELD_HEIGHT;
    MLV_draw_rectangle(MARGIN, (int)(goal_y), (int)(goal_width), (int)(goal_height), MLV_COLOR_WHITE);
    MLV_draw_rectangle(FIELD_WIDTH + MARGIN - goal_width, (int)(goal_y), (int)(goal_width), (int)(goal_height), MLV_COLOR_WHITE);

    goal_y = (1./5)*FIELD_HEIGHT + MARGIN;
    goal_width = (1./6)*FIELD_WIDTH;
    goal_height = (3./5)*FIELD_HEIGHT;
    MLV_draw_rectangle(MARGIN, (int)(goal_y), (int)(goal_width), (int)(goal_height), MLV_COLOR_WHITE);
    MLV_draw_rectangle(FIELD_WIDTH + MARGIN - goal_width, (int)(goal_y), (int)(goal_width), (int)(goal_height), MLV_COLOR_WHITE);

    MLV_draw_line(WINDOW_WIDTH/2, MARGIN, WINDOW_WIDTH/2, WINDOW_HEIGHT-MARGIN, MLV_COLOR_WHITE);
}

int distance(int x1, int y1, int x2, int y2){
    return ((x2 - x1)^2 + (y2 - y1)^2);
}


struct Robot * which_bot_on_click(struct Robot *bot_array[]){
    int mouse_x, mouse_y;
    MLV_get_mouse_position(&mouse_x, &mouse_y);
    for(int i = 0 ; i < BOT_NUMBER ; i++){
        if (distance((int)(bot_array[i]->x), (int)(bot_array[i]->y), mouse_x, mouse_y) <= bot_array[i]->radius^2)
            return bot_array[i];
    }
    return NULL;
}

void bot_click_action(struct Robot *bot){
    if (bot)
        printf("%d \n", bot->x);
}

int main(){
    int stop = 0;
    struct Config config = {900, 600, 100};
    struct Robot bot1 = {20, -100,0,0, 0, 0, 0, 0, NULL};
    struct Robot bot2 = {20, 100,0,0, 0, 0, 0, 1, NULL};
    struct Robot *bot_array[2] = {&bot1, &bot2};

    MLV_create_window("test", "test", WINDOW_WIDTH, WINDOW_HEIGHT);

    create_field();

    draw_robot(&config, &bot1);
    draw_robot(&config, &bot2);


    MLV_actualise_window();
    while (stop == 0){
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED)
            bot_click_action(which_bot_on_click(bot_array));
    }
    MLV_free_window();
    return 0;
}