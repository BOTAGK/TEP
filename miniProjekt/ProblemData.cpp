#include "ProblemData.hpp"

using namespace LcVRPContest;
using namespace std;

Coordinate::Coordinate() : x(0.0), y(0.0) {}
Coordinate::Coordinate(double xP, double yP) : x(xP), y(yP) {}

ProblemData::ProblemData()
	: nodeCount_(0),
	  maxCapacity_(0),
	  depot_(1),
	  hasLimitDistance_(false),
	  maxDistance_(0.0),
	  numGroups_(0),
	  isMatrixReady_(false)
{
	weightType_ = "EUC_2D";
}

double ProblemData::calculateTravelCost(int i, int j) const {
	if (i < 0 || i >= nodeCount_ || j < 0 || j >= nodeCount_) {
		return INVALID_DATA;
	}

	return distanceMatrix_[i][j];
}

void ProblemData::computeDistanceMatrix() {
	if (weightType_ != "EUC_2D") return;

	distanceMatrix_ = vector<vector<double>>(nodeCount_, vector<double>(nodeCount_, 0.0));

	for (int i = 0; i < nodeCount_; i++) {
		for (int j = i; j < nodeCount_; j++) {
			if (i == j) {
				distanceMatrix_[i][j] = 0.0;
			}
			else {
				double distance = calculateCoordinatesDistance(i, j);
				distanceMatrix_[i][j] = distance;
				distanceMatrix_[j][i] = distance;
			}
		}
	}
	
}

double ProblemData::calculateCoordinatesDistance(int i, int j) const {
	double dx = coordinates_[i].x - coordinates_[j].x;
	double dy = coordinates_[i].y - coordinates_[j].y;

	return hypot(dx, dy);
}

void ProblemData::setNodeCount(int count) {
	nodeCount_ = count;
	coordinates_.resize(count);
	demands_.resize(count);
}

void ProblemData::setDistanceLimit(double dist) {
	maxDistance_ = dist;
	hasLimitDistance_ = true;
}