#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ressource {
protected:
    int id;
    string titre;
    string auteur;
    int annee;

public:
    Ressource(int i, string t, string a, int y)
        : id(i), titre(t), auteur(a), annee(y) {
    }

    virtual void afficherInfos() const {
        cout << "ID: " << id << ", Titre: " << titre
            << ", Auteur: " << auteur << ", Annee: " << annee << endl;
    }

    virtual void telecharger() const {
        cout << "Téléchargement de la ressource generique : " << titre << endl;
    }

    bool operator==(const Ressource& r) const {
        return id == r.id;
    }

    int getAnnee() const { return annee; }
    string getTitre() const { return titre; }
    string getAuteur() const { return auteur; }

    virtual ~Ressource() {}
};
class Telechargeable {
public:
    virtual void afficherMessage() const = 0;
};



class Livre : public Ressource, public Telechargeable {
public:
    Livre(int i, string t, string a, int y)
        : Ressource(i, t, a, y) {
    }

    void afficherInfos() const override {
        cout << "[Livre] ";
        Ressource::afficherInfos();
    }

    void telecharger() const override {
        cout << "Téléchargement du livre : " << titre << endl;
    }

    void afficherMessage() const override {
        cout << "Message: Livre disponible en format PDF." << endl;
    }
};

class Magazine : public Ressource, public Telechargeable {
public:
    Magazine(int i, string t, string a, int y)
        : Ressource(i, t, a, y) {
    }

    void afficherInfos() const override {
        cout << "[Magazine] ";
        Ressource::afficherInfos();
    }

    void telecharger() const override {
        cout << "Téléchargement du magazine : " << titre << endl;
    }

    void afficherMessage() const override {
        cout << "Message: Magazine disponible en format numérique." << endl;
    }
};

class Video : public Ressource, public Telechargeable {
public:
    Video(int i, string t, string a, int y)
        : Ressource(i, t, a, y) {
    }

    void afficherInfos() const override {
        cout << "[Video] ";
        Ressource::afficherInfos();
    }

    void telecharger() const override {
        cout << "Téléchargement de la vidéo : " << titre << endl;
    }

    void afficherMessage() const override {
        cout << "Message: Vidéo disponible en HD." << endl;
    }
};


class Mediatheque {
private:
    vector<Ressource*> ressources;

public:
    void ajouter(Ressource* r) {
        ressources.push_back(r);
    }

    void afficher() const {
        cout << "\n=== Liste des ressources ===" << endl;
        for (auto r : ressources) {
            r->afficherInfos();
        }
    }

    // Recherche surchargée
    void rechercher(string titre) const {
        cout << "\nRecherche par titre : " << titre << endl;
        for (auto r : ressources)
            if (r->getTitre() == titre)
                r->afficherInfos();
    }

    void rechercher(int annee) const {
        cout << "\nRecherche par annee : " << annee << endl;
        for (auto r : ressources)
            if (r->getAnnee() == annee)
                r->afficherInfos();
    }

    ~Mediatheque() {
        for (auto r : ressources) delete r;
    }
};


int main() {
    Mediatheque m;

    m.ajouter(new Livre(1, "Le Petit Prince", "Saint-Exupéry", 1943));
    m.ajouter(new Magazine(2, "Science et Vie", "Michel", 2022));
    m.ajouter(new Video(3, "Tutoriel C++", "OpenClassrooms", 2021));

    m.afficher();

    m.rechercher("Science et Vie");
    m.rechercher(2021);

    return 0;
}