#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int caseTaille = 100; // Taille de chaque case (pixels)
const int grilleLargeur = 9; // Nombre de colonnes
const int grilleHauteur = 9; // Nombre de lignes
const int windowWidth = caseTaille * grilleLargeur + 500; // Largeur de la fenêtre (ajout d'une colonne à droite)
const int windowHeight = caseTaille * grilleHauteur; // Hauteur de la fenêtre
const int nbMurs = 20; // Nombre de murs à placer aléatoirement
const float chronoLimite = 11.0f; // Limite de temps en secondes

// Fonction pour générer des murs aléatoires
void genererMurs(std::vector<std::vector<bool>>& murs, int playerX, int playerY, int& objectifX, int& objectifY) {
    srand(static_cast<unsigned>(time(0))); // Initialisation du générateur aléatoire

    for (int i = 0; i < nbMurs; i++) {
        int randX = rand() % grilleLargeur;
        int randY = rand() % grilleHauteur;

        // Éviter de placer un mur sur la position du joueur, sur l'objectif ou de créer un mur déjà existant
        if ((randX != playerX || randY != playerY) && (randX != objectifX || randY != objectifY) && !murs[randY][randX]) {
            murs[randY][randX] = true;
        }
        else {
            i--; // Réessayer si la case est invalide
        }
    }
}

// Fonction pour générer l'objectif
void genererObjectif(int playerX, int playerY, int& objectifX, int& objectifY) {
    do {
        objectifX = rand() % grilleLargeur;
        objectifY = rand() % grilleHauteur;
    } while (objectifX == playerX && objectifY == playerY); // Éviter que l'objectif soit sur le joueur
}
void genererPorte(int playerX, int playerY, int& porteX, int& porteY) {
    do {
        porteX = rand() % grilleLargeur;
        porteY = rand() % grilleHauteur;
    } while (porteX == playerX && porteY == playerY); // Éviter que l'objectif soit sur le joueur
}

void genererInterrupteur(int playerX, int playerY, int& InterrupteurX, int& InterrupteurY) {
    do {
        InterrupteurX = rand() % grilleLargeur;
        InterrupteurY = rand() % grilleHauteur;
    } while (InterrupteurX == InterrupteurX && InterrupteurY == playerY); // Éviter que l'objectif soit sur le joueur
}


