#include "tower.h"

//création d'une tour

Tower* createTower(int index,float x, float y, TypeTower type, Tower ** list)
{
    Tower * newTower = malloc(sizeof(Tower));
    if(newTower == NULL)
    {
        fprintf(stderr,"erreur allocation tour");
        exit(EXIT_FAILURE);
    }

    newTower->index=index;
    newTower->posX = x;
    newTower->posY = y;
    newTower->type = type;
    newTower->nextTower = NULL;

    Tower *tmp = *list;
    if(tmp == NULL){
        *list = newTower;
    }
    else{
        while(tmp->nextTower != NULL){
            tmp = tmp->nextTower;
        }
        tmp->nextTower = newTower;
    }

    switch(type){
        case ROCKET:
            newTower->puissance = 10;
            newTower->portee = 50;
            newTower->cadence = 5;
            newTower->cout = 300;
            break;
        case LASER:
            newTower->puissance = 40;
            newTower->portee = 15;
            newTower->cadence= 15;
            newTower->cout = 350;
            break;
        case MITRAILLETTE:
            newTower->puissance = 30;
            newTower->portee = 20;
            newTower->cadence= 10;
            newTower->cout = 450;
            break;
        case HYBRIDE:
            newTower->puissance = 30;
            newTower->portee = 30;
            newTower->cadence= 10;
            newTower->cout = 500;
            break;

        default:
            break;
    }
    printf("Tour créé yeaaaaaah\n");
   return newTower; 
}


//choix de la tour depuis le menu
TypeTower choixTower(int clickX, int clickY){
    TypeTower type;

    //choix rocket
    if(clickX > 337 && clickX < 385 && clickY > 564 && clickY < 612){
        type = ROCKET;
        printf("OK rocket\n");
    }
    //choix laser
    else if(clickX > 404 && clickX < 454 && clickY > 564 && clickY < 612){
        type = LASER;
        printf("OK laser\n");
    }
    //choix mitraillette
    else if(clickX > 474 && clickX < 521 && clickY > 564 && clickY < 612){
        type = MITRAILLETTE;
        printf("OK mitraillette\n");
    }
    //choix 
    else if(clickX > 541 && clickX < 589 && clickY > 564 && clickY < 612){
        type = HYBRIDE;
        printf("OK hybride\n");
    }
    else{
        fprintf(stderr, "erreur lors du choix du type\n");
    }
    return type;
}

//construction de la tour

void constructTower(Tower** list){
    GLuint tower_texture;
    Tower *tmp = *list;
    while(tmp != NULL)
    {
        
        switch(tmp->type){
            case ROCKET:
                tower_texture = Texture_Load("./images/tower_rocket.png", 31, 31);
                break;
            case LASER:
                tower_texture = Texture_Load("./images/tower_laser.png", 31, 31);
                break;
            case MITRAILLETTE:
                tower_texture = Texture_Load("./images/tower_mitraillette.png", 31, 31);
                break;
            case HYBRIDE:
                tower_texture = Texture_Load("./images/tower_hybride.png", 31, 31);
                break;
            default:
                break;
        
    }

    float posY = 1 - (tmp->posY/630.0);
    float posX = tmp->posX/630.0;
    drawMap(tower_texture, posX, posY , 0.05, 0.05);

        tmp = tmp->nextTower;
    }
}

int countTower(TypeTower type){
    int cout;
    if(type == ROCKET)
    {
       cout = 300; 
    }
    if(type == LASER)
    {
       cout = 350; 
    }
    if(type == MITRAILLETTE)
    {
       cout = 450; 
    }
    if(type == HYBRIDE)
    {
       cout = 500; 
    }
    return cout;
}

Tower * getTower(int index, Tower * listTower){
    if(listTower == NULL){
        fprintf(stderr, "erreur liste nulle\n");
        return NULL;
    }
    else{
        Tower *actuel = listTower;
        while(actuel != NULL){
            if(actuel->index == index)
            {
                return actuel;
            }
            actuel = actuel->nextTower;
        }
        return NULL;
    }
}