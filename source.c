#include "header.h"

enum
{
    ENNEMI_IDLE = 0,
    ENNEMI_RUN = 1,
    ENNEMI_JUMP = 2,
    ENNEMI_ATTACK = 3
};

static const int FRAMES_PAR_ETAT_ENNEMI[4] = {4, 6, 2, 6};

static SDL_Texture *creerTextureObstacleDefaut(SDL_Renderer *rendu)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect pic;

    surface = SDL_CreateRGBSurfaceWithFormat(0, 42, 44, 32, SDL_PIXELFORMAT_RGBA32);
    if (surface == NULL)
    {
        return NULL;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

    /* Base rocheuse */
    pic = (SDL_Rect){0, 16, 42, 28};
    SDL_FillRect(surface, &pic, SDL_MapRGB(surface->format, 118, 86, 66));
    pic = (SDL_Rect){0, 16, 42, 4};
    SDL_FillRect(surface, &pic, SDL_MapRGB(surface->format, 146, 111, 86));

    /* Pointes simples pour un obstacle lisible */
    pic = (SDL_Rect){4, 6, 8, 12};
    SDL_FillRect(surface, &pic, SDL_MapRGB(surface->format, 170, 170, 176));
    pic = (SDL_Rect){16, 2, 10, 16};
    SDL_FillRect(surface, &pic, SDL_MapRGB(surface->format, 188, 188, 195));
    pic = (SDL_Rect){30, 7, 8, 11};
    SDL_FillRect(surface, &pic, SDL_MapRGB(surface->format, 170, 170, 176));

    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}

