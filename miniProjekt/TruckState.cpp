#include "TruckState.hpp"

using namespace LcVRPContest;

TruckState::TruckState(int startNodeIdx)
	: lastNodeIdx_(startNodeIdx),
	currentLoad_(0),
	currentDistance_(0.0),
	totalCost_(0.0){}

void TruckState::visitCustomer(int customerID, int demand, const ProblemData& data){
	int depotIdx = data.getDepot() - 1;
	int customerIdx = customerID - 1;

	if (currentLoad_ + demand > data.getCapacity()) {
		returnToDepot(data);
	}

	double distToCustomer = data.calculateTravelCost(lastNodeIdx_, customerIdx);

	if (data.isDistanceLimited()) {
		double distBack = data.calculateTravelCost(depotIdx, customerIdx);

		if (currentDistance_ + distToCustomer + distBack > data.getMaxDistance()) {
			returnToDepot(data);

			distToCustomer = data.calculateTravelCost(depotIdx, customerIdx);
		}
	}

	moveToNode(distToCustomer, demand, customerIdx);
}

void TruckState::finishRoute(const ProblemData& data)
{
	int depotIdx = data.getDepot() - 1;

	if (lastNodeIdx_ != depotIdx) {
		returnToDepot(data);
	}
}

void TruckState::returnToDepot(const ProblemData& data)
{
	int depotIdx = data.getDepot() - 1;

	double distHome = data.calculateTravelCost(lastNodeIdx_, depotIdx);

	totalCost_ += distHome;
	currentDistance_ = 0.0;
	currentLoad_ = 0;
	lastNodeIdx_ = depotIdx;
}

void TruckState::moveToNode(double dist, int demand, int newLocationIdx)
{
	totalCost_ += dist;
	currentDistance_ += dist;
	currentLoad_ += demand;
	lastNodeIdx_ = newLocationIdx;

}
