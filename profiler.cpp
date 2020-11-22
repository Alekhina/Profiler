#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <set>

//including files with realizations of trees
//#include ""
//#include ""

uint64_t p;
int factor = 10;
int a = 1;
int b = 17;
int i, j, k, N;
int min_k = 10;
int max_k = 20;

auto start = std::chrono::high_resolution_clock::now();
auto finish = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> interval = finish - start;

template <class T>
class Profiler
{
public:
    Profiler(){
        generating_big_prime_number();

        check_insert();
        check_find_and_erase();
    }
    ~Profiler(){

    }
private:
    T tested_tree;
    std::ofstream file, file1, file2;

    void generating_big_prime_number()
    {
        for (p = 1 ; p < factor ; p++){
            p *= p;
        }
        p--;
    }

    check_insert()
    {
        file.open("insert.csv");
        file << "logN"  << ',' << "t" << '\n';

        //just filling the beginning of the tree
        //auto u = tested_tree.insert(a % p);
        for (i = 0 ; i < pow(2, min_k) ; i++){
            tested_tree.insert(a*i % p);
        }

        //continue filling with recording
        for (k = min_k ; k < max_k ; k++){
            for (j = pow(2, k) ; j < pow(2, k+1) ; j++){
                start = std::chrono::high_resolution_clock::now();
                tested_tree.insert(a*j % p);
                finish = std::chrono::high_resolution_clock::now();
                interval = finish - start;
                file << k << ',' << interval.count() << '\n';
            }
        }

        for (i = pow(2, max_k) ; i < p ; i++){
            tested_tree.insert(a*j % p);
        }

        file.close();
    }

    check_find_and_erase()
    {
        file1.open("find.csv");
        file2.open("erase.csv");
        file1 << "logN"  << ',' << "t" << '\n';
        file2 << "logN"  << ',' << "t" << '\n';

        auto it = tested_tree.find(2);

        for (k = max_k ; k > min_k ; k--){
            for (j = pow(2, k) ; j < pow(2, k+1) ; j++){
                start = std::chrono::high_resolution_clock::now();
                it = tested_tree.find(b*j % p);
                finish = std::chrono::high_resolution_clock::now();
                interval = finish - start;
                file1 << k << ',' << interval.count() << '\n';
                if (it != tested_tree.end()){ //How does it work in our realization of trees?
                    start = std::chrono::high_resolution_clock::now();
                    tested_tree.erase(b*j % p);
                    finish = std::chrono::high_resolution_clock::now();
                    interval = finish - start;
                    file2 << k << ',' << interval.count() << '\n';
                }
            }
        }

        file1.close();
        file2.close();
    }
};


int main()
{

    Profiler<std::set<int>> set_profiler;


    //Profiler<AVL<uint64_t>> AVL_profiler;

    //Profiler<RB<uint64_t>> RB_profiler;

}