int main() {
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Jeu de labyrinthe");

    // Charger les textures
    sf::Texture playerTexture, wallTexture, cheeseTexture, porteTexture, InterrupteurTexture;
    if (!playerTexture.loadFromFile("C:/Users/User/Desktop/ConsoleApplication2/asset/player.png") || !wallTexture.loadFromFile("C:/Users/User/Desktop/ConsoleApplication2/asset/wall.png") || !cheeseTexture.loadFromFile("C:/Users/User/Desktop/ConsoleApplication2/asset/cheese.png") || !porteTexture.loadFromFile("C:/Users/User/Desktop/ConsoleApplication2/asset/porte.png") || !cheeseTexture.loadFromFile("C:/Users/User/Desktop/ConsoleApplication2/asset/cheese.png") || !InterrupteurTexture.loadFromFile("C:/Users/User/Desktop/ConsoleApplication2/asset/interrupteur.png")) {
        return -1; // Si les textures ne sont pas chargées, fermer le programme
    }

    // Création du joueur (rectangle vert)
    sf::Sprite player;  // Crée un sprite pour le joueur
    player.setTexture(playerTexture);

    // Ajuster le sprite à la taille d'une case
    sf::FloatRect playerBounds = player.getLocalBounds();
    float scaleX = static_cast<float>(caseTaille) / playerBounds.width;
    float scaleY = static_cast<float>(caseTaille) / playerBounds.height;
    player.setScale(scaleX, scaleY);  // Redimensionner le sprite pour qu'il corresponde à la taille d'une case

    // Position initiale du joueur
    int playerX = grilleLargeur / 2;
    int playerY = grilleHauteur / 2;
    player.setPosition(playerX * caseTaille, playerY * caseTaille);

    sf::Sprite cheese;  // Crée un sprite pour le joueur
    cheese.setTexture(cheeseTexture);

    // Position de l'objectif
    int objectifX, objectifY;
    genererObjectif(playerX, playerY, objectifX, objectifY);
    cheese.setPosition(objectifX * caseTaille, objectifY * caseTaille);

    // Ajuster le sprite à la taille d'une case
    sf::FloatRect cheeseBounds = cheese.getLocalBounds();
    float scale2X = static_cast<float>(caseTaille) / cheeseBounds.width;
    float scale2Y = static_cast<float>(caseTaille) / cheeseBounds.height;
    cheese.setScale(scale2X, scale2Y);  // Redimensionner le sprite pour qu'il corresponde à la taille d'une case


    // Création de la matrice des murs
    std::vector<std::vector<bool>> murs(grilleHauteur, std::vector<bool>(grilleLargeur, false));
    genererMurs(murs, playerX, playerY, objectifX, objectifY);
    sf::Sprite mur;  // Crée un sprite pour le joueur
    mur.setTexture(wallTexture);

    // Ajuster le sprite à la taille d'une case
    sf::FloatRect murBounds = mur.getLocalBounds();
    float scale3X = static_cast<float>(caseTaille) / murBounds.width;
    float scale3Y = static_cast<float>(caseTaille) / murBounds.height;
    mur.setScale(scale3X, scale3Y);  // Redimensionner le sprite pour qu'il corresponde à la taille d'une case

    // Création de la porte
    sf::Sprite porte;  // Crée un sprite pour le joueur
    porte.setTexture(porteTexture);

    // Position de la porte
    int porteX, porteY;
    genererPorte(playerX, playerY, porteX, porteY);
    porte.setPosition(porteX * caseTaille, porteY * caseTaille);

    // Ajuster le sprite à la taille d'une case
    sf::FloatRect porteBounds = porte.getLocalBounds();
    float scale4X = static_cast<float>(caseTaille) / porteBounds.width;
    float scale4Y = static_cast<float>(caseTaille) / porteBounds.height;
    porte.setScale(scale4X, scale4Y);  // Redimensionner le sprite pour qu'il corresponde à la taille d'une case

    sf::Sprite interrupteur;  // Crée un sprite pour le joueur
    interrupteur.setTexture(InterrupteurTexture);

    // Position de l'objectif
    int interrupteurX, interrupteurY;
    genererInterrupteur(playerX, playerY, interrupteurX, interrupteurY);
    interrupteur.setPosition(interrupteurX * caseTaille, interrupteurY * caseTaille);

    // Ajuster le sprite à la taille d'une case
    sf::FloatRect interrupteurBounds = interrupteur.getLocalBounds();
    float scale5X = static_cast<float>(caseTaille) / interrupteurBounds.width;
    float scale5Y = static_cast<float>(caseTaille) / interrupteurBounds.height;
    interrupteur.setScale(scale5X, scale5Y);  // Redimensionner le sprite pour qu'il corresponde à la taille d'une case

    // Police et texte pour afficher le chrono et les messages
    sf::Font font;
    font.loadFromFile("C:/Users/User/Desktop/ConsoleApplication1/asset/arial_bold.ttf"); // Assurez-vous que cette police existe dans le même dossier que l'exécutable
    sf::Text chronoText;
    chronoText.setFont(font);
    chronoText.setCharacterSize(30);
    chronoText.setFillColor(sf::Color::White);
    chronoText.setPosition(windowWidth - 480, 150); // Position de l'affichage du chrono

    sf::Text TitreText;
    TitreText.setFont(font);
    TitreText.setCharacterSize(40);
    TitreText.setFillColor(sf::Color::White);
    TitreText.setPosition(grilleLargeur * caseTaille + 10, 10);
    TitreText.setString(
        "-- THE MAZE GAME --\n"
        "\n"
        "\n"
        "\n"
    );

    sf::Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(grilleLargeur * caseTaille + 10, 70);
    instructionsText.setString(
        "- but : atteindre le carre jaune,\n"
        "- en evitant les murs rouges,\n"
        "- en moins de 10 secondes."
    );

    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(50);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition(270, windowHeight / 2 - 50);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // Taille du texte
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth - 480, 190); // Affichage à droite de la grille
    scoreText.setString("Score: 0"); // Texte initial


    sf::Text Ascii;
    Ascii.setFont(font);
    Ascii.setCharacterSize(64); // Taille du texte
    Ascii.setFillColor(sf::Color::White);
    Ascii.setPosition(windowWidth - 480, 390); // Affichage à droite de la grille
    Ascii.setString("(\(\")\n(  -.-)\no_(')(')");
                        // Texte initial


    // Chronomètre
    int score = 0;
    sf::Clock clock;
    float chrono = chronoLimite;

    /*
    // Charger un son
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("C:/Users/User/Desktop/ConsoleApplication1/asset/win.wav")) { // Charger le fichier audio (ajoutez le bon chemin)
        return -1; // Si le fichier audio ne peut pas être chargé
    }
    /* supprimer cette ligne si vs voulez tester l'audio
        sf::Sound sound;
        sound.setBuffer(buffer);
    /*
        symbole externe non résolu "public: __cdecl sf::Sound::Sound(void)" (??0Sound@sf@@QEAA@XZ) référencé dans la fonction main
        symbole externe non résolu "public: virtual __cdecl sf::Sound::~Sound(void)" (??1Sound@sf@@UEAA@XZ) référencé dans la fonction main
        symbole externe non résolu "public: virtual void __cdecl sf::Sound::play(void)" (?play@Sound@sf@@UEAAXXZ) référencé dans la fonction main
        symbole externe non résolu "public: void __cdecl sf::Sound::setBuffer(class sf::SoundBuffer const &)" (?setBuffer@Sound@sf@@QEAAXAEBVSoundBuffer@2@@Z) référencé dans la fonction main
        symbole externe non résolu "public: __cdecl sf::SoundBuffer::SoundBuffer(void)" (??0SoundBuffer@sf@@QEAA@XZ) référencé dans la fonction main
        symbole externe non résolu "public: __cdecl sf::SoundBuffer::~SoundBuffer(void)" (??1SoundBuffer@sf@@QEAA@XZ) référencé dans la fonction main
        symbole externe non résolu "public: bool __cdecl sf::SoundBuffer::loadFromFile(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const &)" (?loadFromFile@SoundBuffer@sf@@QEAA_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z) référencé dans la fonction main
        7 externes non résolus
    */


    // Ajouter une déclaration globale pour le score (avant la boucle principale)
// Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Gérer les déplacements du joueur
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && playerY > 0 && !murs[playerY - 1][playerX]) {
                    playerY--;
                }
                if (event.key.code == sf::Keyboard::Down && playerY < grilleHauteur - 1 && !murs[playerY + 1][playerX]) {
                    playerY++;

                }
                if (event.key.code == sf::Keyboard::Left && playerX > 0 && !murs[playerY][playerX - 1]) {
                    playerX--;
                }
                if (event.key.code == sf::Keyboard::Right && playerX < grilleLargeur - 1 && !murs[playerY][playerX + 1]) {
                    playerX++;

                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

                // Mettre à jour la position graphique du joueur
                player.setPosition(playerX * caseTaille, playerY * caseTaille);
            }
        }

        // Mettre à jour le chronomètre
        float deltaTime = clock.restart().asSeconds();
        chrono -= deltaTime;

        // Vérifier si le joueur atteint l'objectif
        if (playerX == objectifX && playerY == objectifY) {
            // Réinitialiser le jeu
            playerX = grilleLargeur / 2;
            playerY = grilleHauteur / 2;
            player.setPosition(playerX * caseTaille, playerY * caseTaille);

            genererObjectif(playerX, playerY, objectifX, objectifY);
            cheese.setPosition(objectifX * caseTaille, objectifY * caseTaille);

            murs = std::vector<std::vector<bool>>(grilleHauteur, std::vector<bool>(grilleLargeur, false));
            genererMurs(murs, playerX, playerY, objectifX, objectifY);

            chrono = chronoLimite; // Réinitialiser le chrono

            score++; // Augmenter le score
        }

        // Vérifier si le chronomètre atteint zéro
        if (chrono <= 0) {
            // Afficher "Perdu" et réinitialiser le jeu
            messageText.setString("Perdu,\nAppuyer sur 'R' pour recommencer\nou echap pour quitter\nNombre de fromages ramasser : " + std::to_string(score));
            window.clear(sf::Color::Black);
            window.draw(messageText);
            window.display();
            sf::sleep(sf::seconds(2)); // Attendre 2 secondes

            // Réinitialiser le jeu
            playerX = grilleLargeur / 2;
            playerY = grilleHauteur / 2;
            player.setPosition(playerX * caseTaille, playerY * caseTaille);

            genererObjectif(playerX, playerY, objectifX, objectifY);
            cheese.setPosition(objectifX * caseTaille, objectifY * caseTaille);

            murs = std::vector<std::vector<bool>>(grilleHauteur, std::vector<bool>(grilleLargeur, false));
            genererMurs(murs, playerX, playerY, objectifX, objectifY);

            chrono = chronoLimite; // Réinitialiser le chrono
            score = 0; // Réinitialiser le score
        }

        // Mettre à jour le texte du chrono
        chronoText.setString("Temps restant: " + std::to_string(static_cast<int>(chrono)) + "s");

        // Mettre à jour le texte du score
        scoreText.setString("Score: " + std::to_string(score));

        // Effacer la fenêtre
        window.clear(sf::Color::Black);

        // Dessiner la grille
        for (int x = 0; x <= grilleLargeur; x++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x * caseTaille, 0), sf::Color::White),
                sf::Vertex(sf::Vector2f(x * caseTaille, windowHeight), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }
        for (int y = 0; y <= grilleHauteur; y++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0, y * caseTaille), sf::Color::White),
                sf::Vertex(sf::Vector2f(windowWidth - 500, y * caseTaille), sf::Color::White) // Limiter à la colonne d'affichage
            };
            window.draw(line, 2, sf::Lines);
        }


        // Dessiner les murs
        for (int y = 0; y < grilleHauteur; y++) {
            for (int x = 0; x < grilleLargeur; x++) {
                if (murs[y][x]) {
                    mur.setPosition(x * caseTaille, y * caseTaille);
                    window.draw(mur);
                }
            }
        }

        // Dessiner l'objectif
        window.draw(cheese);

        // Dessiner le joueur
        window.draw(player);

        // Dessiner le texte (chrono, score, instructions, etc.)
        window.draw(TitreText);
        window.draw(instructionsText);
        window.draw(chronoText);
        window.draw(scoreText); // Correctement référencé ici
        window.draw(Ascii); // Correctement référencé ici

        // Afficher le tout
        window.display();
    }

    return 0;
}
bool afficherMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text titreText, jouerText, quitterText;
    titreText.setFont(font);
    titreText.setString("Menu");
    titreText.setCharacterSize(50);
    titreText.setFillColor(sf::Color::White);
    titreText.setPosition(windowWidth / 2 - 150, 100);

    jouerText.setFont(font);
    jouerText.setString("1. Jouer = espace");
    jouerText.setCharacterSize(40);
    jouerText.setFillColor(sf::Color::White);
    jouerText.setPosition(windowWidth / 2 - 100, 250);

    quitterText.setFont(font);
    quitterText.setString("2. Quitter = echap");
    quitterText.setCharacterSize(40);
    quitterText.setFillColor(sf::Color::White);
    quitterText.setPosition(windowWidth / 2 - 100, 350);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    return true; // Lancer le jeu
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    window.close();
                    return false; // Quitter le jeu
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(titreText);
        window.draw(jouerText);
        window.draw(quitterText);
        window.display();
    }
    return false;
}
