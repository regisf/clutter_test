#include <stdlib.h> 
#include <clutter/clutter.h>

#define MAX_SPRITE 1000 
#define WIDTH 800 
#define HEIGHT 600 

typedef struct Actor { 
    ClutterActor * actor; 
    gdouble rotation; 
    gint x; 
    gint y; 
    gint xdir; 
    gint ydir; 
    gint xspeed; 
    gint yspeed; 
} Actor;

static void get_random_direction(gint * x,gint * y) 
{ 
    switch(rand()%4)
    { 
        case 0: 
            *x = -1; 
            *y = -1; 
            break; 

        case 1:
            *x = 1; 
            *y = -1; 
            break; 

        case 2: 
            *x = 1; 
            *y = 1; 
            break;

        case 3: 
            *x = -1; 
            *y = 1;
            break;
    }
} 

static void get_random_position(const gint width, const gint height, gint * x, gint * y ) 
{ 
    *x = rand() % height; 
    *y = rand() % width;
 } 

void on_new_frame(ClutterTimeline * timeline, gint frame_nb, gpointer data) 
{ 
    Actor ** actors = (Actor **)data; 
    gfloat width = 0.0; 
    gfloat height = 0.0; 
    guint i; 
    for (i=0;i < MAX_SPRITE; i++) { 
        clutter_actor_get_size(actors[i]->actor, &width, &height); 
        actors[i]->x+= actors[i]->xspeed *actors[i]->xdir; 
        actors[i]->y+= actors[i]->yspeed * actors[i]->ydir;
        if (actors[i]->x+width > WIDTH || actors[i]->x < 0) actors[i]->xdir = -actors[i]->xdir; 

        if (actors[i]->y+height > HEIGHT || actors[i]->y < 0) actors[i]->ydir = -actors[i]->ydir; 

        clutter_actor_set_position(actors[i]->actor,actors[i]->x,actors[i]->y); 
    } 
} 

static Actor * create_actor(ClutterActor * stage) 
{ 
    Actor * act = g_malloc(sizeof(Actor)); 
    act->actor = clutter_texture_new_from_file("balloon.png",NULL); 
    get_random_direction(&act->xdir, &act->ydir); 
    get_random_position(WIDTH - clutter_actor_get_width(act->actor), HEIGHT - clutter_actor_get_height(act->actor), &act->x, &act->y); 
    clutter_actor_set_position(act->actor,act->x,act->y); 
    act->rotation = 0.0; 
    act->xspeed = rand() % 5 + 1; 
    act->yspeed = rand() % 5 + 1 ; 
    clutter_container_add_actor(CLUTTER_CONTAINER(stage),act->actor); 
    clutter_actor_show(act->actor); 
    return act;
} 

int main( int argc, char ** argv ) 
{ 
    ClutterActor * stage = NULL; 
    Actor * actors[MAX_SPRITE];// = NULL;
    ClutterTimeline * timeline = NULL; 
    ClutterColor color = { 0, 0, 0, 255 }; 
    guint i; 

    clutter_init(&argc,&argv); 
    stage = clutter_stage_get_default(); 
    clutter_actor_set_size(stage,WIDTH,HEIGHT); 
    clutter_stage_set_color(CLUTTER_STAGE(stage),&color);  

    for (i=0;i<MAX_SPRITE;i++) 
        actors[i]=create_actor(stage);  

    clutter_actor_show(stage); timeline=clutter_timeline_new(1); 
    g_signal_connect(timeline,"new-frame",G_CALLBACK(on_new_frame),actors); 
    clutter_timeline_set_loop(timeline,TRUE); 
    clutter_timeline_start(timeline);
    clutter_main(); 
    return 0; 
}
