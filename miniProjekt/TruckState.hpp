#pragma once
#include "ProblemData.hpp"

namespace LcVRPContest {
	class TruckState
	{
	public:
		TruckState(int startNodeIdx);
		double getTotalCost() const { return totalCost_; };
		void visitCustomer(int customerId, int demand, const ProblemData& data);
		void finishRoute(const ProblemData& data);
	private:
		int lastNodeIdx_;
		int currentLoad_;
		double currentDistance_;
		double totalCost_;

		void returnToDepot(const ProblemData& data);
		void moveToNode(double dist, int demand, int newLocation);
	};
}


