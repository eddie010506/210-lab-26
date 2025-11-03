#include <iostream>
#include <chrono>
#include <fstream>  
#include <string>   
#include <vector>   
#include <list>     
#include <set>
#include <algorithm> 
#include <iomanip>  
#include <iterator> 
using namespace std;
using namespace chrono;

int main() {
    const int NUM_SIMULATIONS = 15;//number for loop count

    // edit 1 need for the data structures to be inside the loop to reset
    string line;

    long long total_read_vector_time=0, total_read_list_time=0, total_read_set_time=0;
    long long total_sort_vector_time=0, total_sort_list_time=0;
    long long total_insert_vector_time=0, total_insert_list_time=0, total_insert_set_time=0;
    long long total_delete_vector_time=0, total_delete_list_time=0, total_delete_set_time=0;
    //edit 2 need variables for total time and setting them 0

    for (int i = 0; i< NUM_SIMULATIONS; i++){
        //edit 3 copy and paste the previous code inside the loop and add data structures
        vector<string> my_vector;
        list<string> my_list;
        set<string> my_set;

        long long read_vector_time, read_list_time, read_set_time;
        long long sort_vector_time, sort_list_time;
        long long insert_vector_time, insert_list_time, insert_set_time;
        long long delete_vector_time, delete_list_time, delete_set_time;

        ifstream infile("codes.txt");
        if (!infile.is_open()) {
            cerr << "Error: Could not open codes.txt" << endl;
            return 1;
        }

    //race 1 reading
        auto start = high_resolution_clock::now();
        while (getline(infile, line)) {
            my_vector.push_back(line);
        }
        auto end = high_resolution_clock::now();
        read_vector_time = duration_cast<microseconds>(end - start).count();
        total_read_vector_time += read_vector_time;//edit 4 adding time to total

    // reset file stream to beginning
        infile.clear();
        infile.seekg(0, ios::beg);

    // time List Read
        start = high_resolution_clock::now();
        while (getline(infile, line)) {
            my_list.push_back(line);
        }
        end = high_resolution_clock::now();
        read_list_time = duration_cast<microseconds>(end - start).count();
        total_read_list_time += read_list_time;//edit 5 adding time to total

    // reset file stream to beginning
        infile.clear();
        infile.seekg(0, ios::beg);

        start = high_resolution_clock::now();
        while (getline(infile, line)) {
            my_set.insert(line);
        }
        end = high_resolution_clock::now();
        read_set_time = duration_cast<microseconds>(end - start).count();
        total_read_set_time += read_set_time;//edit 6 adding time to total

        infile.close();
    

    //race 2 sorting
        start = high_resolution_clock::now();
        sort(my_vector.begin(), my_vector.end());
        end = high_resolution_clock::now();
        sort_vector_time = duration_cast<microseconds>(end - start).count();
        total_sort_vector_time += sort_vector_time; // edit 7 adding time to total

    // time List Sort
        start = high_resolution_clock::now();
        my_list.sort();
        end = high_resolution_clock::now();
        sort_list_time = duration_cast<microseconds>(end - start).count();
        total_sort_list_time += sort_list_time; // edit 8 adding time to total

    //set is already sorted
    // race 3 insert
        const string test_value = "TEST";

    // time Vector Insert
        start = high_resolution_clock::now();
        my_vector.insert(my_vector.begin() + my_vector.size() / 2, test_value);
        end = high_resolution_clock::now();
        insert_vector_time = duration_cast<microseconds>(end - start).count();
        total_insert_vector_time += insert_vector_time; // edit 9 adding time to total
    // time List Insert 
        auto list_it = my_list.begin();
        advance(list_it, my_list.size() / 2);
        start = high_resolution_clock::now();
        my_list.insert(list_it, test_value);
        end = high_resolution_clock::now();
        insert_list_time = duration_cast<microseconds>(end - start).count();// seems too small for microseconds shows 0 sometimes but work normal on nanoseconds
        total_insert_list_time += insert_list_time; // edit 10 adding time to total
    // time Set Insert
        start = high_resolution_clock::now();
        my_set.insert(test_value);
        end = high_resolution_clock::now();
        insert_set_time = duration_cast<microseconds>(end - start).count();
        total_insert_set_time += insert_set_time; // edit 10 adding time to total

    //race 4 delete
    // time Vector Delete
        start = high_resolution_clock::now();
        my_vector.erase(my_vector.begin() + my_vector.size() / 2);
        end = high_resolution_clock::now();
        delete_vector_time = duration_cast<microseconds>(end - start).count();
        total_delete_vector_time += delete_vector_time;// edit 11 adding time to total
    // time List Delete 
        auto list_it_del = my_list.begin();
        advance(list_it_del, my_list.size() / 2);
        start = high_resolution_clock::now();
        my_list.erase(list_it_del);
        end = high_resolution_clock::now();
        delete_list_time = duration_cast<microseconds>(end - start).count();// seems too small for microseconds shows 0 sometimes but work normal on nanoseconds
        total_delete_list_time += delete_list_time;// edit 12 adding time to total


    // time Set Delete
        start = high_resolution_clock::now();
        my_set.erase(test_value);
        end = high_resolution_clock::now();
        delete_set_time = duration_cast<microseconds>(end - start).count();
        total_delete_vector_time += delete_vector_time;// edit 13 adding time to total



        
    }
    //moving   print out side the loop
    cout << "Number of simulations : "<< NUM_SIMULATIONS<< endl;
    cout << left << setw(10) << "Operation"<< setw(10) << "Vector"<< setw(10) << "List"<< setw(10) << "Set" << endl;
    cout << "----------------------------------------" << endl;

    cout << left << setw(10) << "Read"<< setw(10) << total_read_vector_time/NUM_SIMULATIONS<< setw(10) << total_read_list_time/NUM_SIMULATIONS<< setw(10) << total_read_set_time/NUM_SIMULATIONS << endl;

    cout << left << setw(10) << "Sort"<< setw(10) << total_sort_vector_time/NUM_SIMULATIONS<< setw(10) << total_sort_list_time/NUM_SIMULATIONS<< setw(10) << -1 << endl;

    cout << left << setw(10) << "Insert"<< setw(10) << total_insert_vector_time/NUM_SIMULATIONS<< setw(10) << total_insert_list_time/NUM_SIMULATIONS<< setw(10) << total_insert_set_time/NUM_SIMULATIONS << endl;

    cout << left << setw(10) << "Delete"<< setw(10) << total_delete_vector_time/NUM_SIMULATIONS<< setw(10) << total_delete_list_time/NUM_SIMULATIONS<< setw(10) << total_delete_set_time/NUM_SIMULATIONS << endl;
    return 0;
    
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/