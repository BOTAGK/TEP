#pragma once
#include <vector>
#include "MyEvaluator.hpp"
#include "Individual.hpp"

using namespace std;

namespace LcVRPContest {
	//nie inicjalizowac tutaj zmiennnych 
	struct GAParams {
		int populationSize;
		double mutationRate;
		double crossoverRate;
	};

	class GeneticAlgorithm {

	public:
		static mt19937 gen_;

		GeneticAlgorithm(const MyEvaluator& evaluator, const GAParams& params);

		void run(int maxIterations);
		const vector<int>& getBestSolution() const;
		double getBestFitness() const;

	private:
		const MyEvaluator& evaluator_;
		GAParams params_;
		
		vector<Individual> population_;
		vector<Individual> nextGeneration_;

		Individual bestSolution_;

		void evaluatePopulation(vector<Individual>& population);
		void crossPopulation();
		void mutatePopulation();
		void updateBestSolution();

		void initializePopulation();
		
		int doTournament(int k);
		
	};
}

