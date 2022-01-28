#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "maxweight.hh"
#include "timer.hh"

using namespace std;

int main()
{
    ofstream greedy("greedy.csv");
    greedy << "n,seconds" << endl;
    greedy << fixed << setprecision(10);

    auto all_goods = load_cargo_database("cargo.csv");
    auto filtered_cargo = filter_cargo_vector(*all_goods, 1, 2500, all_goods->size());

    for(int i = 0; i < 2000; i++)
    {
        int n = i + 1;
        auto small_cargo = filter_cargo_vector(*filtered_cargo, 1, 2000, n);

        Timer timer;
        auto solution = greedy_max_weight(*small_cargo, 2000);
        greedy << n << "," << timer.elapsed() << endl;
    }
    greedy.close();

    ofstream exhaustive("exhaustive.csv");
    exhaustive << "n,seconds" << endl;
    exhaustive << fixed << setprecision(10);

    for(int i = 0; i < 22; i++)
    {
        int n = i + 1;
        auto small_cargo = filter_cargo_vector(*filtered_cargo, 1, 2000, n);

        Timer timer;
        auto solution = exhaustive_max_weight(*small_cargo, 2000);
        exhaustive << n << "," << timer.elapsed() << endl;
    }
    exhaustive.close();
}
