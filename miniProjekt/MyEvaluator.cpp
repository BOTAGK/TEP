#include "MyEvaluator.hpp"
#include "TruckState.hpp"
#include <iostream>
#include <vector>


using namespace std;
using namespace LcVRPContest;



MyEvaluator::MyEvaluator(const ProblemData& data)
	: data_(data),
	numGroups_(data.getNumGroups()),
	numCustomers_(data.getNumCustomers()),
	validState_(true)
{
	ValidateProblemData();
}

void MyEvaluator::ValidateProblemData() {
	int capacity = data_.getCapacity();
	const auto& demands = data_.getDemands();
	int depotIdx = data_.getDepot() - 1;
	int dimension = data_.getTotalNodes();

	for (int i = 1; i < dimension; i++) {
		if (demands[i] > capacity) {
			validState_ = false;
			return;
		}

		if (data_.isDistanceLimited()) {
			double maxDist = data_.getMaxDistance();
			double distToCustomer = data_.calculateTravelCost(depotIdx, i);

			if (distToCustomer < 0.0) {
				validState_ = false;
				return;
			}

			if (distToCustomer * 2.0 > maxDist) {
				validState_ = false;
				return;
			}
		}
	}
}

double MyEvaluator::Evaluate(const int* solution) const {
	if (!solution || !validState_) return Wrong_VAL;

	int depotIdx = data_.getDepot() - 1;

	vector<TruckState> trucks(numGroups_, TruckState(depotIdx));

	const auto& permutation = data_.getTargetPermutation();
	const auto& demands = data_.getDemands();

	for (int customerID : permutation) {

		int solutionIdx = customerID - 2;

		int truckID = solution[solutionIdx];

		if (truckID < 0 || truckID >= numGroups_) {
			return Wrong_VAL;
		}

		int demandIdx = customerID - 1;
		int demand = demands[demandIdx];

		trucks[truckID].visitCustomer(customerID, demand, data_);
	}

	double totalCost = 0.0;

	for (auto& truck : trucks) {
		truck.finishRoute(data_);

		totalCost += truck.getTotalCost();
	}

	return totalCost;
}


double MyEvaluator::Evaluate(const vector<int>& solution) const {
	if (solution.size() != static_cast<size_t>(numCustomers_)) {
		return Wrong_VAL;
	}
	return Evaluate(solution.data());
}

double MyEvaluator::Evaluate(const vector<int>* solution) const {
	if (!solution) return Wrong_VAL;

	return Evaluate(*solution);
}




