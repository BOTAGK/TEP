#pragma once
#include <vector>
#include <string>
using namespace std;

namespace LcVRPContest {
	constexpr unsigned int RANDOM_PERMUTATION_SEED = 42;

	struct Coordinate {
		double x;
		double y;

		Coordinate();
		Coordinate(double x, double y);
	};
	class ProblemData {
	public:
		static constexpr double INVALID_DATA = -1.0;
		ProblemData();

		string getInstanceName() const { return instanceName_; }
		int getTotalNodes() const { return nodeCount_; }
		int getCapacity() const { return maxCapacity_; }
		double getMaxDistance() const { return maxDistance_; }
		bool isDistanceLimited() const { return hasLimitDistance_; }

		int getNumCustomers() const { return nodeCount_ - 1; }
		int getDepot() const { return depot_; }
		int getNumGroups() const { return numGroups_; }

		const vector<Coordinate>& getCoordinate() const { return coordinates_; }
		const vector<int>& getDemands() const { return demands_; }
		const vector<int>& getTargetPermutation() const { return permutation_; }

		double calculateTravelCost(int a, int b) const;
		double calculateCoordinatesDistance(int i, int j) const;
		void computeDistanceMatrix();

		void setInstanceName(const string& name) { instanceName_ = name; }

		void setNodeCount(int count);
		void setCapacity(int cap) { maxCapacity_ = cap; }
		void setDistanceLimit(double dist);
		void setWeightType(const string& type) { weightType_ = type; }
		void setDepotId(int depot) { depot_ = depot; }
		void setNumGroups(int groups) { numGroups_ = groups; }

		void setLocations(const vector<Coordinate>& coords) { coordinates_ = coords; }
		void setDemands(const vector<int>& demands) { demands_ = demands; }
		void setPermutation(const vector<int>& permutation) { permutation_ = permutation; }
		void setDistanceMatrix(const vector<vector<double>>& matrix) { distanceMatrix_ = matrix; }


	private:
		string instanceName_;
		string weightType_;

		int nodeCount_;
		int depot_;
		int maxCapacity_;
		int numGroups_;
		double maxDistance_;
		bool hasLimitDistance_;

		vector<Coordinate> coordinates_;
		vector<int> demands_;
		vector<int> permutation_;

		vector<vector<double>> distanceMatrix_;
		bool isMatrixReady_;
	};
}