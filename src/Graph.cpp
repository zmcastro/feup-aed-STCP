//
// Created by zemar on 27/01/2022.
//

#define INF (std::numeric_limits<double>::max()/2)

#include "../headers/Graph.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) { }

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, const std::string lineCode) {
    if (src<0 || src>n || dest<0 || dest>n) return;

    double weight = haversine(nodes[src].stop.getLatitude(), nodes[src].stop.getLongitude(), nodes[dest].stop.getLatitude(), nodes[dest].stop.getLongitude());

    nodes[src].adj.push_back({dest, weight, lineCode});
}

void Graph::addNode(const Stop &stop, const int &idx) {
    Node newNode = Node();
    newNode.stop = stop;
    nodes.at(idx) = newNode;
}

Stop Graph::getStop(const int &idx) {
    if (idx < n || idx >= 0)
        return nodes.at(idx).stop;
    else
        throw "Stop not found!";
}

int Graph::findNearest(const int &src) {
    double minDist = INF;
    int nearestIdx = src;
    for (auto e : nodes[src].adj) {
        if (e.weight < minDist) {
            minDist = e.weight;
            nearestIdx = e.dest;
        }
    }
    return nearestIdx;
}
int Graph::findNearest(const int &src, const std::string &line) {
    double minDist = INF;
    int nearestIdx = src;
    for (auto e : nodes[src].adj) {
        if (e.weight < minDist && e.line == line) {
            minDist = e.weight;
            nearestIdx = e.dest;
        }
    }
    return nearestIdx;
}

std::vector<Stop> Graph::findNearestStops(const int &src, const double &maxDist) {
    std::vector<Stop> res;
    for (auto & node : nodes) {
        double dist = haversine(nodes[src].stop.getLatitude(), nodes[src].stop.getLongitude(), node.stop.getLatitude(), node.stop.getLongitude());
        if ((dist < maxDist) && (node.stop.getCode() != nodes[src].stop.getCode())) {
            res.push_back(node.stop);
        }
    }
    return res;
}
std::vector<Stop> Graph::findNearestStops2(const double latitude, const double longitude, const double &maxDist) {
    std::vector<Stop> res;
    for (auto & node : nodes) {
        double dist = haversine(latitude, longitude, node.stop.getLatitude(), node.stop.getLongitude());
        if ((dist < maxDist) ) {
            res.push_back(node.stop);
        }
    }
    return res;
}

std::vector<Stop> Graph::findNearestLineStops(const int &src, const double &maxDist) {
    std::vector<int> aux;
    std::vector<Stop> res;
    for (auto e : nodes[src].adj) {
        if ((e.weight < maxDist) && (std::find(aux.begin(), aux.end(), e.dest) == aux.end())) {
            aux.push_back(e.dest);
            res.push_back(getStop(e.dest));
        }
        if (res.size() == 5)
            break;
    }
    return res;
}

void Graph::dijkstraByDist(const int &index, const bool &time) // 0 if day, 1 if night
{
    std::set<std::pair<double, int>> q;
    for (int v = 0; v < n; v++) {
        nodes[v].pred = -1;
        nodes[v].dist = INF;
        q.insert({INF, v});
        nodes[v].visited = false;
    }

    nodes[index].dist = 0;
    q.erase({INF, index});
    q.insert({0, index});
    nodes[index].pred = index;
    while (q.size() > 0) {
        int u = q.begin()->second;
        q.erase(q.begin());
        nodes[u].visited = true;
        for (auto e: nodes[u].adj ) {
            if (time == 0 && e.line.back() == 'M')
                continue;
            int v = e.dest;
            double w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                q.erase({nodes[v].dist, v});
                nodes[v].stop.setLine(e.line);
                nodes[v].dist = nodes[u].dist + w;
                nodes[v].pred = u;
                q.insert({nodes[v].dist, v});
            }
        }
    }
}

void Graph::dijkstraByCost(const int &index, const bool &time) // 0 if day, 1 if night
{
    std::set<std::pair<double, int>> q;
    for (int v = 0; v < n; v++) {
        nodes[v].pred = -1;
        nodes[v].dist = INF;
        q.insert({INF, v});
        nodes[v].visited = false;
    }

    nodes[index].dist = 0;
    q.erase({INF, index});
    q.insert({0, index});
    nodes[index].pred = index;
    while (q.size() > 0) {
        int u = q.begin()->second;
        q.erase(q.begin());
        nodes[u].visited = true;
        for (auto e: nodes[u].adj ) {
            if (time == 0 && e.line.back() == 'M')
                continue;
            int v = e.dest;
            double w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                q.erase({nodes[v].dist, v});
                nodes[v].stop.setLine(e.line);
                nodes[v].dist = nodes[u].dist + w + 10*(nodes[v].stop.getZone() != nodes[u].stop.getZone());
                nodes[v].pred = u;
                q.insert({nodes[v].dist, v});
            }
        }
    }
}

void Graph::bfs(const int &index, const bool &time) {
    // initialize all nodes as unvisited
    for (int i=1; i<=n; i++)
        nodes[i].visited = false;
    std::queue<int> q; // queue of unvisited nodes
    q.push(index);
    nodes[index].dist = 0;
    nodes[index].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        for (auto e : nodes[u].adj) {
            if (time == 0 && e.line.back() == 'M')
                continue;
            int w = e.dest;
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].stop.setLine(e.line);
                nodes[w].pred = u;
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
}

std::list<Stop> Graph::bfs_path(const int &idx1, const int &idx2, const int &time)
{
    std::list<Stop> path;

    bfs(idx1, (time == 1));

    path.push_back(nodes.at(idx2).stop);
    int v = idx2;
    while (v != idx1) {
        v = nodes[v].pred;
        path.push_front(nodes.at(v).stop);
    }

    return path;
}

std::list<Stop> Graph::dijkstra_path(const int &idx1, const int &idx2, const int &time, const int &dijkstraType) {
    switch(dijkstraType) {
        case 2:
            dijkstraByDist(idx1, (time == 1));
            break;
        case 3:
            //dijkstraByLine;
            break;
        case 4:
            dijkstraByCost(idx1, (time == 1));
            break;
        default:
            std::cout << "How did you get past input checking?" << std::endl;
            exit(1);
    }
    std::list<Stop> path;

    if (nodes[idx2].dist == INF) return path;
    path.push_back(nodes.at(idx2).stop);
    int v = idx2;
    while (v != idx1) {
        v = nodes[v].pred;
        path.push_front(nodes.at(v).stop);
    }
    return path;
}

double Graph::dijkstra_distance(const int &idx1, const int &idx2, const int &dijkstraType) {
    switch(dijkstraType) {
        case 2:
            dijkstraByDist(idx1, 0);
            break;
        case 3:
            //dijkstraByLine;
            break;
        case 4:
            dijkstraByCost(idx1, 0);
            break;
        default:
            std::cout << "How did you get past input checking?" << std::endl;
            exit(1);
    }

    dijkstraByDist(idx1, 0);
    if (nodes[idx2].dist == INF) return -1;
    return nodes[idx2].dist;
}


