#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Client {
private:
    string nom;
    string CIN;
    int idClient;

public:
    Client(string n, string c, int id)
        : nom(n), CIN(c), idClient(id) {
    }

    string getNom() const { return nom; }
    int getId() const { return idClient; }
};

class CompteBancaire {
private:
    string numeroCompte;
    double solde;
    string codeSecret;
    int refClient;

public:
    CompteBancaire(string num, double s, string code, int ref)
        : numeroCompte(num), solde(s), codeSecret(code), refClient(ref) {
    }

    void depot(double montant) { solde += montant; }

    bool retrait(double montant) {
        if (montant <= solde) {
            solde -= montant;
            return true;
        }
        return false;
    }

    void afficher() const {
        cout << "Compte: " << numeroCompte << " | Solde: " << solde << endl;
    }

    friend class AgentBancaire;  
    friend class Banque;
};

class AgentBancaire {
private:
    string nomAgent;

public:
    AgentBancaire(string nom) : nomAgent(nom) {}

    void transferer(CompteBancaire& src, CompteBancaire& dest, double montant) {
        if (src.retrait(montant)) {
            dest.depot(montant);
            cout << "Transfert de " << montant << " effectué par " << nomAgent << endl;
        }
        else {
            cout << "Solde insuffisant pour le transfert !" << endl;
        }
    }
};

// =========================
// Classe Banque
// =========================
class Banque {
private:
    vector<Client> clients;
    vector<CompteBancaire> comptes;

public:
    void ajouterClient(Client c) { clients.push_back(c); }

    void ajouterCompte(CompteBancaire c) { comptes.push_back(c); }

    void afficherAudit() const {
        cout << "\n=== Rapport d'Audit Bancaire ===" << endl;
        for (auto& c : comptes) c.afficher();
    }
};


int main() {
    Banque b;
    Client c1("Moubssir", "AA12345", 1);
    Client c2("Chorok", "BB67890", 2);

    b.ajouterClient(c1);
    b.ajouterClient(c2);

    CompteBancaire comp1("C001", 5000, "1234", 1);
    CompteBancaire comp2("C002", 2000, "5678", 2);

    b.ajouterCompte(comp1);
    b.ajouterCompte(comp2);

    AgentBancaire agent("Youssef");
    agent.transferer(comp1, comp2, 1500);

    b.afficherAudit();

    return 0;
}