static SDL_Texture *creerTextureEnnemiSpritesheetDefaut(SDL_Renderer *rendu)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect corps;
    SDL_Rect tete;
    SDL_Rect yeux;
    SDL_Rect bouche;
    SDL_Rect jambeA;
    SDL_Rect jambeB;
    SDL_Rect brasA;
    SDL_Rect brasB;
    SDL_Rect corneA;
    SDL_Rect corneB;
    SDL_Rect frameRect;
    int dirOffset;
    int frameX;
    int frameY;
    int rangee;
    int col;
    int sens;
    int etat;
    int frameEtat;
    int totalCols;
    int totalRows;
    int frameW;
    int frameH;
    Uint32 couleurCorpsClair;
    Uint32 couleurCorpsFonce;
    Uint32 couleurOeil;
    Uint32 couleurCorne;
    Uint32 couleurBouche;

    totalCols = 6;
    totalRows = 8;
    frameW = 64;
    frameH = 64;
    surface = SDL_CreateRGBSurfaceWithFormat(0, totalCols * frameW, totalRows * frameH, 32, SDL_PIXELFORMAT_RGBA32);
    if (surface == NULL)
    {
        return NULL;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

    couleurCorpsClair = SDL_MapRGB(surface->format, 174, 84, 214);
    couleurCorpsFonce = SDL_MapRGB(surface->format, 104, 46, 148);
    couleurOeil = SDL_MapRGB(surface->format, 240, 235, 120);
    couleurCorne = SDL_MapRGB(surface->format, 200, 200, 220);
    couleurBouche = SDL_MapRGB(surface->format, 70, 30, 96);

    for (rangee = 0; rangee < totalRows; rangee = rangee + 1)
    {
        sens = rangee >= 4 ? -1 : 1;
        etat = rangee % 4;
        for (col = 0; col < totalCols; col = col + 1)
        {
            frameRect = (SDL_Rect){col * frameW, rangee * frameH, frameW, frameH};
            SDL_FillRect(surface, &frameRect, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
            frameX = col * frameW;
            frameY = rangee * frameH;
            frameEtat = col;
            if (etat == ENNEMI_IDLE && col >= 4)
            {
                frameEtat = 3;
            }
            if (etat == ENNEMI_JUMP && col >= 2)
            {
                frameEtat = 1;
            }
            dirOffset = sens == 1 ? 0 : 4;

            if (etat == ENNEMI_ATTACK)
            {
                brasA = (SDL_Rect){frameX + 6 + dirOffset, frameY + 30 - (frameEtat % 2), 10, 8};
                brasB = (SDL_Rect){frameX + 48 - dirOffset, frameY + 30 + (frameEtat % 2), 10, 8};
            }
            else
            {
                brasA = (SDL_Rect){frameX + 9 + dirOffset, frameY + 34, 8, 7};
                brasB = (SDL_Rect){frameX + 47 - dirOffset, frameY + 34, 8, 7};
            }
            jambeA = (SDL_Rect){frameX + 20 + ((etat == ENNEMI_RUN) ? (frameEtat % 3) : 0), frameY + 49, 10, 11};
            jambeB = (SDL_Rect){frameX + 34 - ((etat == ENNEMI_RUN) ? (frameEtat % 3) : 0), frameY + 49, 10, 11};
            corps = (SDL_Rect){frameX + 15, frameY + 28, 34, 23};
            tete = (SDL_Rect){frameX + 19, frameY + 13, 26, 16};
            yeux = (SDL_Rect){frameX + (sens == 1 ? 25 : 21), frameY + 19, 5, 5};
            bouche = (SDL_Rect){frameX + (sens == 1 ? 32 : 27), frameY + 22, 8, 3};
            corneA = (SDL_Rect){frameX + 21, frameY + 9, 4, 5};
            corneB = (SDL_Rect){frameX + 39, frameY + 9, 4, 5};

            if (etat == ENNEMI_JUMP)
            {
                corps.y = corps.y - 5;
                tete.y = tete.y - 5;
                yeux.y = yeux.y - 5;
                bouche.y = bouche.y - 5;
                jambeA.y = jambeA.y - 4;
                jambeB.y = jambeB.y - 4;
                corneA.y = corneA.y - 5;
                corneB.y = corneB.y - 5;
                brasA.y = brasA.y - 4;
                brasB.y = brasB.y - 4;
            }

            SDL_FillRect(surface, &jambeB, couleurCorpsFonce);
            SDL_FillRect(surface, &jambeA, couleurCorpsFonce);
            SDL_FillRect(surface, &brasA, couleurCorpsFonce);
            SDL_FillRect(surface, &brasB, couleurCorpsFonce);
            SDL_FillRect(surface, &corps, couleurCorpsClair);
            SDL_FillRect(surface, &tete, couleurCorpsClair);
            SDL_FillRect(surface, &corneA, couleurCorne);
            SDL_FillRect(surface, &corneB, couleurCorne);
            SDL_FillRect(surface, &yeux, couleurOeil);
            SDL_FillRect(surface, &bouche, couleurBouche);
        }
    }

    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}

static void placerObstaclesSurSupports(DonneesJeu *jeu)
{
    int i;
    int j;
    int supportY;
    int obstacleX1;
    int obstacleX2;
    int platX1;
    int platX2;

    for (i = 0; i < jeu->nbObstacles; i = i + 1)
    {
        supportY = jeu->hauteurNiveau - 10;
        obstacleX1 = jeu->obstacles[i].zone.x;
        obstacleX2 = jeu->obstacles[i].zone.x + jeu->obstacles[i].zone.w;
        for (j = 0; j < jeu->nbPlateformes; j = j + 1)
        {
            if (jeu->plateformes[j].active == 0)
            {
                continue;
            }
            platX1 = jeu->plateformes[j].zone.x;
            platX2 = jeu->plateformes[j].zone.x + jeu->plateformes[j].zone.w;
            if (obstacleX2 > platX1 && obstacleX1 < platX2)
            {
                if (jeu->plateformes[j].zone.y <= jeu->hauteurNiveau - 10 && jeu->plateformes[j].zone.y > supportY - 160)
                {
                    if (jeu->plateformes[j].zone.y < supportY)
                    {
                        supportY = jeu->plateformes[j].zone.y;
                    }
                }
            }
        }
        jeu->obstacles[i].zone.y = supportY - jeu->obstacles[i].zone.h;
    }
}

static void agrandirRectObstacleAffichage(SDL_Rect *zone)
{
    int largeurOriginale;
    int hauteurOriginale;
    int largeurNouvelle;
    int hauteurNouvelle;

    largeurOriginale = zone->w;
    hauteurOriginale = zone->h;
    largeurNouvelle = (largeurOriginale * 18) / 10;
    hauteurNouvelle = (hauteurOriginale * 18) / 10;
    zone->x = zone->x - (largeurNouvelle - largeurOriginale) / 2;
    zone->y = zone->y - (hauteurNouvelle - hauteurOriginale);
    zone->w = largeurNouvelle;
    zone->h = hauteurNouvelle;
}

int initialiserJeu(DonneesJeu *jeu, int niveau)
{
    int i;
    int textureW;
    int textureH;
    SDL_Texture *backgroundActif;
    SDL_Surface *surfaceSecours;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init erreur: %s\n", SDL_GetError());
        return -1;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
        fprintf(stderr, "IMG_Init erreur: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }
    jeu->fenetre = SDL_CreateWindow("Jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);
    if (jeu->fenetre == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow erreur: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    if (TTF_Init() == -1)
    {
        SDL_DestroyRenderer(jeu->rendu);
        SDL_DestroyWindow(jeu->fenetre);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    jeu->police = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 14);
    if (jeu->police == NULL)
    {
        jeu->police = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 14);
    }
    jeu->rendu = SDL_CreateRenderer(jeu->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (jeu->rendu == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer erreur: %s\n", SDL_GetError());
        SDL_DestroyWindow(jeu->fenetre);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    jeu->backgroundNiveau1 = IMG_LoadTexture(jeu->rendu, "background.png");
    jeu->backgroundNiveau2 = IMG_LoadTexture(jeu->rendu, "5.png");
    if (jeu->backgroundNiveau1 == NULL)
    {
        surfaceSecours = SDL_CreateRGBSurfaceWithFormat(0, 2200, 600, 32, SDL_PIXELFORMAT_RGBA32);
        if (surfaceSecours != NULL)
        {
            SDL_FillRect(surfaceSecours, NULL, SDL_MapRGB(surfaceSecours->format, 25, 90, 140));
            jeu->backgroundNiveau1 = SDL_CreateTextureFromSurface(jeu->rendu, surfaceSecours);
            SDL_FreeSurface(surfaceSecours);
        }
    }
    if (jeu->backgroundNiveau2 == NULL)
    {
        surfaceSecours = SDL_CreateRGBSurfaceWithFormat(0, 2600, 600, 32, SDL_PIXELFORMAT_RGBA32);
        if (surfaceSecours != NULL)
        {
            SDL_FillRect(surfaceSecours, NULL, SDL_MapRGB(surfaceSecours->format, 120, 70, 95));
            jeu->backgroundNiveau2 = SDL_CreateTextureFromSurface(jeu->rendu, surfaceSecours);
            SDL_FreeSurface(surfaceSecours);
        }
    }
    if (jeu->backgroundNiveau1 == NULL || jeu->backgroundNiveau2 == NULL)
    {
        fprintf(stderr, "IMG_LoadTexture erreur: %s\n", IMG_GetError());
        if (jeu->backgroundNiveau1 != NULL)
        {
            SDL_DestroyTexture(jeu->backgroundNiveau1);
        }
        if (jeu->backgroundNiveau2 != NULL)
        {
            SDL_DestroyTexture(jeu->backgroundNiveau2);
        }
        SDL_DestroyRenderer(jeu->rendu);
        SDL_DestroyWindow(jeu->fenetre);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    for (i = 0; i < NB_TEXTURES_OBSTACLES; i = i + 1)
    {
        jeu->texturesObstacles[i] = NULL;
    }
    jeu->texturesObstacles[OBSTACLE_ROUE] = IMG_LoadTexture(jeu->rendu, "roue.png");
    if (jeu->texturesObstacles[OBSTACLE_ROUE] == NULL)
    {
        jeu->texturesObstacles[OBSTACLE_ROUE] = IMG_LoadTexture(jeu->rendu, "images/roue.png");
    }
    jeu->texturesObstacles[OBSTACLE_BOX] = IMG_LoadTexture(jeu->rendu, "box.png");
    if (jeu->texturesObstacles[OBSTACLE_BOX] == NULL)
    {
        jeu->texturesObstacles[OBSTACLE_BOX] = IMG_LoadTexture(jeu->rendu, "images/box.png");
    }
    jeu->texturesObstacles[OBSTACLE_BARREL] = IMG_LoadTexture(jeu->rendu, "barrel.png");
    if (jeu->texturesObstacles[OBSTACLE_BARREL] == NULL)
    {
        jeu->texturesObstacles[OBSTACLE_BARREL] = IMG_LoadTexture(jeu->rendu, "images/barrel.png");
    }
    for (i = 0; i < NB_TEXTURES_OBSTACLES; i = i + 1)
    {
        if (jeu->texturesObstacles[i] == NULL)
        {
            jeu->texturesObstacles[i] = creerTextureObstacleDefaut(jeu->rendu);
        }
    }
    jeu->textureEnnemi = IMG_LoadTexture(jeu->rendu, "ennemi.png");
    if (jeu->textureEnnemi == NULL)
    {
        jeu->textureEnnemi = IMG_LoadTexture(jeu->rendu, "enemy.png");
    }
    if (jeu->textureEnnemi == NULL)
    {
        jeu->textureEnnemi = IMG_LoadTexture(jeu->rendu, "images/ennemi.png");
    }
    if (jeu->textureEnnemi == NULL)
    {
        jeu->textureEnnemi = IMG_LoadTexture(jeu->rendu, "images/enemy.png");
    }
    if (jeu->textureEnnemi == NULL)
    {
        jeu->textureEnnemi = creerTextureEnnemiSpritesheetDefaut(jeu->rendu);
    }
    jeu->frameEnnemi = 0;
    jeu->nbFramesEnnemi = 6;
    jeu->nbLignesEnnemi = 8;
    jeu->frameLargeurEnnemi = 45;
    jeu->frameHauteurEnnemi = 70;
    jeu->etatEnnemi = ENNEMI_RUN;
    jeu->dernierTickEnnemi = SDL_GetTicks();
    jeu->finAttaqueEnnemi = 0;
    jeu->finIdleEnnemi = 0;
    if (jeu->textureEnnemi != NULL)
    {
        SDL_QueryTexture(jeu->textureEnnemi, NULL, NULL, &textureW, &textureH);
        if (textureW > 0 && textureH > 0)
        {
            if (textureW >= 6 && textureH >= 8 && textureW % 6 == 0 && textureH % 8 == 0)
            {
                jeu->nbFramesEnnemi = 6;
                jeu->nbLignesEnnemi = 8;
                jeu->frameLargeurEnnemi = textureW / 6;
                jeu->frameHauteurEnnemi = textureH / 8;
            }
            else if (textureH > 0)
            {
                jeu->nbFramesEnnemi = textureW / textureH;
                if (jeu->nbFramesEnnemi <= 0)
                {
                    jeu->nbFramesEnnemi = 1;
                }
                jeu->nbLignesEnnemi = 1;
                jeu->frameLargeurEnnemi = textureW / jeu->nbFramesEnnemi;
                jeu->frameHauteurEnnemi = textureH;
            }
        }
    }

    jeu->niveau = niveau;
    if (niveau == NIVEAU_1)
    {
        backgroundActif = jeu->backgroundNiveau1;
    }
    else
    {
        backgroundActif = jeu->backgroundNiveau2;
    }
    SDL_QueryTexture(backgroundActif, NULL, NULL, &jeu->largeurNiveau, &jeu->hauteurNiveau);
    jeu->modeAffichage = MODE_MULTI;
    jeu->score = 0;
    jeu->vies = 3;
    jeu->continuer = 1;
    jeu->afficherGuide = 1;
    jeu->modeSauvegarde = 0;
    jeu->scoreEnregistre = 0;
    jeu->nomJoueur[0] = '\0';
    jeu->longueurNom = 0;
    jeu->tempsDebut = SDL_GetTicks();
    jeu->dernierDegat = SDL_GetTicks();

    jeu->joueur1.x = 120;
    jeu->joueur1.y = 460;
    jeu->joueur1.w = 40;
    jeu->joueur1.h = 60;
    jeu->joueur2.x = 200;
    jeu->joueur2.y = 460;
    jeu->joueur2.w = 40;
    jeu->joueur2.h = 60;
    jeu->vitesseY1 = 0;
    jeu->vitesseY2 = 0;
    jeu->auSol1 = 0;
    jeu->auSol2 = 0;

    jeu->camera1.x = 0;
    jeu->camera1.y = 0;
    jeu->camera1.w = LARGEUR_FENETRE / 2;
    jeu->camera1.h = HAUTEUR_FENETRE;
    jeu->camera2.x = 0;
    jeu->camera2.y = 0;
    jeu->camera2.w = LARGEUR_FENETRE / 2;
    jeu->camera2.h = HAUTEUR_FENETRE;
    jeu->ecran1.x = 0;
    jeu->ecran1.y = 0;
    jeu->ecran1.w = LARGEUR_FENETRE / 2;
    jeu->ecran1.h = HAUTEUR_FENETRE;
    jeu->ecran2.x = LARGEUR_FENETRE / 2;
    jeu->ecran2.y = 0;
    jeu->ecran2.w = LARGEUR_FENETRE / 2;
    jeu->ecran2.h = HAUTEUR_FENETRE;

    if (niveau == NIVEAU_1)
    {
        jeu->nbPlateformes = 4;
        jeu->plateformes[0].zone = (SDL_Rect){180, 510, 180, 20};
        jeu->plateformes[1].zone = (SDL_Rect){480, 430, 180, 20};
        jeu->plateformes[2].zone = (SDL_Rect){860, 360, 180, 20};
        jeu->plateformes[3].zone = (SDL_Rect){1220, 470, 180, 20};
        jeu->plateformes[0].type = 0;
        jeu->plateformes[1].type = 1;
        jeu->plateformes[2].type = 2;
        jeu->plateformes[3].type = 0;
        for (i = 0; i < jeu->nbPlateformes; i = i + 1)
        {
            jeu->plateformes[i].active = 1;
            jeu->plateformes[i].direction = 1;
        }
        jeu->plateformes[1].borneMinX = 420;
        jeu->plateformes[1].borneMaxX = 760;

        jeu->nbObstacles = 3;
        jeu->obstacles[0].zone = (SDL_Rect){640, 560, 35, 35};
        jeu->obstacles[0].typeImage = OBSTACLE_ROUE;
        jeu->obstacles[1].zone = (SDL_Rect){980, 550, 40, 45};
        jeu->obstacles[1].typeImage = OBSTACLE_BOX;
        jeu->obstacles[2].zone = (SDL_Rect){1320, 555, 35, 40};
        jeu->obstacles[2].typeImage = OBSTACLE_BARREL;
        for (i = 0; i < jeu->nbObstacles; i = i + 1)
        {
            jeu->obstacles[i].degats = 1;
        }
        /* Niveau 2: obstacles alignes sur le meme plan que les joueurs. */
        for (i = 0; i < jeu->nbObstacles; i = i + 1)
        {
            jeu->obstacles[i].zone.y = jeu->hauteurNiveau - 10 - jeu->obstacles[i].zone.h;
        }

        jeu->nbPieces = 5;
        jeu->pieces[0].zone = (SDL_Rect){250, 470, 18, 18};
        jeu->pieces[1].zone = (SDL_Rect){560, 390, 18, 18};
        jeu->pieces[2].zone = (SDL_Rect){930, 320, 18, 18};
        jeu->pieces[3].zone = (SDL_Rect){1280, 430, 18, 18};
        jeu->pieces[4].zone = (SDL_Rect){1700, 500, 18, 18};
        for (i = 0; i < jeu->nbPieces; i = i + 1)
        {
            jeu->pieces[i].actif = 1;
        }

        jeu->ennemi.zone = (SDL_Rect){1500, 520, 45, 70};
        jeu->ennemi.actif = 1;
        jeu->ennemi.direction = -1;
        jeu->ennemi.vitesse = 2;
        jeu->ennemi.borneMinX = 1340;
        jeu->ennemi.borneMaxX = 1760;
        jeu->ennemi.degats = 1;
    }
    else
    {
        jeu->nbPlateformes = 5;
        jeu->plateformes[0].zone = (SDL_Rect){120, 520, 170, 20};
        jeu->plateformes[1].zone = (SDL_Rect){390, 460, 170, 20};
        jeu->plateformes[2].zone = (SDL_Rect){740, 400, 170, 20};
        jeu->plateformes[3].zone = (SDL_Rect){1080, 360, 170, 20};
        jeu->plateformes[4].zone = (SDL_Rect){1420, 470, 170, 20};
        jeu->plateformes[0].type = 0;
        jeu->plateformes[1].type = 1;
        jeu->plateformes[2].type = 2;
        jeu->plateformes[3].type = 1;
        jeu->plateformes[4].type = 0;
        for (i = 0; i < jeu->nbPlateformes; i = i + 1)
        {
            jeu->plateformes[i].active = 1;
            jeu->plateformes[i].direction = 1;
        }
        jeu->plateformes[1].borneMinX = 320;
        jeu->plateformes[1].borneMaxX = 680;
        jeu->plateformes[3].borneMinX = 980;
        jeu->plateformes[3].borneMaxX = 1260;

        jeu->nbObstacles = 4;
        jeu->obstacles[0].zone = (SDL_Rect){(jeu->largeurNiveau * 30) / 100, 560, 34, 34};
        jeu->obstacles[0].typeImage = OBSTACLE_ROUE;
        jeu->obstacles[1].zone = (SDL_Rect){(jeu->largeurNiveau * 48) / 100, 555, 38, 38};
        jeu->obstacles[1].typeImage = OBSTACLE_BOX;
        jeu->obstacles[2].zone = (SDL_Rect){(jeu->largeurNiveau * 64) / 100, 550, 42, 42};
        jeu->obstacles[2].typeImage = OBSTACLE_BARREL;
        jeu->obstacles[3].zone = (SDL_Rect){(jeu->largeurNiveau * 80) / 100, 548, 44, 44};
        jeu->obstacles[3].typeImage = OBSTACLE_ROUE;
        for (i = 0; i < jeu->nbObstacles; i = i + 1)
        {
            jeu->obstacles[i].degats = 1;
        }
        placerObstaclesSurSupports(jeu);

        jeu->nbPieces = 6;
        jeu->pieces[0].zone = (SDL_Rect){180, 490, 18, 18};
        jeu->pieces[1].zone = (SDL_Rect){460, 430, 18, 18};
        jeu->pieces[2].zone = (SDL_Rect){800, 370, 18, 18};
        jeu->pieces[3].zone = (SDL_Rect){1140, 330, 18, 18};
        jeu->pieces[4].zone = (SDL_Rect){1480, 440, 18, 18};
        jeu->pieces[5].zone = (SDL_Rect){2060, 500, 18, 18};
        for (i = 0; i < jeu->nbPieces; i = i + 1)
        {
            jeu->pieces[i].actif = 1;
        }

        jeu->ennemi.zone = (SDL_Rect){1840, 520, 45, 70};
        jeu->ennemi.actif = 1;
        jeu->ennemi.direction = 1;
        jeu->ennemi.vitesse = 3;
        jeu->ennemi.borneMinX = 1720;
        jeu->ennemi.borneMaxX = 2140;
        jeu->ennemi.degats = 1;
    }
    return 0;
}

void mettreAJourJeu(DonneesJeu *jeu, const Uint8 *clavier)
{
    int i;
    int collisionP1;
    int collisionP2;
    SDL_Rect testCollision;
    SDL_Rect testPiece;
    Uint32 maintenant;
    int centerX;
    int centerY;
    int joueurYEcran;
    int limiteHaute;
    int limiteBasse;
    int scoreSauve;
    int viesSauvees;
    int modeSauve;
    Uint32 tempsSauve;
    int contactDessusObstacle;

    if (jeu->modeSauvegarde == 1)
    {
        return;
    }

    if (jeu->modeAffichage == MODE_MONO)
    {
        jeu->camera1.w = LARGEUR_FENETRE;
        jeu->camera1.h = HAUTEUR_FENETRE;
    }
    else
    {
        jeu->camera1.w = LARGEUR_FENETRE / 2;
        jeu->camera1.h = HAUTEUR_FENETRE;
        jeu->camera2.w = LARGEUR_FENETRE / 2;
        jeu->camera2.h = HAUTEUR_FENETRE;
    }

    if (clavier[SDL_SCANCODE_RIGHT])
    {
        jeu->joueur1.x = jeu->joueur1.x + 4;
    }
    if (clavier[SDL_SCANCODE_LEFT])
    {
        jeu->joueur1.x = jeu->joueur1.x - 4;
    }
    if (clavier[SDL_SCANCODE_D])
    {
        jeu->joueur2.x = jeu->joueur2.x + 4;
    }
    if (clavier[SDL_SCANCODE_Q])
    {
        jeu->joueur2.x = jeu->joueur2.x - 4;
    }

    jeu->vitesseY1 = jeu->vitesseY1 + 1;
    jeu->vitesseY2 = jeu->vitesseY2 + 1;
    if (jeu->vitesseY1 > 12)
    {
        jeu->vitesseY1 = 12;
    }
    if (jeu->vitesseY2 > 12)
    {
        jeu->vitesseY2 = 12;
    }
    jeu->joueur1.y = jeu->joueur1.y + jeu->vitesseY1;
    jeu->joueur2.y = jeu->joueur2.y + jeu->vitesseY2;
    jeu->auSol1 = 0;
    jeu->auSol2 = 0;
    collisionP1 = 0;
    collisionP2 = 0;
    contactDessusObstacle = 0;

    for (i = 0; i < jeu->nbPlateformes; i = i + 1)
    {
        if (jeu->plateformes[i].active == 1)
        {
            testCollision = jeu->plateformes[i].zone;
            if (jeu->joueur1.x + jeu->joueur1.w > testCollision.x && jeu->joueur1.x < testCollision.x + testCollision.w)
            {
                if (jeu->joueur1.y + jeu->joueur1.h >= testCollision.y && jeu->joueur1.y + jeu->joueur1.h <= testCollision.y + 18 && jeu->vitesseY1 >= 0)
                {
                    jeu->joueur1.y = testCollision.y - jeu->joueur1.h;
                    jeu->vitesseY1 = 0;
                    jeu->auSol1 = 1;
                    collisionP1 = 1;
                    if (jeu->plateformes[i].type == 2)
                    {
                        jeu->plateformes[i].active = 0;
                    }
                }
            }
            if (jeu->joueur2.x + jeu->joueur2.w > testCollision.x && jeu->joueur2.x < testCollision.x + testCollision.w)
            {
                if (jeu->joueur2.y + jeu->joueur2.h >= testCollision.y && jeu->joueur2.y + jeu->joueur2.h <= testCollision.y + 18 && jeu->vitesseY2 >= 0)
                {
                    jeu->joueur2.y = testCollision.y - jeu->joueur2.h;
                    jeu->vitesseY2 = 0;
                    jeu->auSol2 = 1;
                    collisionP2 = 1;
                    if (jeu->plateformes[i].type == 2)
                    {
                        jeu->plateformes[i].active = 0;
                    }
                }
            }
        }
    }

    /* Les obstacles (roues) deviennent des supports solides comme les plateformes */
    for (i = 0; i < jeu->nbObstacles; i = i + 1)
    {
        testCollision = jeu->obstacles[i].zone;
        if (jeu->joueur1.x + jeu->joueur1.w > testCollision.x && jeu->joueur1.x < testCollision.x + testCollision.w)
        {
            if (jeu->joueur1.y + jeu->joueur1.h >= testCollision.y && jeu->joueur1.y + jeu->joueur1.h <= testCollision.y + 16 && jeu->vitesseY1 >= 0)
            {
                jeu->joueur1.y = testCollision.y - jeu->joueur1.h;
                jeu->vitesseY1 = 0;
                jeu->auSol1 = 1;
                collisionP1 = 1;
            }
        }
        if (jeu->joueur2.x + jeu->joueur2.w > testCollision.x && jeu->joueur2.x < testCollision.x + testCollision.w)
        {
            if (jeu->joueur2.y + jeu->joueur2.h >= testCollision.y && jeu->joueur2.y + jeu->joueur2.h <= testCollision.y + 16 && jeu->vitesseY2 >= 0)
            {
                jeu->joueur2.y = testCollision.y - jeu->joueur2.h;
                jeu->vitesseY2 = 0;
                jeu->auSol2 = 1;
                collisionP2 = 1;
            }
        }
    }

    if (collisionP1 == 0 && jeu->joueur1.y + jeu->joueur1.h >= jeu->hauteurNiveau - 10)
    {
        jeu->joueur1.y = jeu->hauteurNiveau - 10 - jeu->joueur1.h;
        jeu->vitesseY1 = 0;
        jeu->auSol1 = 1;
    }
    if (collisionP2 == 0 && jeu->joueur2.y + jeu->joueur2.h >= jeu->hauteurNiveau - 10)
    {
        jeu->joueur2.y = jeu->hauteurNiveau - 10 - jeu->joueur2.h;
        jeu->vitesseY2 = 0;
        jeu->auSol2 = 1;
    }

    if (jeu->joueur1.x < 0)
    {
        jeu->joueur1.x = 0;
    }
    if (jeu->joueur2.x < 0)
    {
        jeu->joueur2.x = 0;
    }
    if (jeu->joueur1.x > jeu->largeurNiveau - jeu->joueur1.w)
    {
        jeu->joueur1.x = jeu->largeurNiveau - jeu->joueur1.w;
    }
    if (jeu->joueur2.x > jeu->largeurNiveau - jeu->joueur2.w)
    {
        jeu->joueur2.x = jeu->largeurNiveau - jeu->joueur2.w;
    }

    for (i = 0; i < jeu->nbPlateformes; i = i + 1)
    {
        if (jeu->plateformes[i].active == 1 && jeu->plateformes[i].type == 1)
        {
            jeu->plateformes[i].zone.x = jeu->plateformes[i].zone.x + 2 * jeu->plateformes[i].direction;
            if (jeu->plateformes[i].zone.x <= jeu->plateformes[i].borneMinX)
            {
                jeu->plateformes[i].zone.x = jeu->plateformes[i].borneMinX;
                jeu->plateformes[i].direction = 1;
            }
            if (jeu->plateformes[i].zone.x >= jeu->plateformes[i].borneMaxX)
            {
                jeu->plateformes[i].zone.x = jeu->plateformes[i].borneMaxX;
                jeu->plateformes[i].direction = -1;
            }
        }
    }

    maintenant = SDL_GetTicks();
    if (jeu->ennemi.actif == 1)
    {
        int overlapY;
        int distJ1;
        int distJ2;
        int distMin;
        int etatPrecedent;
        int intervalleAnim;
        int framesEtat;
        int centreEnnemi;
        int centreJ1;
        int centreJ2;

        if (maintenant >= jeu->finIdleEnnemi)
        {
            jeu->ennemi.zone.x = jeu->ennemi.zone.x + jeu->ennemi.direction * jeu->ennemi.vitesse;
            if (jeu->ennemi.zone.x <= jeu->ennemi.borneMinX)
            {
                jeu->ennemi.zone.x = jeu->ennemi.borneMinX;
                jeu->ennemi.direction = 1;
                jeu->finIdleEnnemi = maintenant + 180;
            }
            if (jeu->ennemi.zone.x >= jeu->ennemi.borneMaxX)
            {
                jeu->ennemi.zone.x = jeu->ennemi.borneMaxX;
                jeu->ennemi.direction = -1;
                jeu->finIdleEnnemi = maintenant + 180;
            }
        }

        overlapY = (jeu->joueur1.y + jeu->joueur1.h > jeu->ennemi.zone.y && jeu->joueur1.y < jeu->ennemi.zone.y + jeu->ennemi.zone.h) ||
                   (jeu->joueur2.y + jeu->joueur2.h > jeu->ennemi.zone.y && jeu->joueur2.y < jeu->ennemi.zone.y + jeu->ennemi.zone.h);
        centreEnnemi = jeu->ennemi.zone.x + jeu->ennemi.zone.w / 2;
        centreJ1 = jeu->joueur1.x + jeu->joueur1.w / 2;
        centreJ2 = jeu->joueur2.x + jeu->joueur2.w / 2;
        distJ1 = centreEnnemi > centreJ1 ? centreEnnemi - centreJ1 : centreJ1 - centreEnnemi;
        distJ2 = centreEnnemi > centreJ2 ? centreEnnemi - centreJ2 : centreJ2 - centreEnnemi;
        distMin = distJ1 < distJ2 ? distJ1 : distJ2;
        if (overlapY && distMin < 86)
        {
            jeu->finAttaqueEnnemi = maintenant + 240;
        }

        etatPrecedent = jeu->etatEnnemi;
        if (maintenant < jeu->finAttaqueEnnemi)
        {
            jeu->etatEnnemi = ENNEMI_ATTACK;
        }
        else if (jeu->ennemi.zone.y + jeu->ennemi.zone.h < jeu->hauteurNiveau - 10)
        {
            jeu->etatEnnemi = ENNEMI_JUMP;
        }
        else if (maintenant < jeu->finIdleEnnemi || jeu->ennemi.vitesse == 0)
        {
            jeu->etatEnnemi = ENNEMI_IDLE;
        }
        else
        {
            jeu->etatEnnemi = ENNEMI_RUN;
        }

        if (jeu->etatEnnemi != etatPrecedent)
        {
            jeu->frameEnnemi = 0;
            jeu->dernierTickEnnemi = maintenant;
        }

        if (jeu->etatEnnemi == ENNEMI_IDLE)
        {
            intervalleAnim = 180;
        }
        else if (jeu->etatEnnemi == ENNEMI_RUN)
        {
            intervalleAnim = 95;
        }
        else if (jeu->etatEnnemi == ENNEMI_JUMP)
        {
            intervalleAnim = 140;
        }
        else
        {
            intervalleAnim = 85;
        }
        framesEtat = FRAMES_PAR_ETAT_ENNEMI[jeu->etatEnnemi];
        if (framesEtat <= 0)
        {
            framesEtat = 1;
        }
        if (maintenant - jeu->dernierTickEnnemi >= (Uint32)intervalleAnim)
        {
            jeu->dernierTickEnnemi = maintenant;
            jeu->frameEnnemi = (jeu->frameEnnemi + 1) % framesEtat;
        }
    }
    if (maintenant - jeu->dernierDegat > 500)
    {
        if (jeu->ennemi.actif == 1)
        {
            if (jeu->joueur1.x + jeu->joueur1.w > jeu->ennemi.zone.x && jeu->joueur1.x < jeu->ennemi.zone.x + jeu->ennemi.zone.w && jeu->joueur1.y + jeu->joueur1.h > jeu->ennemi.zone.y && jeu->joueur1.y < jeu->ennemi.zone.y + jeu->ennemi.zone.h)
            {
                jeu->vies = jeu->vies - jeu->ennemi.degats;
                jeu->dernierDegat = maintenant;
            }
            if (jeu->joueur2.x + jeu->joueur2.w > jeu->ennemi.zone.x && jeu->joueur2.x < jeu->ennemi.zone.x + jeu->ennemi.zone.w && jeu->joueur2.y + jeu->joueur2.h > jeu->ennemi.zone.y && jeu->joueur2.y < jeu->ennemi.zone.y + jeu->ennemi.zone.h)
            {
                jeu->vies = jeu->vies - jeu->ennemi.degats;
                jeu->dernierDegat = maintenant;
            }
        }
        for (i = 0; i < jeu->nbObstacles; i = i + 1)
        {
            if (jeu->joueur1.x + jeu->joueur1.w > jeu->obstacles[i].zone.x && jeu->joueur1.x < jeu->obstacles[i].zone.x + jeu->obstacles[i].zone.w && jeu->joueur1.y + jeu->joueur1.h > jeu->obstacles[i].zone.y && jeu->joueur1.y < jeu->obstacles[i].zone.y + jeu->obstacles[i].zone.h)
            {
                contactDessusObstacle = (jeu->joueur1.y + jeu->joueur1.h <= jeu->obstacles[i].zone.y + 8 && jeu->vitesseY1 >= 0);
                if (contactDessusObstacle == 0)
                {
                    jeu->vies = jeu->vies - jeu->obstacles[i].degats;
                    jeu->dernierDegat = maintenant;
                }
            }
            if (jeu->joueur2.x + jeu->joueur2.w > jeu->obstacles[i].zone.x && jeu->joueur2.x < jeu->obstacles[i].zone.x + jeu->obstacles[i].zone.w && jeu->joueur2.y + jeu->joueur2.h > jeu->obstacles[i].zone.y && jeu->joueur2.y < jeu->obstacles[i].zone.y + jeu->obstacles[i].zone.h)
            {
                contactDessusObstacle = (jeu->joueur2.y + jeu->joueur2.h <= jeu->obstacles[i].zone.y + 8 && jeu->vitesseY2 >= 0);
                if (contactDessusObstacle == 0)
                {
                    jeu->vies = jeu->vies - jeu->obstacles[i].degats;
                    jeu->dernierDegat = maintenant;
                }
            }
        }
    }

    for (i = 0; i < jeu->nbPieces; i = i + 1)
    {
        if (jeu->pieces[i].actif == 1)
        {
            testPiece = jeu->pieces[i].zone;
            if (jeu->joueur1.x + jeu->joueur1.w > testPiece.x && jeu->joueur1.x < testPiece.x + testPiece.w && jeu->joueur1.y + jeu->joueur1.h > testPiece.y && jeu->joueur1.y < testPiece.y + testPiece.h)
            {
                jeu->pieces[i].actif = 0;
                jeu->score = jeu->score + POINTS_PAR_PIECE;
            }
            else if (jeu->joueur2.x + jeu->joueur2.w > testPiece.x && jeu->joueur2.x < testPiece.x + testPiece.w && jeu->joueur2.y + jeu->joueur2.h > testPiece.y && jeu->joueur2.y < testPiece.y + testPiece.h)
            {
                jeu->pieces[i].actif = 0;
                jeu->score = jeu->score + POINTS_PAR_PIECE;
            }
        }
    }

    centerX = jeu->joueur1.x + jeu->joueur1.w / 2;
    if (jeu->modeAffichage == MODE_MONO)
    {
        jeu->camera1.x = centerX - jeu->camera1.w / 2;
        if (jeu->camera1.x < 0)
        {
            jeu->camera1.x = 0;
        }
        if (jeu->camera1.x > jeu->largeurNiveau - jeu->camera1.w)
        {
            jeu->camera1.x = jeu->largeurNiveau - jeu->camera1.w;
        }
    }
    else
    {
        centerX = jeu->joueur1.x + jeu->joueur1.w / 2;
        jeu->camera1.x = centerX - jeu->camera1.w / 2;
        if (jeu->camera1.x < 0)
        {
            jeu->camera1.x = 0;
        }
        if (jeu->camera1.x > jeu->largeurNiveau - jeu->camera1.w)
        {
            jeu->camera1.x = jeu->largeurNiveau - jeu->camera1.w;
        }
        centerX = jeu->joueur2.x + jeu->joueur2.w / 2;
        jeu->camera2.x = centerX - jeu->camera2.w / 2;
        if (jeu->camera2.x < 0)
        {
            jeu->camera2.x = 0;
        }
        if (jeu->camera2.x > jeu->largeurNiveau - jeu->camera2.w)
        {
            jeu->camera2.x = jeu->largeurNiveau - jeu->camera2.w;
        }
    }

    limiteHaute = jeu->camera1.h / 3;
    limiteBasse = (jeu->camera1.h * 2) / 3;
    centerY = jeu->joueur1.y + jeu->joueur1.h / 2;
    joueurYEcran = centerY - jeu->camera1.y;
    if (joueurYEcran < limiteHaute)
    {
        jeu->camera1.y = centerY - limiteHaute;
    }
    else if (joueurYEcran > limiteBasse)
    {
        jeu->camera1.y = centerY - limiteBasse;
    }
    if (jeu->camera1.y < 0)
    {
        jeu->camera1.y = 0;
    }
    if (jeu->camera1.y > jeu->hauteurNiveau - jeu->camera1.h)
    {
        jeu->camera1.y = jeu->hauteurNiveau - jeu->camera1.h;
    }

    limiteHaute = jeu->camera2.h / 3;
    limiteBasse = (jeu->camera2.h * 2) / 3;
    centerY = jeu->joueur2.y + jeu->joueur2.h / 2;
    joueurYEcran = centerY - jeu->camera2.y;
    if (joueurYEcran < limiteHaute)
    {
        jeu->camera2.y = centerY - limiteHaute;
    }
    else if (joueurYEcran > limiteBasse)
    {
        jeu->camera2.y = centerY - limiteBasse;
    }
    if (jeu->camera2.y < 0)
    {
        jeu->camera2.y = 0;
    }
    if (jeu->camera2.y > jeu->hauteurNiveau - jeu->camera2.h)
    {
        jeu->camera2.y = jeu->hauteurNiveau - jeu->camera2.h;
    }

    if (jeu->vies <= 0)
    {
        jeu->modeSauvegarde = 1;
    }
    if (jeu->modeSauvegarde == 0 && jeu->niveau == NIVEAU_1 && (jeu->joueur1.x >= jeu->largeurNiveau - jeu->joueur1.w - 10 || jeu->joueur2.x >= jeu->largeurNiveau - jeu->joueur2.w - 10))
    {
        scoreSauve = jeu->score;
        viesSauvees = jeu->vies;
        modeSauve = jeu->modeAffichage;
        tempsSauve = jeu->tempsDebut;
        if (jeu->rendu != NULL)
        {
            if (jeu->textureEnnemi != NULL)
            {
                SDL_DestroyTexture(jeu->textureEnnemi);
                jeu->textureEnnemi = NULL;
            }
            for (i = 0; i < NB_TEXTURES_OBSTACLES; i = i + 1)
            {
                if (jeu->texturesObstacles[i] != NULL)
                {
                    SDL_DestroyTexture(jeu->texturesObstacles[i]);
                    jeu->texturesObstacles[i] = NULL;
                }
            }
            if (jeu->backgroundNiveau1 != NULL)
            {
                SDL_DestroyTexture(jeu->backgroundNiveau1);
                jeu->backgroundNiveau1 = NULL;
            }
            if (jeu->backgroundNiveau2 != NULL)
            {
                SDL_DestroyTexture(jeu->backgroundNiveau2);
                jeu->backgroundNiveau2 = NULL;
            }
            SDL_DestroyRenderer(jeu->rendu);
            jeu->rendu = NULL;
        }
        if (jeu->fenetre != NULL)
        {
            SDL_DestroyWindow(jeu->fenetre);
            jeu->fenetre = NULL;
        }
        if (initialiserJeu(jeu, NIVEAU_2) != 0)
        {
            jeu->continuer = 0;
            return;
        }
        jeu->score = scoreSauve;
        jeu->vies = viesSauvees;
        jeu->modeAffichage = modeSauve;
        jeu->tempsDebut = tempsSauve;
    }
}

void afficherJeu(DonneesJeu *jeu)
{
    SDL_Rect plateformeEcran;
    SDL_Rect obstacleEcran;
    SDL_Rect pieceEcran;
    SDL_Rect ennemiEcran;
    SDL_Rect joueurEcran;
    SDL_Rect joueurEcran2;
    SDL_Rect barreVie;
    SDL_Rect fondVie;
    SDL_Rect sourcePlan;
    SDL_Rect destPlan;
    SDL_Rect sourceEnnemi;
    SDL_Rect obstacleAffichage;
    SDL_Texture *textureObstacleActuelle;
    int i;
    float ratioVie;
    char titre[128];
    SDL_Rect fenetreGuide;
    SDL_Rect fenetreSauvegarde;
    SDL_Texture *backgroundActif;
    SDL_Color couleurTexte;
    SDL_Surface *surfaceTexte;
    SDL_Texture *textureTexte;
    SDL_Rect positionTexte;
    int ligneY;
    const char *guideLignes[6];
    char texteTemps[64];
    char texteVies[64];
    SDL_Rect fondTemps;
    SDL_Rect fondVies;
    Uint32 secondesEcoulees;
    FILE *fichierScores;
    char ligneScore[128];
    char nomLu[64];
    int scoreLu;
    char topNoms[5][32];
    int topScores[5];
    int j;
    int k;

    if (jeu->niveau == NIVEAU_1)
    {
        backgroundActif = jeu->backgroundNiveau1;
    }
    else
    {
        backgroundActif = jeu->backgroundNiveau2;
    }

    SDL_SetRenderDrawColor(jeu->rendu, 10, 10, 10, 255);
    SDL_RenderClear(jeu->rendu);

    if (jeu->modeAffichage == MODE_MONO)
    {
        sourcePlan.x = jeu->camera1.x;
        sourcePlan.y = jeu->camera1.y;
        sourcePlan.w = jeu->camera1.w;
        sourcePlan.h = jeu->camera1.h;
        destPlan.x = 0;
        destPlan.y = 0;
        destPlan.w = LARGEUR_FENETRE;
        destPlan.h = HAUTEUR_FENETRE;
        SDL_RenderCopy(jeu->rendu, backgroundActif, &sourcePlan, &destPlan);
    }
    else
    {
        sourcePlan = jeu->camera1;
        SDL_RenderCopy(jeu->rendu, backgroundActif, &sourcePlan, &jeu->ecran1);
        sourcePlan = jeu->camera2;
        SDL_RenderCopy(jeu->rendu, backgroundActif, &sourcePlan, &jeu->ecran2);
        SDL_SetRenderDrawColor(jeu->rendu, 38, 38, 48, 255);
        SDL_RenderDrawLine(jeu->rendu, LARGEUR_FENETRE / 2, 0, LARGEUR_FENETRE / 2, HAUTEUR_FENETRE);
    }

    for (i = 0; i < jeu->nbPlateformes; i = i + 1)
    {
        if (jeu->plateformes[i].active == 1)
        {
            if (jeu->plateformes[i].type == 0)
            {
                SDL_SetRenderDrawColor(jeu->rendu, 255, 180, 0, 255);
            }
            if (jeu->plateformes[i].type == 1)
            {
                SDL_SetRenderDrawColor(jeu->rendu, 0, 220, 90, 255);
            }
            if (jeu->plateformes[i].type == 2)
            {
                SDL_SetRenderDrawColor(jeu->rendu, 220, 60, 60, 255);
            }
            if (jeu->modeAffichage == MODE_MONO)
            {
                plateformeEcran = jeu->plateformes[i].zone;
                plateformeEcran.x = plateformeEcran.x - jeu->camera1.x;
                plateformeEcran.y = plateformeEcran.y - jeu->camera1.y;
                SDL_RenderFillRect(jeu->rendu, &plateformeEcran);
            }
            else
            {
                plateformeEcran = jeu->plateformes[i].zone;
                plateformeEcran.x = plateformeEcran.x - jeu->camera1.x;
                plateformeEcran.y = plateformeEcran.y - jeu->camera1.y;
                SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran1);
                SDL_RenderFillRect(jeu->rendu, &plateformeEcran);
                plateformeEcran = jeu->plateformes[i].zone;
                plateformeEcran.x = plateformeEcran.x - jeu->camera2.x + jeu->ecran2.x;
                plateformeEcran.y = plateformeEcran.y - jeu->camera2.y;
                SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran2);
                SDL_RenderFillRect(jeu->rendu, &plateformeEcran);
                SDL_RenderSetClipRect(jeu->rendu, NULL);
            }
        }
    }

    for (i = 0; i < jeu->nbObstacles; i = i + 1)
    {
        textureObstacleActuelle = NULL;
        if (jeu->obstacles[i].typeImage >= 0 && jeu->obstacles[i].typeImage < NB_TEXTURES_OBSTACLES)
        {
            textureObstacleActuelle = jeu->texturesObstacles[jeu->obstacles[i].typeImage];
        }
        if (jeu->modeAffichage == MODE_MONO)
        {
            obstacleEcran = jeu->obstacles[i].zone;
            obstacleEcran.x = obstacleEcran.x - jeu->camera1.x;
            obstacleEcran.y = obstacleEcran.y - jeu->camera1.y;
            obstacleAffichage = obstacleEcran;
            agrandirRectObstacleAffichage(&obstacleAffichage);
            if (textureObstacleActuelle != NULL)
            {
                SDL_RenderCopy(jeu->rendu, textureObstacleActuelle, NULL, &obstacleAffichage);
            }
            else
            {
                SDL_SetRenderDrawColor(jeu->rendu, 240, 40, 30, 255);
                SDL_RenderFillRect(jeu->rendu, &obstacleAffichage);
            }
        }
        else
        {
            obstacleEcran = jeu->obstacles[i].zone;
            obstacleEcran.x = obstacleEcran.x - jeu->camera1.x;
            obstacleEcran.y = obstacleEcran.y - jeu->camera1.y;
            obstacleAffichage = obstacleEcran;
            agrandirRectObstacleAffichage(&obstacleAffichage);
            SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran1);
            if (textureObstacleActuelle != NULL)
            {
                SDL_RenderCopy(jeu->rendu, textureObstacleActuelle, NULL, &obstacleAffichage);
            }
            else
            {
                SDL_SetRenderDrawColor(jeu->rendu, 240, 40, 30, 255);
                SDL_RenderFillRect(jeu->rendu, &obstacleAffichage);
            }
            obstacleEcran = jeu->obstacles[i].zone;
            obstacleEcran.x = obstacleEcran.x - jeu->camera2.x + jeu->ecran2.x;
            obstacleEcran.y = obstacleEcran.y - jeu->camera2.y;
            obstacleAffichage = obstacleEcran;
            agrandirRectObstacleAffichage(&obstacleAffichage);
            SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran2);
            if (textureObstacleActuelle != NULL)
            {
                SDL_RenderCopy(jeu->rendu, textureObstacleActuelle, NULL, &obstacleAffichage);
            }
            else
            {
                SDL_SetRenderDrawColor(jeu->rendu, 240, 40, 30, 255);
                SDL_RenderFillRect(jeu->rendu, &obstacleAffichage);
            }
            SDL_RenderSetClipRect(jeu->rendu, NULL);
        }
    }

    SDL_SetRenderDrawColor(jeu->rendu, 255, 215, 40, 255);
    for (i = 0; i < jeu->nbPieces; i = i + 1)
    {
        if (jeu->pieces[i].actif == 1)
        {
            if (jeu->modeAffichage == MODE_MONO)
            {
                pieceEcran = jeu->pieces[i].zone;
                pieceEcran.x = pieceEcran.x - jeu->camera1.x;
                pieceEcran.y = pieceEcran.y - jeu->camera1.y;
                SDL_RenderFillRect(jeu->rendu, &pieceEcran);
            }
            else
            {
                pieceEcran = jeu->pieces[i].zone;
                pieceEcran.x = pieceEcran.x - jeu->camera1.x;
                pieceEcran.y = pieceEcran.y - jeu->camera1.y;
                SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran1);
                SDL_RenderFillRect(jeu->rendu, &pieceEcran);
                pieceEcran = jeu->pieces[i].zone;
                pieceEcran.x = pieceEcran.x - jeu->camera2.x + jeu->ecran2.x;
                pieceEcran.y = pieceEcran.y - jeu->camera2.y;
                SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran2);
                SDL_RenderFillRect(jeu->rendu, &pieceEcran);
                SDL_RenderSetClipRect(jeu->rendu, NULL);
            }
        }
    }

    if (jeu->ennemi.actif == 1)
    {
        int rangeeEnnemi;
        int frameMaxEtat;

        frameMaxEtat = FRAMES_PAR_ETAT_ENNEMI[jeu->etatEnnemi];
        if (frameMaxEtat <= 0)
        {
            frameMaxEtat = 1;
        }
        if (jeu->frameEnnemi >= frameMaxEtat)
        {
            jeu->frameEnnemi = frameMaxEtat - 1;
        }
        if (jeu->nbLignesEnnemi >= 8)
        {
            if (jeu->ennemi.direction >= 0)
            {
                rangeeEnnemi = jeu->etatEnnemi;
            }
            else
            {
                rangeeEnnemi = jeu->etatEnnemi + 4;
            }
        }
        else
        {
            rangeeEnnemi = 0;
        }
        sourceEnnemi.x = jeu->frameEnnemi * jeu->frameLargeurEnnemi;
        sourceEnnemi.y = rangeeEnnemi * jeu->frameHauteurEnnemi;
        sourceEnnemi.w = jeu->frameLargeurEnnemi;
        sourceEnnemi.h = jeu->frameHauteurEnnemi;
        if (jeu->modeAffichage == MODE_MONO)
        {
            ennemiEcran = jeu->ennemi.zone;
            ennemiEcran.x = ennemiEcran.x - jeu->camera1.x;
            ennemiEcran.y = ennemiEcran.y - jeu->camera1.y;
            if (jeu->textureEnnemi != NULL)
            {
                SDL_RenderCopy(jeu->rendu, jeu->textureEnnemi, &sourceEnnemi, &ennemiEcran);
            }
            else
            {
                SDL_SetRenderDrawColor(jeu->rendu, 180, 40, 220, 255);
                SDL_RenderFillRect(jeu->rendu, &ennemiEcran);
            }
            fondVie = (SDL_Rect){ennemiEcran.x, ennemiEcran.y - 10, ennemiEcran.w, 6};
            barreVie = fondVie;
            barreVie.x = barreVie.x + 1;
            barreVie.y = barreVie.y + 1;
            barreVie.w = barreVie.w - 2;
            barreVie.h = barreVie.h - 2;
            SDL_SetRenderDrawColor(jeu->rendu, 20, 20, 24, 255);
            SDL_RenderFillRect(jeu->rendu, &fondVie);
            SDL_SetRenderDrawColor(jeu->rendu, 230, 60, 60, 255);
            SDL_RenderFillRect(jeu->rendu, &barreVie);
        }
        else
        {
            ennemiEcran = jeu->ennemi.zone;
            ennemiEcran.x = ennemiEcran.x - jeu->camera1.x;
            ennemiEcran.y = ennemiEcran.y - jeu->camera1.y;
            SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran1);
            if (jeu->textureEnnemi != NULL)
            {
                SDL_RenderCopy(jeu->rendu, jeu->textureEnnemi, &sourceEnnemi, &ennemiEcran);
            }
            else
            {
                SDL_SetRenderDrawColor(jeu->rendu, 180, 40, 220, 255);
                SDL_RenderFillRect(jeu->rendu, &ennemiEcran);
            }
            fondVie = (SDL_Rect){ennemiEcran.x, ennemiEcran.y - 10, ennemiEcran.w, 6};
            barreVie = fondVie;
            barreVie.x = barreVie.x + 1;
            barreVie.y = barreVie.y + 1;
            barreVie.w = barreVie.w - 2;
            barreVie.h = barreVie.h - 2;
            SDL_SetRenderDrawColor(jeu->rendu, 20, 20, 24, 255);
            SDL_RenderFillRect(jeu->rendu, &fondVie);
            SDL_SetRenderDrawColor(jeu->rendu, 230, 60, 60, 255);
            SDL_RenderFillRect(jeu->rendu, &barreVie);

            ennemiEcran = jeu->ennemi.zone;
            ennemiEcran.x = ennemiEcran.x - jeu->camera2.x + jeu->ecran2.x;
            ennemiEcran.y = ennemiEcran.y - jeu->camera2.y;
            SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran2);
            if (jeu->textureEnnemi != NULL)
            {
                SDL_RenderCopy(jeu->rendu, jeu->textureEnnemi, &sourceEnnemi, &ennemiEcran);
            }
            else
            {
                SDL_SetRenderDrawColor(jeu->rendu, 180, 40, 220, 255);
                SDL_RenderFillRect(jeu->rendu, &ennemiEcran);
            }
            fondVie = (SDL_Rect){ennemiEcran.x, ennemiEcran.y - 10, ennemiEcran.w, 6};
            barreVie = fondVie;
            barreVie.x = barreVie.x + 1;
            barreVie.y = barreVie.y + 1;
            barreVie.w = barreVie.w - 2;
            barreVie.h = barreVie.h - 2;
            SDL_SetRenderDrawColor(jeu->rendu, 20, 20, 24, 255);
            SDL_RenderFillRect(jeu->rendu, &fondVie);
            SDL_SetRenderDrawColor(jeu->rendu, 230, 60, 60, 255);
            SDL_RenderFillRect(jeu->rendu, &barreVie);
            SDL_RenderSetClipRect(jeu->rendu, NULL);
        }
    }

    ratioVie = (float)jeu->vies / 3.0f;
    if (ratioVie < 0.0f)
    {
        ratioVie = 0.0f;
    }
    if (ratioVie > 1.0f)
    {
        ratioVie = 1.0f;
    }
    SDL_SetRenderDrawColor(jeu->rendu, 80, 170, 255, 255);
    joueurEcran = jeu->joueur1;
    joueurEcran.x = joueurEcran.x - jeu->camera1.x;
    joueurEcran.y = joueurEcran.y - jeu->camera1.y;
    if (jeu->modeAffichage == MODE_MULTI)
    {
        SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran1);
    }
    SDL_RenderFillRect(jeu->rendu, &joueurEcran);
    fondVie = (SDL_Rect){joueurEcran.x, joueurEcran.y - 10, joueurEcran.w, 6};
    barreVie = fondVie;
    barreVie.x = barreVie.x + 1;
    barreVie.y = barreVie.y + 1;
    barreVie.w = (int)((barreVie.w - 2) * ratioVie);
    barreVie.h = barreVie.h - 2;
    SDL_SetRenderDrawColor(jeu->rendu, 20, 20, 24, 255);
    SDL_RenderFillRect(jeu->rendu, &fondVie);
    SDL_SetRenderDrawColor(jeu->rendu, 80, 220, 100, 255);
    SDL_RenderFillRect(jeu->rendu, &barreVie);
    if (jeu->modeAffichage == MODE_MULTI)
    {
        SDL_RenderSetClipRect(jeu->rendu, NULL);
    }

    if (jeu->modeAffichage == MODE_MULTI)
    {
        SDL_SetRenderDrawColor(jeu->rendu, 255, 90, 140, 255);
        joueurEcran2 = jeu->joueur2;
        joueurEcran2.x = joueurEcran2.x - jeu->camera2.x + jeu->ecran2.x;
        joueurEcran2.y = joueurEcran2.y - jeu->camera2.y;
        SDL_RenderSetClipRect(jeu->rendu, &jeu->ecran2);
        SDL_RenderFillRect(jeu->rendu, &joueurEcran2);
        fondVie = (SDL_Rect){joueurEcran2.x, joueurEcran2.y - 10, joueurEcran2.w, 6};
        barreVie = fondVie;
        barreVie.x = barreVie.x + 1;
        barreVie.y = barreVie.y + 1;
        barreVie.w = (int)((barreVie.w - 2) * ratioVie);
        barreVie.h = barreVie.h - 2;
        SDL_SetRenderDrawColor(jeu->rendu, 20, 20, 24, 255);
        SDL_RenderFillRect(jeu->rendu, &fondVie);
        SDL_SetRenderDrawColor(jeu->rendu, 80, 220, 100, 255);
        SDL_RenderFillRect(jeu->rendu, &barreVie);
        SDL_RenderSetClipRect(jeu->rendu, NULL);
    }

    if (jeu->police != NULL)
    {
        snprintf(texteVies, 64, "Vies: %d", jeu->vies);
        couleurTexte.r = 245;
        couleurTexte.g = 246;
        couleurTexte.b = 248;
        couleurTexte.a = 255;
        surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, texteVies, couleurTexte);
        if (surfaceTexte != NULL)
        {
            textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
            if (textureTexte != NULL)
            {
                fondVies.w = surfaceTexte->w + 24;
                fondVies.h = surfaceTexte->h + 10;
                fondVies.x = 8;
                fondVies.y = 8;
                SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(jeu->rendu, 12, 14, 20, 210);
                SDL_RenderFillRect(jeu->rendu, &fondVies);
                SDL_SetRenderDrawColor(jeu->rendu, 226, 230, 236, 235);
                SDL_RenderDrawRect(jeu->rendu, &fondVies);
                SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_NONE);
                positionTexte.x = fondVies.x + 12;
                positionTexte.y = fondVies.y + 5;
                positionTexte.w = surfaceTexte->w;
                positionTexte.h = surfaceTexte->h;
                SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                SDL_DestroyTexture(textureTexte);
            }
            SDL_FreeSurface(surfaceTexte);
        }

        secondesEcoulees = (SDL_GetTicks() - jeu->tempsDebut) / 1000;
        snprintf(texteTemps, 64, "Temps: %u s", (unsigned int)secondesEcoulees);
        couleurTexte.r = 245;
        couleurTexte.g = 246;
        couleurTexte.b = 248;
        couleurTexte.a = 255;
        surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, texteTemps, couleurTexte);
        if (surfaceTexte != NULL)
        {
            textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
            if (textureTexte != NULL)
            {
                fondTemps.w = surfaceTexte->w + 24;
                fondTemps.h = surfaceTexte->h + 10;
                fondTemps.x = (LARGEUR_FENETRE - fondTemps.w) / 2;
                fondTemps.y = 8;
                SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(jeu->rendu, 12, 14, 20, 210);
                SDL_RenderFillRect(jeu->rendu, &fondTemps);
                SDL_SetRenderDrawColor(jeu->rendu, 226, 230, 236, 235);
                SDL_RenderDrawRect(jeu->rendu, &fondTemps);
                SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_NONE);
                positionTexte.x = fondTemps.x + 12;
                positionTexte.y = fondTemps.y + 5;
                positionTexte.w = surfaceTexte->w;
                positionTexte.h = surfaceTexte->h;
                SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                SDL_DestroyTexture(textureTexte);
            }
            SDL_FreeSurface(surfaceTexte);
        }
    }

    if (jeu->afficherGuide == 1)
    {
        fenetreGuide.x = 14;
        fenetreGuide.y = 44;
        fenetreGuide.w = 280;
        fenetreGuide.h = 145;
        SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(jeu->rendu, 10, 12, 18, 210);
        SDL_RenderFillRect(jeu->rendu, &fenetreGuide);
        SDL_SetRenderDrawColor(jeu->rendu, 210, 216, 224, 230);
        SDL_RenderDrawRect(jeu->rendu, &fenetreGuide);
        SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_NONE);
        if (jeu->police != NULL)
        {
            guideLignes[0] = "GUIDE";
            guideLignes[1] = "TAB: mono/multi";
            guideLignes[2] = "J1: <- ->  saut: UP";
            guideLignes[3] = "J2: Q D   saut: Z";
            guideLignes[4] = "G: afficher/masquer guide";
            guideLignes[5] = "1/2: changer de niveau";
            couleurTexte.r = 235;
            couleurTexte.g = 238;
            couleurTexte.b = 243;
            couleurTexte.a = 255;
            ligneY = fenetreGuide.y + 8;
            for (i = 0; i < 6; i = i + 1)
            {
                surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, guideLignes[i], couleurTexte);
                if (surfaceTexte != NULL)
                {
                    textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                    if (textureTexte != NULL)
                    {
                        positionTexte.x = fenetreGuide.x + 10;
                        positionTexte.y = ligneY;
                        positionTexte.w = surfaceTexte->w;
                        positionTexte.h = surfaceTexte->h;
                        SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                        SDL_DestroyTexture(textureTexte);
                    }
                    SDL_FreeSurface(surfaceTexte);
                }
                ligneY = ligneY + 22;
            }
        }
    }

    if (jeu->modeSauvegarde == 1)
    {
        fenetreSauvegarde.x = 180;
        fenetreSauvegarde.y = 120;
        fenetreSauvegarde.w = 640;
        fenetreSauvegarde.h = 340;
        SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(jeu->rendu, 0, 0, 0, 170);
        SDL_RenderFillRect(jeu->rendu, &fenetreSauvegarde);
        SDL_SetRenderDrawColor(jeu->rendu, 228, 232, 238, 240);
        SDL_RenderDrawRect(jeu->rendu, &fenetreSauvegarde);
        SDL_SetRenderDrawBlendMode(jeu->rendu, SDL_BLENDMODE_NONE);
        if (jeu->police != NULL)
        {
            couleurTexte.r = 240;
            couleurTexte.g = 240;
            couleurTexte.b = 240;
            couleurTexte.a = 255;
            surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, "FIN DU JEU - SAUVEGARDE", couleurTexte);
            if (surfaceTexte != NULL)
            {
                textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                if (textureTexte != NULL)
                {
                    positionTexte.x = fenetreSauvegarde.x + 18;
                    positionTexte.y = fenetreSauvegarde.y + 18;
                    positionTexte.w = surfaceTexte->w;
                    positionTexte.h = surfaceTexte->h;
                    SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                    SDL_DestroyTexture(textureTexte);
                }
                SDL_FreeSurface(surfaceTexte);
            }

            snprintf(ligneScore, 128, "Nom joueur: %s_", jeu->nomJoueur);
            surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, ligneScore, couleurTexte);
            if (surfaceTexte != NULL)
            {
                textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                if (textureTexte != NULL)
                {
                    positionTexte.x = fenetreSauvegarde.x + 20;
                    positionTexte.y = fenetreSauvegarde.y + 58;
                    positionTexte.w = surfaceTexte->w;
                    positionTexte.h = surfaceTexte->h;
                    SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                    SDL_DestroyTexture(textureTexte);
                }
                SDL_FreeSurface(surfaceTexte);
            }

            snprintf(ligneScore, 128, "Score a sauvegarder: %d", jeu->score);
            surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, ligneScore, couleurTexte);
            if (surfaceTexte != NULL)
            {
                textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                if (textureTexte != NULL)
                {
                    positionTexte.x = fenetreSauvegarde.x + 20;
                    positionTexte.y = fenetreSauvegarde.y + 82;
                    positionTexte.w = surfaceTexte->w;
                    positionTexte.h = surfaceTexte->h;
                    SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                    SDL_DestroyTexture(textureTexte);
                }
                SDL_FreeSurface(surfaceTexte);
            }

            surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, "Enter: valider | Backspace: effacer", couleurTexte);
            if (surfaceTexte != NULL)
            {
                textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                if (textureTexte != NULL)
                {
                    positionTexte.x = fenetreSauvegarde.x + 20;
                    positionTexte.y = fenetreSauvegarde.y + 106;
                    positionTexte.w = surfaceTexte->w;
                    positionTexte.h = surfaceTexte->h;
                    SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                    SDL_DestroyTexture(textureTexte);
                }
                SDL_FreeSurface(surfaceTexte);
            }

            for (j = 0; j < 5; j = j + 1)
            {
                topNoms[j][0] = '\0';
                topScores[j] = -1;
            }
            fichierScores = fopen("scores.txt", "r");
            if (fichierScores != NULL)
            {
                while (fgets(ligneScore, 128, fichierScores) != NULL)
                {
                    if (sscanf(ligneScore, "%31s %d", nomLu, &scoreLu) == 2)
                    {
                        for (j = 0; j < 5; j = j + 1)
                        {
                            if (scoreLu > topScores[j])
                            {
                                for (k = 4; k > j; k = k - 1)
                                {
                                    topScores[k] = topScores[k - 1];
                                    strcpy(topNoms[k], topNoms[k - 1]);
                                }
                                topScores[j] = scoreLu;
                                strcpy(topNoms[j], nomLu);
                                break;
                            }
                        }
                    }
                }
                fclose(fichierScores);
            }

            surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, "Meilleurs scores:", couleurTexte);
            if (surfaceTexte != NULL)
            {
                textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                if (textureTexte != NULL)
                {
                    positionTexte.x = fenetreSauvegarde.x + 20;
                    positionTexte.y = fenetreSauvegarde.y + 146;
                    positionTexte.w = surfaceTexte->w;
                    positionTexte.h = surfaceTexte->h;
                    SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                    SDL_DestroyTexture(textureTexte);
                }
                SDL_FreeSurface(surfaceTexte);
            }

            for (j = 0; j < 5; j = j + 1)
            {
                if (topScores[j] >= 0)
                {
                    snprintf(ligneScore, 128, "%d) %s - %d", j + 1, topNoms[j], topScores[j]);
                }
                else
                {
                    snprintf(ligneScore, 128, "%d) ---", j + 1);
                }
                surfaceTexte = TTF_RenderUTF8_Blended(jeu->police, ligneScore, couleurTexte);
                if (surfaceTexte != NULL)
                {
                    textureTexte = SDL_CreateTextureFromSurface(jeu->rendu, surfaceTexte);
                    if (textureTexte != NULL)
                    {
                        positionTexte.x = fenetreSauvegarde.x + 34;
                        positionTexte.y = fenetreSauvegarde.y + 170 + j * 24;
                        positionTexte.w = surfaceTexte->w;
                        positionTexte.h = surfaceTexte->h;
                        SDL_RenderCopy(jeu->rendu, textureTexte, NULL, &positionTexte);
                        SDL_DestroyTexture(textureTexte);
                    }
                    SDL_FreeSurface(surfaceTexte);
                }
            }
        }
    }

    if (jeu->modeSauvegarde == 1)
    {
        snprintf(titre, 128, "Sauvegarde - Nom:%s_  Enter: valider  Backspace: effacer  Score:%d", jeu->nomJoueur, jeu->score);
    }
    else
    {
        snprintf(titre, 128, "Niveau:%d  Score:%d  Vies:%d  Temps:%u  Mode:%s  G:guide  1/2:niveau", jeu->niveau, jeu->score, jeu->vies, (unsigned int)((SDL_GetTicks() - jeu->tempsDebut) / 1000), jeu->modeAffichage == MODE_MONO ? "mono" : "multi");
    }
    SDL_SetWindowTitle(jeu->fenetre, titre);
    SDL_RenderPresent(jeu->rendu);
}

