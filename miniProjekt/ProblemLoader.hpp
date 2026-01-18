#pragma once
#include <string>
#include "ProblemData.hpp"


namespace LcVRPContest {
	class ProblemLoader {
	public:
		ProblemLoader(const std::string& directory, const std::string& filename, bool forceRandomPermutation = true);

		ProblemData loadData();
	private:
		std::string filePath_;
		bool randomizePermutation_;

		void readFile(std::ifstream& file, ProblemData& data);

		void skipDelimiters(std::ifstream& file);

		void parseNodeCoords(std::ifstream& file, ProblemData& data);
		void parseDemands(std::ifstream& file, ProblemData& data);
		void parseEdgeWeights(std::ifstream& file, ProblemData& data);
		void parseDepot(std::ifstream& file, ProblemData& data);
		void parsePermutation(std::ifstream& file, ProblemData& data);


		void generateRandomPermutation(ProblemData& instance) const;
	};
}


