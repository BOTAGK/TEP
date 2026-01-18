#include "MyEvaluator.hpp"
#include "GeneticAlgorithm.hpp"
#include "ProblemLoader.hpp"
#include <iostream>

using namespace LcVRPContest;

void StartOptimization(const string& folder_name, const string& instance_name, int maxIterations, bool useRandomPerm) {
	ProblemLoader problem_loader(folder_name, instance_name, useRandomPerm);
	ProblemData problem_data = problem_loader.loadData();

	cout << problem_data.getNumCustomers() << endl;
	cout << problem_data.getNumGroups() << endl;

	int num_groups = problem_data.getNumGroups();
	cout << num_groups << endl;
	cout << problem_data.getNumCustomers();
	/*Evaluator eval(problem_data, num_groups);*/

	MyEvaluator evaluator(problem_data);
	GAParams params;
	params.populationSize = 500;
	params.crossoverRate = 0.8;
	params.mutationRate = 0.05;


	GeneticAlgorithm optimizer(evaluator, params);

	optimizer.run(maxIterations);

	const vector<int>& best_solution = optimizer.getBestSolution();
	cout << "final best fitness: " << optimizer.getBestFitness() << endl;
}

int main() {

	StartOptimization("Vrp-Set-P", "P-n19-k2", 100, true);
	
	return 0;
}