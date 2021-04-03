/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2021
 */

#include "sdl2-light.h"


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32


/**
 * \brief Taille d'un météorite
*/

#define METEORITE_SIZE 32


/**
 * \brief Hauteur de la ligne d'arrivée
 */


#define FINISH_LINE_HEIGHT 10


/**
 * \brief Pas de déplacement horizontal du vaisseau
*/

#define MOVING_STEP 10


/**
  * \brief Vitesse initiale de déplacement vertical des éléments du jeu 
*/

#define INITIAL_SPEED 2




/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* sprite;
};
/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;




/**
 * \brief Représentation des parametres du sprite du jeu
*/
struct sprite_s{
    int x;
    int y;
    int h;
    int w;

};
/**
 * \brief Type qui correspond au sprite
*/
typedef struct sprite_s sprite_t;




/**
 * \brief Représentation du monde du jeu
*/
struct world_s{

    sprite_t vaisseau;
    
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;


/*===================== FONCTIONS ========================*/




/**
 * \brief
 * \param
 * \param
*/
void print_sprite(sprite_t *sprite){
    printf("Sprite: Coordonees: (x=%i, y=%i) ; Hauteur = %i ; Largeur = %i\n\n", sprite->x, sprite->y, sprite->h, sprite->w);
}




/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world){

    world->vaisseau.x = (SCREEN_WIDTH-SHIP_SIZE)/2;
    world->vaisseau.y = SCREEN_HEIGHT-SHIP_SIZE;
    world->vaisseau.w = SHIP_SIZE;
    world->vaisseau.h = SHIP_SIZE;

    //on n'est pas à la fin du jeu
    world->gameover = 0;
    
}






/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}






/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}







/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    /* A COMPLETER */
}






/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'fleche droite'
            if(event->key.keysym.sym == SDLK_RIGHT){
                world->vaisseau.x+=MOVING_STEP;
            }
            else if(event->key.keysym.sym == SDLK_UP){
                world->vaisseau.y-=MOVING_STEP;
            }
            else if(event->key.keysym.sym == SDLK_LEFT){
                world->vaisseau.x-=MOVING_STEP;
            }
            else if(event->key.keysym.sym == SDLK_DOWN){
                world->vaisseau.y+=MOVING_STEP;
            }
            else if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover=1;
            }

            //print_sprite(&world->vaisseau);

        }
    }
}






/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);

    clean_texture(textures->sprite);
}






/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->sprite = load_image( "ressources/spaceship.bmp",renderer);
    
}



/**
 * \brief La fonction initialise les parametres nécessaires à l'affichage graphique du sprite
 * \param sprite: Le sprite
 * \param x,y: la position du sprite
 * \param w,h: taille du sprite
*/
void init_sprite(sprite_t *sprite, int x, int y, int w, int h){
    sprite->x=x;
    sprite->y=y;
    sprite->h=h;
    sprite->w=w;
}




/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/
void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
      apply_texture(texture, renderer, 0, 0);
    }
}




/**
 * \brief La fonction applique la texture du sprite sur le renderer
 * \param renderer le renderer
 * \param texture la texture liée au fond
* \param sprite le sprite a afficher
*/
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    if(texture != NULL){
        apply_texture(texture, renderer, sprite->x, sprite->y);
    }
}





/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures du background dans le renderer
    apply_background(renderer, textures->background);

    //application de la texture du sprite dans le renderer
    apply_sprite(renderer, textures->sprite, &world->vaisseau);

    // on met à jour l'écran
    update_screen(renderer);
}





/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}






/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param world le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}



/*=========================== MAIN ==============================*/



/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}