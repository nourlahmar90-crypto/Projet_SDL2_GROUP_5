#include "header.h"

int main(void)
{
    DonneesJeu jeu;
    SDL_Event evenement;
    const Uint8 *clavier;
    int i;
    int niveauDemande;
    int scoreSauve;
    int viesSauvees;
    int modeSauve;
    int guideSauve;
    Uint32 tempsSauve;

    if (initialiserJeu(&jeu, NIVEAU_1) != 0)
    {
        return 1;
    }
    niveauDemande = 0;
    SDL_StartTextInput();

    while (jeu.continuer == 1)
    {
        while (SDL_PollEvent(&evenement))
        {
            if (evenement.type == SDL_QUIT)
            {
                jeu.continuer = 0;
            }
            if (evenement.type == SDL_KEYDOWN)
            {
                if (evenement.key.keysym.sym == SDLK_ESCAPE)
                {
                    jeu.continuer = 0;
                }
                if (evenement.key.keysym.sym == SDLK_TAB)
                {
                    if (jeu.modeAffichage == MODE_MONO)
                    {
                        jeu.modeAffichage = MODE_MULTI;
                    }
                    else
                    {
                        jeu.modeAffichage = MODE_MONO;
                    }
                }
                if (evenement.key.keysym.sym == SDLK_g)
                {
                    if (jeu.afficherGuide == 1)
                    {
                        jeu.afficherGuide = 0;
                    }
                    else
                    {
                        jeu.afficherGuide = 1;
                    }
                }
                if (evenement.key.keysym.sym == SDLK_1)
                {
                    niveauDemande = NIVEAU_1;
                }
                if (evenement.key.keysym.sym == SDLK_2)
                {
                    niveauDemande = NIVEAU_2;
                }
                if (evenement.key.keysym.sym == SDLK_UP && jeu.auSol1 == 1)
                {
                    jeu.vitesseY1 = -16;
                    jeu.auSol1 = 0;
                }
                if (evenement.key.keysym.sym == SDLK_z && jeu.auSol2 == 1)
                {
                    jeu.vitesseY2 = -16;
                    jeu.auSol2 = 0;
                }
                if (jeu.modeSauvegarde == 1 && evenement.key.keysym.sym == SDLK_BACKSPACE && jeu.longueurNom > 0)
                {
                    jeu.longueurNom = jeu.longueurNom - 1;
                    jeu.nomJoueur[jeu.longueurNom] = '\0';
                }
                if (jeu.modeSauvegarde == 1 && evenement.key.keysym.sym == SDLK_RETURN)
                {
                    sauvegarderScore(&jeu);
                    jeu.continuer = 0;
                }
            }
            if (jeu.modeSauvegarde == 1 && evenement.type == SDL_TEXTINPUT)
            {
                i = 0;
                while (evenement.text.text[i] != '\0' && jeu.longueurNom < 30)
                {
                    jeu.nomJoueur[jeu.longueurNom] = evenement.text.text[i];
                    jeu.longueurNom = jeu.longueurNom + 1;
                    jeu.nomJoueur[jeu.longueurNom] = '\0';
                    i = i + 1;
                }
            }
        }

        if (niveauDemande != 0 && niveauDemande != jeu.niveau)
        {
            scoreSauve = jeu.score;
            viesSauvees = jeu.vies;
            modeSauve = jeu.modeAffichage;
            guideSauve = jeu.afficherGuide;
            tempsSauve = jeu.tempsDebut;
            nettoyerJeu(&jeu);
            if (initialiserJeu(&jeu, niveauDemande) != 0)
            {
                return 1;
            }
            jeu.score = scoreSauve;
            jeu.vies = viesSauvees;
            jeu.modeAffichage = modeSauve;
            jeu.afficherGuide = guideSauve;
            jeu.tempsDebut = tempsSauve;
            niveauDemande = 0;
        }

        clavier = SDL_GetKeyboardState(NULL);
        mettreAJourJeu(&jeu, clavier);
        afficherJeu(&jeu);
        SDL_Delay(16);
    }

    sauvegarderScore(&jeu);
    SDL_StopTextInput();
    nettoyerJeu(&jeu);
    return 0;
}
