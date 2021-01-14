#include <iostream>
#include <vector>
using namespace std;
const int POINTS = 4;
struct point {
	double lat, lot;
	int id;
} points[POINTS] = {
	{50.448363,30.397821,0},
	{50.432223,30.420635,1},
	{50.512842,30.767189,2},
	{50.486877,30.805299,3}
};
int distances[POINTS][POINTS] = {
	{13,8194,40852,47590},
	{8916,9,37720,44458},
	{37879,37300,1,8763},
	{40121,39542,7635,209}
};
typedef vector<vector<point>> clusters;
ostream& operator<<(ostream& os, clusters cs) {
	os << '~' << endl;
	for (int i = 0; i < cs.size(); i++)
		for (point p : cs[i])
			os << p.lat << ' ' << p.lot << ' ' << i << endl;
	os << '~' << endl;
	return os;
}
typedef vector<point> cluster;
int distance(cluster a, cluster b) {
	int d;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b.size(); j++)
			if (!i && !j)
				d = distances[a[i].id][b[j].id];
			else {
				if (distances[a[i].id][b[j].id] < d)
					d = distances[a[i].id][b[j].id];
			}
	for (int i = 0; i < b.size(); i++)
		for (int j = 0; j < a.size(); j++)
			if (distances[b[i].id][a[j].id] < d)
				d = distances[b[i].id][a[j].id];
	return d;
}
void connectNearest(clusters& clusters) {
	if (clusters.size() == 1) return;
	int a, b, d;
	for (int i = 0; i < clusters.size(); i++) {
		for (int j = 0; j < clusters.size(); j++)
			if (i != j) {
				if (!i && j == 1) {
					a = 0;
					b = 1;
					d = distance(clusters[i], clusters[j]);
				}
				else {
					if (distance(clusters[i], clusters[j]) < d) {
						a = i;
						b = j;
						d = distance(clusters[i], clusters[j]);
					}
				}
			}
	}
	while (clusters[b].size()) {
		clusters[a].push_back(clusters[b][clusters[b].size()-1]);
		clusters[b].pop_back();
	}
	clusters.erase(clusters.begin() + b);
}
int main() {
	clusters clusters;
	for (int i = 0; i < POINTS; i++)
		clusters.push_back({points[i]});
	cout << clusters;
	while (clusters.size() > 1) {
		connectNearest(clusters);
		cout << clusters;
	}
}