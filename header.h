#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 600
#define MODE_MONO 0
#define MODE_MULTI 1
#define NIVEAU_1 1
#define NIVEAU_2 2
#define NB_PLATEFORMES_MAX 8
#define NB_OBSTACLES_MAX 6
#define NB_PIECES_MAX 12
#define POINTS_PAR_PIECE 10
#define NB_TEXTURES_OBSTACLES 3
#define OBSTACLE_ROUE 0
#define OBSTACLE_BOX 1
#define OBSTACLE_BARREL 2

typedef struct
{
    SDL_Rect zone;
    int type;
    int active;
    int direction;
    int borneMinX;
    int borneMaxX;
} Plateforme;

typedef struct
{
    SDL_Rect zone;
    int degats;
    int typeImage;
} ObstacleJeu;

typedef struct
{
    SDL_Rect zone;
    int actif;
} PieceJeu;

typedef struct
{
    SDL_Rect zone;
    int actif;
    int direction;
    int vitesse;
    int borneMinX;
    int borneMaxX;
    int degats;
} EnnemiJeu;

typedef struct
{
    SDL_Window *fenetre;
    SDL_Renderer *rendu;
    TTF_Font *police;
    SDL_Texture *backgroundNiveau1;
    SDL_Texture *backgroundNiveau2;
    SDL_Texture *texturesObstacles[NB_TEXTURES_OBSTACLES];
    SDL_Texture *textureEnnemi;
    int frameEnnemi;
    int nbFramesEnnemi;
    int nbLignesEnnemi;
    int frameLargeurEnnemi;
    int frameHauteurEnnemi;
    int etatEnnemi;
    Uint32 dernierTickEnnemi;
    Uint32 finAttaqueEnnemi;
    Uint32 finIdleEnnemi;
    Plateforme plateformes[NB_PLATEFORMES_MAX];
    int nbPlateformes;
    ObstacleJeu obstacles[NB_OBSTACLES_MAX];
    int nbObstacles;
    PieceJeu pieces[NB_PIECES_MAX];
    int nbPieces;
    EnnemiJeu ennemi;
    SDL_Rect joueur1;
    SDL_Rect joueur2;
    SDL_Rect camera1;
    SDL_Rect camera2;
    SDL_Rect ecran1;
    SDL_Rect ecran2;
    int vitesseY1;
    int vitesseY2;
    int auSol1;
    int auSol2;
    int modeAffichage;
    int niveau;
    int largeurNiveau;
    int hauteurNiveau;
    int score;
    int vies;
    int continuer;
    int afficherGuide;
    int modeSauvegarde;
    int scoreEnregistre;
    char nomJoueur[32];
    int longueurNom;
    Uint32 tempsDebut;
    Uint32 dernierDegat;
} DonneesJeu;

int initialiserJeu(DonneesJeu *jeu, int niveau);
void mettreAJourJeu(DonneesJeu *jeu, const Uint8 *clavier);
void afficherJeu(DonneesJeu *jeu);
void sauvegarderScore(DonneesJeu *jeu);
void nettoyerJeu(DonneesJeu *jeu);

#endif
