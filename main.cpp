#include <fstream>
#include <iostream>
#include <vector>
#include<string>
#include <algorithm>
#include <regex>
#include "Node.h"

using namespace std;

void usage();

bool is_1(string &str);

bool is_2(string &str);

bool is_3(string &str);

bool is_4(string &str);

bool is_5(string &str);

bool is_6(string &str);

int getType(string str, int ordre);

int getType(string str);

bool verificationFichierEntre(const string &str);

bool verificationOrdre(const vector<string> &tab);

bool verificationCaractere(const vector<string> &tab);

void afficheVector(const vector<Connection>& myList);

void generateDatFile(vector<Connection> ensConnection, vector<Traffic> ensTraffic, string name);

int main(int argc, char *argv[]) {
    if (argc != 2) { // verification que l'argument du main est la
        usage();
        return 1;
    }

    ifstream in_file;
    vector<string> tabFichier;

    if (verificationFichierEntre(argv[1])) { // verification de l'extention du fichier ouvert
        in_file.open(argv[1]);
    } else {
        cout << "EXIT_FAILURE : wrong file type";
        return EXIT_FAILURE;
    }

    if (in_file.is_open()) { // lecture du fichier
        cout << "File open." << endl;

        while (!in_file.eof()) {
            string line;
            getline(in_file, line);
            tabFichier.push_back(line);
        }
        cout << "file read completely." << endl;
    }

    if (verificationCaractere(tabFichier) && verificationOrdre(tabFichier)) {
        cout << "ok" << endl; // TODO mettre le reste des autres
    } else {
        cout << "EXIT_FAILURE : bad file write";
        return EXIT_FAILURE;
    }

    in_file.close();

    //analyse
    vector<Node> node_vect = {};
    vector<Traffic> traffic_vector = {};
    vector<Connection> connection_vector = {};
    for (string str: tabFichier) {
        int type = getType(str);
        Node node;
        Traffic traffic;
        Connection connection;
        switch (type) {
            case 2:
                //cout << "case 0" << endl;
                node = string_to_node(str);
                node_vect.push_back(node);
                break;
            case 4:
                traffic = Traffic(string_to_traffic(str));
                traffic_vector.push_back(traffic);
                break;
            case 6:
                connection = string_to_connection(str);
                connection_vector.push_back(connection);
                break;
            default:
                cout << "default" << endl;
        }
    }
    afficheVector(connection_vector);

    generateDatFile(connection_vector, traffic_vector, "test1");

    return 0;
}

void afficheVector(const vector<Connection>& myList) {
    for (Connection co: myList) {
        cout << "Node1 x : " << co.get_node_1().get_x() << " Node1 y : " << co.get_node_1().get_y() << endl;
        cout << "Node2 x : " << co.get_node_2().get_x() << " Node2 y : " << co.get_node_2().get_y() << endl << endl;
    }
}

bool verificationFichierEntre( // verification que l'extention du fichier est la bonne
        const string &str) {
    if (str[str.length() - 4] == '.' && str[str.length() - 3] == 'c' && str[str.length() - 2] == 's' &&
        str[str.length() - 1] == 'v') {
        return true;
    } else {
        return false;
    }
}

bool verificationCaractere(
        const vector<string> &tab) { // verification que les caractère du fichier son bien ceux auquelle on se restraint
    vector<char> caractere = {'"', 'N', 'o', 'd', 'e', ',', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 't', 'r',
                              'a', 'f', 'i', 'c', 'n', 'e', 't', '\n', ' ', ','};
    short nombre = 0, total = 0;
    for (const string &c: tab) {
        for (char caraTab: c) {
            total++;
            if (count(caractere.begin(), caractere.end(), caraTab)) {
                nombre++;
            }
        }
    }
    if (nombre == total) {
        return true;
    } else {
        return false;
    }
}

bool verificationOrdre(const vector<string> &tab) { // verification que le fichier est bien écrit
    short ordre = 0;
    for (basic_string<char> i: tab) {
        if (is_1(i) && ordre == 0) {
            ordre = 2;
        } else if (is_3(i) && ordre == 2) {
            ordre = 4;
        } else if (is_5(i) && ordre == 4) {
            ordre = 6;
        } else if (i.empty()) {

        } else if (getType(i, ordre) != ordre) {
            return false;
        }
    }
    return true;
}

int getType(string str) // Permet de déterminer le type de données
{
    //cout << str << endl;
    if (is_1(str)) {
        return 1;
    } else if (is_2(str)) {
        return 2;
    } else if (is_3(str)) {
        return 3;
    } else if (is_6(str)) {
        return 6;
    } else if (is_5(str)) {
        return 5;
    } else if (is_4(str)) {
        return 4;
    }
    return 0;
}

int getType(string str, int ordre) { // Permet de déterminer le type de données
    if (is_1(str)) {
        return 1;
    } else if (is_2(str)) {
        return 2;
    } else if (is_3(str)) {
        return 3;
    } else if (is_4(str) && ordre < 5) {
        return 4;
    } else if (is_5(str)) {
        return 5;
    } else if (is_6(str) && ordre > 5) {
        return 6;
    } else {
        return 7;
    }
}

bool is_1(string &str) // Utilisation de regex pour les 6 cas
{
    static const regex r(R"("Node",,)");
    return regex_match(str, r);
}

bool is_2(string &str) {
    static const regex r(R"("Node[0-9]{1,3}",[0-9]{1,3},[0-9]{1,3})");
    return regex_match(str, r);
}

bool is_3(string &str) {
    static const regex r(R"("traffic",,)");
    return regex_match(str, r);
}

bool is_4(string &str) {
    static const regex r(R"(("Node[0-9]{1,3}",)*"Node[0-9]{1,3}")");
    return regex_match(str, r);
}

bool is_5(string &str) {
    static const regex r(R"("connection",,)");
    return regex_match(str, r);
}

bool is_6(string &str) {
    static const regex r(R"("Node[0-9]{1,3}","Node[0-9]{1,3}")");
    return regex_match(str, r);
}

void usage() {
    cout << "mettre le chemin du csv en argument";
}


/**
 * @brief Genere un fichier .dat .
 * @param ensConnection l'ensemble des connexions entre 2 noeuds.
 * @param ensTraffic l'ensemble des chemins (traffic).
 * @param name le nom du fichier dat.
 */
void generateDatFile(vector<Connection> ensConnection, vector<Traffic> ensTraffic, string name) {

    // On creer le fichier dat :
    name = name + ".dat";
    fstream datFile{name, std::ios::out};

    // On parcourt l'ensemble des connexions et on ecrit leurs infos dans le fichier .dat :
    for (int i = 0; i < ensConnection.size(); i++) {

        // On recupere les coordonnees du premier Node :
        int coordX1 = ensConnection.at(i).get_node_1().get_x();
        int coordY1 = ensConnection.at(i).get_node_1().get_y();

        // On recupere les coordonnees du deuxieme Node :
        int coordX2 = ensConnection.at(i).get_node_2().get_x();
        int coordY2 = ensConnection.at(i).get_node_2().get_y();

        // On definit les string à ecrire dans le fichier :
        string coordNode1 = to_string(coordX1) + "  " + to_string(coordY1);
        string coordNode2 = to_string(coordX2) + "  " + to_string(coordY2);

        // On les ecrit dans le fichier .dat et on saute une lignne:
        datFile << coordNode1 << endl;
        datFile << coordNode2 << endl;
        datFile << "" << endl;
    }
}

