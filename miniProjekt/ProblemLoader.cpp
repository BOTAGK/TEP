#include "ProblemLoader.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>

using namespace LcVRPContest;
using namespace std;

ProblemLoader::ProblemLoader(const string& dir, const string& name, bool forceRandPermutation)
	: randomizePermutation_(forceRandPermutation)
{
	string separator = (dir.empty() || dir.back() == '/') ? "" : "/";

	string basePath = "data/lcvrp/" + dir + separator;

	filePath_ = basePath + name;
	if (filePath_.find(".lcvrp") == string::npos) {
		filePath_ += ".lcvrp";
	}
}

ProblemData ProblemLoader::loadData() {
	ProblemData data;
	ifstream file(filePath_);

	readFile(file, data);

	file.close();
	data.computeDistanceMatrix();

	if (randomizePermutation_) {
		generateRandomPermutation(data);
	}

	return data;
}

void ProblemLoader::readFile(ifstream& file, ProblemData& data) {
	if (!file.is_open()) {
		cerr << "[Reader] Critical error: File not found at " << filePath_ << endl;
		return;
	}

	string token;
	bool end = false;

	while (file >> token && !end) {

		if (token == "NAME") {
			skipDelimiters(file);
			string name;
			file >> name;
			data.setInstanceName(name);
		}
		else if (token == "DIMENSION") {
			skipDelimiters(file);
			int dim;
			file >> dim;
			data.setNodeCount(dim);
		}
		else if (token == "CAPACITY") {
			skipDelimiters(file);
			int cap;
			file >> cap;
			data.setCapacity(cap);
		}
		else if (token == "EDGE_WEIGHT_TYPE") {
			skipDelimiters(file);
			string type;
			file >> type;
			data.setWeightType(type);
		}
		else if (token == "NUM_GROUPS") {
			skipDelimiters(file);
			int groups;
			file >> groups;
			data.setNumGroups(groups);
		}
		else if (token == "NODE_COORD_SECTION") {
			parseNodeCoords(file, data);
		}
		else if (token == "DEMAND_SECTION") {
			parseDemands(file, data);
		}
		else if (token == "EDGE_WEIGHT_SECTION") {
			parseEdgeWeights(file, data);
		}
		else if (token == "DEPOT_SECTION") {
			parseDepot(file, data);
		}
		else if (token == "PERMUTATION") {
			parsePermutation(file, data);
		}
		else if (token == "EOF") {
			end = true;
		}
	}
}
void ProblemLoader::skipDelimiters(ifstream& file) {
	char peek = file.peek();

	while (peek == ' ' || peek == '\t' || peek == ':') {
		file.get();
		peek = file.peek();
	}
}

void ProblemLoader::parseNodeCoords(ifstream& file, ProblemData& data) {
	int n = data.getTotalNodes();

	vector<Coordinate> locations(n);

	for (int i = 0; i < n; i++) {
		int id;
		double x, y;
		file >> id >> x >> y;
		locations[id - 1] = Coordinate(x, y);
	}

	data.setLocations(locations);
}

void ProblemLoader::parseDemands(ifstream& file, ProblemData& data) {
	int n = data.getTotalNodes();
	vector<int> demands(n);

	for (int i = 0; i < n; i++) {
		int id, demand;
		file >> id >> demand;

		demands[id - 1] = demand;
	}
	data.setDemands(demands);
}

void ProblemLoader::parseEdgeWeights(ifstream& file, ProblemData& data) {
	int dimension = data.getTotalNodes();

	vector<vector<double>> edgeWeights(dimension, vector<double>(dimension, 0.0));
	for (int i = 1; i < dimension; i++) {
		for (int j = 0; j < i; j++) {
			double weight;

			file >> weight;
			
			edgeWeights[i][j] = weight;
			edgeWeights[j][i] = weight;
		}
	}
	data.setDistanceMatrix(edgeWeights);
}

void ProblemLoader::parseDepot(ifstream& file, ProblemData& data) {
	int id;

	file >> id;
	data.setDepotId(id);

	int trash;
	while (file >> trash && trash != -1);
}

void ProblemLoader::parsePermutation(ifstream& file, ProblemData& data) {
	skipDelimiters(file);

	int numCust = data.getNumCustomers();
	vector<int> permutation;

	permutation.reserve(numCust);

	for (int i = 0; i < numCust; i++) {
		int val;
		file >> val;
		permutation.push_back(val);
	}
	data.setPermutation(permutation);
}

void ProblemLoader::generateRandomPermutation(ProblemData& data) const {
	int num_customers = data.getNumCustomers();
	vector<int> permutation;

	permutation.reserve(num_customers);

	for (int i = 2; i <= num_customers + 1; ++i) {
		permutation.push_back(i);
	}

	mt19937 gen(RANDOM_PERMUTATION_SEED);
	shuffle(permutation.begin(), permutation.end(), gen);

	data.setPermutation(permutation);
}