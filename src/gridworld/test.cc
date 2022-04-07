/**
 * \file test.cc
 * \brief unit test for some function
 */

#if 1
#include "../Environment.h"
#include "GridWorld.h"
#include "../runtime_api.h"
#include <random>

using ::magent::gridworld::SectorRange;
using ::magent::gridworld::CircleRange;

// void test_sector_range() {
//     printf(" ==== test sector range ==== \n");

//     /*SectorRange s1(120, 3, 0);
//     SectorRange s2(120, 5, 0);

//     s1.print_self();
//     s2.print_self();*/

//     CircleRange r1(4, 1, 0);
//     CircleRange r2(4, 0, 1);

//     r1.print_self();
//     r2.print_self();
// }

// void get_observation(EnvHandle game, GroupHandle group, float **pview_buf, float **php_buf) {
//     int buf[3];
//     int height, width, n_channel;
//     //env_get_int_info(game, group, "view_size", buf);
//     height = buf[0], width = buf[1], n_channel = buf[2];
//     int n;
//     //env_get_num(game, group, &n);

//     float *view_buf = new float[n * height * width * n_channel];
//     float *hp_buf   = new float[n];

//     float *bufs[] = {view_buf, hp_buf};
//     env_get_observation(game, group, bufs);

//     *pview_buf = view_buf;
//     *php_buf   = hp_buf;
// }

// void get_position(EnvHandle game, GroupHandle group, int **ppos_x, int **ppos_y) {
//     int n;
//     //env_get_num(game, group, &n);
//     int *pos = new int [n * 2];
//     int *pos_x = new int [n];
//     int *pos_y = new int [n];
//     //env_get_int_info(game, group, "pos", pos);
//     for (int i = 0; i < n; i++) {
//         pos_x[i] = pos[i * 2];
//         pos_y[i] = pos[i * 2 + 1];
//     }
//     *ppos_x = pos_x;
//     *ppos_y = pos_y;
//     delete [] pos;
// }

void test_extract_view() {
    // printf("22222222222\n");
    EnvHandle game;
    env_new_game(&game, "GridWorld");

    // config
    int width = 20;
    int height = 20;
    game->set_config("map_width", &width);
    game->set_config("map_height", &height);

    // register type
    const char *type_keys[] =  {
            "width", "length", "speed", "hp",
            "view_radius", "view_angle", "attack_radius", "attack_angle",
            "hear_radius", "speak_radius",
            "speak_ability", "damage", "trace", "step_recover", "kill_supply",
            "attack_in_group",
            "step_reward", "kill_reward", "dead_penalty",
    };

    float type_deer[] = {
            1, 1, 1, 10,
            2, 360, 0, 0,
            0, 0,
            0, 2, 0, 0, 10,
            0,
            -.005f, -0.1, 0.2,
    };

    float type_tiger[] = {
            1, 1, 1, 10,
            2, 360, 0, 0,
            0, 0,
            0, 2, 0, 0, 10,
            0,
            -.005f, -0.1, 0.2,
    };

    // printf("3333333\n");
    int n = sizeof(type_keys) / sizeof(type_keys[1]);
    gridworld_register_agent_type(game, "deer", n, type_keys, type_deer);
    gridworld_register_agent_type(game, "tiger", n, type_keys, type_tiger);

    // new group
    GroupHandle deer_handle, tiger_handle;
    gridworld_new_group(game, "deer", &deer_handle);
    gridworld_new_group(game, "tiger", &tiger_handle);

    env_reset(game);

    //gridworld_add_agents(game, -1, 4, "random", nullptr, nullptr, nullptr);
    gridworld_add_agents(game, deer_handle, 12, "random", nullptr, nullptr, nullptr);
    gridworld_add_agents(game, tiger_handle, 12, "random", nullptr, nullptr, nullptr);
    // printf("4444444\n");
    //env_set_render(game, "save_dir", "___debug___");
    env_render(game);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,20);

    int deer_acts[12] = {1,1,1,1,1,1,1,1,1,1,1,1}; 
    int tiger_acts[12] = {1,1,1,1,1,1,1,1,1,1,1,1}; 
    for(int i=0;i<3000;i++){

        std::cout << i << std::endl;
         for(int j=0;j<sizeof(deer_acts) / sizeof(deer_acts[0]);j++){
             deer_acts[j] = dist6(rng);
             tiger_acts[j] = dist6(rng);
        }

        env_set_action(game, deer_handle, deer_acts);
        env_set_action(game, tiger_handle, tiger_acts);

        int done;
        env_step(game, &done);
        env_render(game);

    }

    // int observation_handle = deer_handle;

    // int buf[3];
    // int t_height, t_width, t_n_channel;
    //env_get_int_info(game, observation_handle, "view_size", buf);
    // t_height = buf[0], t_width = buf[1], t_n_channel = buf[2];

    // float (*view_buf)[t_height][t_width][t_n_channel];
    // float *hp_buf;
    // int *pos_x, *pos_y;

    //env_get_num(game, observation_handle, &n);
    // get_position(game, observation_handle, &pos_x, &pos_y);
    // get_observation(game, observation_handle, (float **)&view_buf, &hp_buf);
    // printf("5555555555555\n");

    // printf("observation\n");
    // for (int i = 0; i < n; i++) {
    //     printf("======\n");
    //     printf("%d %d\n", pos_x[i], pos_y[i]);
    //     for (int j = 0; j < t_height; j++) {
    //         for (int k = 0; k < t_n_channel; k++) {
    //             for (int l = 0; l < t_width; l++) {
    //                 printf("%1.1f ", (view_buf[i][j][l][k]));
    //             }
    //             printf("  ");
    //         }
    //         printf("\n");
    //     }
    // }

    // printf("hp");
    // for (int i = 0; i < n; i++) {
    //     printf("%.2f ", hp_buf[i]);
    // }

    delete(game);
}
#endif

int main() {
    // printf("111111\n");
    //test_sector_range();
    test_extract_view();

    return 0;
}
