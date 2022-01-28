///////////////////////////////////////////////////////////////////////////////
// maxweight_test.cc
//
// Unit tests for maxweight.hh
//
///////////////////////////////////////////////////////////////////////////////


#include <cassert>
#include <sstream>


#include "maxweight.hh"
#include "rubrictest.hh"


int main()
{
	Rubric rubric;
	
	CargoVector trivial_cargo;
	trivial_cargo.push_back(std::shared_ptr<CargoItem>(new CargoItem("test car tires", 100.0, 20.0)));
	trivial_cargo.push_back(std::shared_ptr<CargoItem>(new CargoItem("test corn", 40.0, 5.0)));
	
	auto all_cargo = load_cargo_database("cargo.csv");
	assert( all_cargo );
	
	auto filtered_cargo = filter_cargo_vector(*all_cargo, 1, 2500, all_cargo->size());
	
	//
	rubric.criterion(
		"load_cargo_database still works", 2,
		[&]()
		{
			TEST_TRUE("non-null", all_cargo);
			TEST_EQUAL("size", 8064, all_cargo->size());
		}
	);
	
	//
	rubric.criterion(
		"filter_cargo_vector", 2,
		[&]()
		{
			auto
				three = filter_cargo_vector(*all_cargo, 100, 500, 3),
				ten = filter_cargo_vector(*all_cargo, 100, 500, 10);
			TEST_TRUE("non-null", three);
			TEST_TRUE("non-null", ten);
			TEST_EQUAL("total_size", 3, three->size());
			TEST_EQUAL("total_size", 10, ten->size());
			TEST_EQUAL("contents", "enriched yellow soybean", (*ten)[0]->description());
			TEST_EQUAL("contents", "Idaho barley", (*ten)[9]->description());
			for (int i = 0; i < 3; i++) {
				TEST_EQUAL("contents", (*three)[i]->description(), (*ten)[i]->description());
			}
		}
	);
	
	//
	rubric.criterion(
		"greedy_max_weight trivial cases", 2,
		[&]()
		{
			std::unique_ptr<CargoVector> soln;
			
			soln = greedy_max_weight(trivial_cargo, 10);
			TEST_TRUE("non-null", soln);
			TEST_TRUE("empty solution", soln->empty());
			
			soln = greedy_max_weight(trivial_cargo, 100);
			TEST_TRUE("non-null", soln);
			TEST_EQUAL("car tires only", 1, soln->size());
			TEST_EQUAL("car tires only", "test car tires", (*soln)[0]->description());
			
			soln = greedy_max_weight(trivial_cargo, 99);
			TEST_TRUE("non-null", soln);
			TEST_EQUAL("corn only", 1, soln->size());
			TEST_EQUAL("corn only", "test corn", (*soln)[0]->description());
			
			soln = greedy_max_weight(trivial_cargo, 150);
			TEST_TRUE("non-null", soln);
			TEST_EQUAL("car tires and corn", 2, soln->size());
			TEST_EQUAL("car tires and corn", "test car tires", (*soln)[0]->description());
			TEST_EQUAL("car tires and corn", "test corn", (*soln)[1]->description());
		}
	);
	
	//
	rubric.criterion(
		"greedy_max_weight correctness", 4,
		[&]()
		{
			std::unique_ptr<CargoVector> soln_small, soln_large;
			
			soln_small = greedy_max_weight(*filtered_cargo, 500),
			soln_large = greedy_max_weight(*filtered_cargo, 5000);
			
			//print_cargo_vector(*soln_small);
			//print_cargo_vector(*soln_large);
			
			TEST_TRUE("non-null", soln_small);
			TEST_TRUE("non-null", soln_large);
			
			TEST_FALSE("non-empty", soln_small->empty());
			TEST_FALSE("non-empty", soln_large->empty());
			
			double
				volume_small, weight_small,
				volume_large, weight_large
				;
			sum_cargo_vector(*soln_small, volume_small, weight_small);
			sum_cargo_vector(*soln_large, volume_large, weight_large);
			
			//	Precision
			volume_small	= std::round( volume_small	* 100 ) / 100;
			weight_small	= std::round( weight_small	* 100 ) / 100;
			volume_large	= std::round( volume_large	* 100 ) / 100;
			weight_large	= std::round( weight_large	* 100 ) / 100;
			
			TEST_EQUAL("Small solution volume",	481.48,	volume_small);
			TEST_EQUAL("Small solution weight",	950.19,	weight_small);
			TEST_EQUAL("Large solution volume",	4990.35, volume_large);
			TEST_EQUAL("Large solution weight",	9209.82, weight_large);
		}
	);
	
	//
	rubric.criterion(
		"exhaustive_max_weight trivial cases", 2,
		[&]()
		{
			std::unique_ptr<CargoVector> soln;
			
			//soln = exhaustive_max_weight(trivial_cargo, 10);
			//TEST_TRUE("non-null", soln);
			//TEST_TRUE("empty solution", soln->empty());
			
			//soln = exhaustive_max_weight(trivial_cargo, 100);
			//TEST_TRUE("non-null", soln);
			//TEST_EQUAL("car tires only", 1, soln->size());
			//TEST_EQUAL("car tires only", "test car tires", (*soln)[0]->description());
			
			soln = exhaustive_max_weight(trivial_cargo, 99);
			TEST_TRUE("non-null", soln);
			TEST_EQUAL("corn only", 1, soln->size());
			TEST_EQUAL("corn only", "test corn", (*soln)[0]->description());
			
			soln = exhaustive_max_weight(trivial_cargo, 150);
			TEST_TRUE("non-null", soln);
			TEST_EQUAL("car tires and corn", 2, soln->size());
			TEST_EQUAL("car tires and corn", "test car tires", (*soln)[0]->description());
			TEST_EQUAL("car tires and corn", "test corn", (*soln)[1]->description());
		}
	);
	
	//
	rubric.criterion(
		"exhaustive_max_weight correctness", 4,
		[&]()
		{
			std::vector<double> optimal_weight_totals =
			{
				500,		1033.05,	1100,	1600,	1600,
				1600,		1900,		2100,	2300,	2300,
				2300,		2300,		2400,	2400,	2400,
				2400,		2400,		2400,	2400,	2400
			};
			
			for ( int optimal_index = 0; optimal_index < optimal_weight_totals.size(); optimal_index++ )
			{
				int n = optimal_index + 1;
				double expected_weight = optimal_weight_totals[optimal_index];
				
				auto small_cargo = filter_cargo_vector(*filtered_cargo, 1, 2000, n);
				TEST_TRUE("non-null", small_cargo);
				
				auto solution = exhaustive_max_weight(*small_cargo, 2000);
				TEST_TRUE("non-null", solution);
				
				double actual_volume, actual_weight;
				sum_cargo_vector(*solution, actual_volume, actual_weight);
				
				// Round
				expected_weight	= std::round( expected_weight	/ 100.0) * 100;
				actual_weight		= std::round( actual_weight	/ 100.0) * 100;
				
				std::stringstream ss;
				ss
					<< "exhaustive optimization n = " << n << " (optimal index = " << optimal_index << ")"
					<< ", expected weight = " << expected_weight
					<< " but algorithm found = " << actual_weight
					;
				TEST_EQUAL(ss.str(), expected_weight, actual_weight);
				
				auto greedy_solution = greedy_max_weight(*small_cargo, 2000);
				double greedy_actual_volume, greedy_actual_weight;
				sum_cargo_vector(*solution, greedy_actual_volume, greedy_actual_weight);
				greedy_actual_weight	= std::round( greedy_actual_weight	/ 100.0) * 100;
				TEST_EQUAL("Exhaustive and greedy get the same answer", actual_weight, greedy_actual_weight);
			}
		}
	);

	return rubric.run();
}