void sauvegarderScore(DonneesJeu *jeu)
{
    FILE *fichier;

    if (jeu->scoreEnregistre == 1)
    {
        return;
    }
    if (jeu->longueurNom <= 0)
    {
        return;
    }
    fichier = fopen("scores.txt", "a");
    if (fichier == NULL)
    {
        return;
    }
    fprintf(fichier, "%s %d\n", jeu->nomJoueur, jeu->score);
    fclose(fichier);
    jeu->scoreEnregistre = 1;
}

void nettoyerJeu(DonneesJeu *jeu)
{
    int i;

    if (jeu->police != NULL)
    {
        TTF_CloseFont(jeu->police);
    }
    if (jeu->backgroundNiveau1 != NULL)
    {
        SDL_DestroyTexture(jeu->backgroundNiveau1);
    }
    if (jeu->backgroundNiveau2 != NULL)
    {
        SDL_DestroyTexture(jeu->backgroundNiveau2);
    }
    for (i = 0; i < NB_TEXTURES_OBSTACLES; i = i + 1)
    {
        if (jeu->texturesObstacles[i] != NULL)
        {
            SDL_DestroyTexture(jeu->texturesObstacles[i]);
        }
    }
    if (jeu->textureEnnemi != NULL)
    {
        SDL_DestroyTexture(jeu->textureEnnemi);
    }
    if (jeu->rendu != NULL)
    {
        SDL_DestroyRenderer(jeu->rendu);
    }
    if (jeu->fenetre != NULL)
    {
        SDL_DestroyWindow(jeu->fenetre);
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
