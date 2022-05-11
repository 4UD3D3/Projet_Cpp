//
// Created by Martin on 10/05/2022.
//
#include<string>
#include<vector>

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

using namespace std;


class Node {
private:
    string name;
    int x;
    int y;
public:
    Node() {
        this->name = "";
        this->x = 0;
        this->y = 0;
    }

    Node(string _name) {
        this->name = _name;
        this->x = 0;
        this->y = 0;
    }

    Node(string _name, int _x, int _y) {
        this->name = _name;
        this->x = _x;
        this->y = _y;
    }

    string get_name() {
        return this->name;
    }

    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

};

class Traffic {
private:
    vector<Node> traffic;
public:
    Traffic() {
    }

    Traffic(vector<Node> _traffic) {
        this->traffic = _traffic;
    }

    vector<Node> get_traffic() {
        return this->traffic;
    }

    Node get_node(int index) {
        return this->traffic.at(index);
    }

    int get_size() {
        return this->traffic.size();
    }
};

class Connection {
private:
    Node node_1, node_2;
public:
    Connection(Node _node_1, Node _node_2) {
        this->node_1 = _node_1;
        this->node_2 = _node_2;
    }

    Connection() {}

    Node get_node_1() {
        return this->node_1;
    }

    Node get_node_2() {
        return this->node_2;
    }
};

Node string_to_node(string &str) {
    cout << "test1" << endl;
    string delimiter = ",";
    size_t pos = 0;
    string token;
    vector<string> split;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        split.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    split.push_back(str);
    Node node = Node(split.at(0), stoi(split.at(1)), stoi(split.at(2)));
    return node;
}

Traffic string_to_traffic(string &str) {
    vector<Node> traffic_nodes;
    string var_str = str;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    while ((pos = var_str.find(delimiter)) != std::string::npos) {
        token = var_str.substr(0, pos);
        Node *node = new Node(token);
        traffic_nodes.push_back(*node);
        var_str.erase(0, pos + delimiter.length());
    }
    Node *node = new Node(token);
    traffic_nodes.push_back(*node);
    Traffic traffic = Traffic(traffic_nodes);
    return traffic;
}

Connection string_to_connection(string &str) {
    string var_str = str;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    Node *node_1;
    Node *node_2;
    while ((pos = var_str.find(delimiter)) != std::string::npos) {
        token = var_str.substr(0, pos);
        std::cout << token << std::endl;
        node_1 = new Node(token);
        var_str.erase(0, pos + delimiter.length());
    }
    node_2 = new Node(token);
    Connection connection = Connection(*node_1, *node_2);
    return connection;
}


#endif //PROJECT_NODE_H
