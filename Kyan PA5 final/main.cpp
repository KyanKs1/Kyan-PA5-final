#include "ChainingHash.h"
#include "ProbingHash.h"
#include "ParallelProbingHash.h" 
#include <omp.h>
#include <chrono>
#include <ostream>
#include <fstream>

#define NUM_THREADS 6 // update this value with the number of cores in your system. 
/*Programer Kyan Kotschevar-Smead,(Alone)
* Pa 5 HashTables
*3/22/2023
* . (6 pts) How did the serial implementations for the ChainingHash and ProbingHash
compare to each other? Did you expect the time results obtained? Explain.
With my hash function they should have similar times  I have no idea why my chain implementation is way faster i tried looking but couldnt find the error.
I believe most of it has to do with the rehash but i use move in both. With my hash i did expect the same load factor and buckets but under a different i would expect
the chain to have a lower load factor and less size and greater complexity

2. (6 pts) Compare the parallel and serial implementations for the ProbingHash. Did the
parallel implementations provide you with the expected speedup? Explain.
Parrellization speed up the program but not as significantly as i would have expected. The difference from 1 thread to 6 was a huge difference.
i can see openmp being used for more data structrers such as a tree.

3. (6 pts) What could you change in your parallel implementations to improve performance and
speedup? Explain
technecially to really speed up the finding and deleting i could implement a parrellel loop but it would be negleible as there are near linear complexitys with 0s 
time for implmentation. i do not not beleive much else could be optimized.
*/
int main()
{
	/*Task I (a)- ChainingHash table*/

		//  create an object of type ChainingHash 
	ChainingHash<int,int> Chash(11);
		// In order, insert values with keys 1 – 1,000,000. For simplicity, the key and value stored are the same. 
	// Report the total amount of time, in seconds, required to insert the values to ChainingHash table. Write the results to a file called “HashAnalysis.txt”. 
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 30000; i++)
	{
		Chash.insert(std::make_pair(i, i));
	}
	auto end = std::chrono::high_resolution_clock::now();
	double time_taken =	std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() /1000.0;
	cout << time_taken << endl;
	std::ofstream output("HashAnalysis.txt");
	output << "\nChaning table\nTime taken to insert 1,000,000 values to ChainingHash table: "
		<< time_taken << " seconds." << std::endl;
	

	
		
		// Search for the value with key 177 in ChainingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
	
	start = std::chrono::high_resolution_clock::now();
	int p = Chash.at(177);
	 end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 117 " << time_taken << endl;
	output << "time taken to search for 117 : " << time_taken << "  : Value : " <<p  <<endl;
		// Search for the value with key 2,000,000 in ChainingHash table. Report the time required to find the value in each table by writing it to the file.  
	
	start = std::chrono::high_resolution_clock::now();
	 p = Chash.at(20000);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 20000 " << time_taken << endl;
	output << "time taken to search for 20000 : " << time_taken << "  : Value : " << p << endl;
		// Remove the value with key 177 from ChainingHash table. Report the time required to remove the value with in each table by writing it to the file.  
	
	start = std::chrono::high_resolution_clock::now();
	 Chash.erase(117);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to delete 117 " << time_taken << endl;
	output << "time taken to delete 117 : " << time_taken  << endl;
		// Also, write to the file the final size, bucket count, and load factor of the hash for ChainingHash table. 
	output <<"TableSize : " << Chash.getCurrentSize() << "\nBucketCount: " << Chash.bucket_count() << "\nLoadFactor: " << Chash.load_factor() << endl;
		/* Example output template:
			Chaining insertion time:
			Chaining search time:
			Chaining failed search time:
			Chaining deletion time:
			Table size:
			Bucket count:
			Load factor:
		*/

		/*Task I (b) - ProbingHash table (using Linear Probing) */

			//  create an object of type ProbingHash 
	ProbingHash<int, int> Phash(11);
	// In order, insert values with keys 1 – 1,000,000. For simplicity, the key and value stored are the same. 
// Report the total amount of time, in seconds, required to insert the values to ChainingHash table. Write the results to a file called “HashAnalysis.txt”. 
	 start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 30000; i++)
	{
		Phash.insert(std::make_pair(i, i));
	}
	end = std::chrono::high_resolution_clock::now();
	 time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;

			// Report the total amount of time, in seconds, required to insert the values to ProbingHash table. Write the results to a file called “HashAnalysis.txt”. 
	 time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << time_taken << endl;
	output << "\nProbing Table\nTime taken to insert 1,000,000 values to Probing table: "
		<< time_taken << " seconds." << std::endl;
			// Search for the value with key 177 in ProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 

	start = std::chrono::high_resolution_clock::now();
	 p = Phash.at(177);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 117 " << time_taken << endl;
	output << "time taken to search for 117 : " << time_taken << "  : Value : " << p << endl;
			// Search for the value with key 2,000,000 in ProbingHash table. Report the time required to find the value in each table by writing it to the file.  

	start = std::chrono::high_resolution_clock::now();
	 p = Phash.at(20000);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 20000 " << time_taken << endl;
	output << "time taken to search for 20000 : " << time_taken << "  : Value : " << p << endl;
			// Remove the value with key 177 from ProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

	start = std::chrono::high_resolution_clock::now();
	Phash.erase(117);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to delete 117 " << time_taken << endl;
	output << "time taken to delete 117 : " << time_taken << endl;
			// Also, write to the file the final size, bucket count, and load factor of the hash for ProbingHash table. 
	output << "TableSize : " << Phash.getcurrentSize() << "\nBucketCount: " << Phash.bucket_count() << "\nLoadFactor: " << Phash.load_factor() << endl;
			/* Example output template:
				Linear Probing insertion time:
				Linear Probing search time:
				Linear Probing failed search time:
				Linear Probing deletion time:
				Table size:
				Bucket count:
				Load factor:
			*/

			


			  // (a) Using a single thread:  
				//  create an object of type ParallelProbingHash 
	omp_set_num_threads(1);
	ParallelProbingHash<int, int> PPhash(11);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 30000; i++)
	{
		PPhash.insert(std::make_pair(i, i));
	}
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << time_taken << endl;
	output << "\n 1 thread\nTime taken to insert 1,000,000 values to 1 thread table: "
		<< time_taken << " seconds." << std::endl;


	start = std::chrono::high_resolution_clock::now();
	p = PPhash.at(177);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 117 " << time_taken << endl;
	output << "time taken to search for 117 : " << time_taken << "  : Value : " << p << endl;
	// Search for the value with key 2,000,000 in ProbingHash table. Report the time required to find the value in each table by writing it to the file.  

	start = std::chrono::high_resolution_clock::now();
	p = PPhash.at(20000);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 20000 " << time_taken << endl;
	output << "time taken to search for 20000 : " << time_taken << "  : Value : " << p << endl;
	// Remove the value with key 177 from ProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

	start = std::chrono::high_resolution_clock::now();
	PPhash.erase(117);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to delete 117 " << time_taken << endl;
	output << "time taken to delete 117 : " << time_taken << endl;
	// Also, write to the file the final size, bucket count, and load factor of the hash for ProbingHash table. 
	output << "TableSize : " << PPhash.getcurrentSize() << "\nBucketCount: " << PPhash.bucket_count() << "\nLoadFactor: " << PPhash.load_factor() << endl;
				// Set the number of threads (omp_set_num_threads()) to 1 

				/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000.
				Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads.
				For simplicity, the key and value stored are the same.
				*/
				// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

				// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 

				// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

				// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

				// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

				/* Example output template:
					Parallel Probing insertion time:
					Parallel Probing search time:
					Parallel Probing failed search time:
					Parallel Probing deletion time:
					Table size:
					Bucket count:
					Load factor:
				*/



				// (b) Using
				// 
				// 
				// multiple threads:  
					//  create an object of type ParallelProbingHash 

					// i.	Change the number of threads to match the number of cores on your system 

					/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000.
					Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads.
					For simplicity, the key and value stored are the same.
					*/
					// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

					// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 

					// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

					// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

					// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

					/* Example output template:
						Parallel Probing insertion time:
						Parallel Probing search time:
						Parallel Probing failed search time:
						Parallel Probing deletion time:
						Table size:
						Bucket count:
						Load factor:
					*/
	omp_set_num_threads(omp_get_max_threads());
	ParallelProbingHash<int, int> PPPhash(11);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 30000; i++)
	{
		PPPhash.insert(std::make_pair(i, i));
	}
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << time_taken << endl;
	output << "\nMAX THREAD\nTime taken to insert 1,000,000 values to a MAX thread table: "
		<< time_taken << " seconds." << std::endl;

	// Report the total amount of time, in seconds, required to insert the values to ProbingHash table. Write the results to a file called “HashAnalysis.txt”. 
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << time_taken << endl;
	output << "Time taken to insert 1,000,000 values to a MAX thread table: "
		<< time_taken << " seconds." << std::endl;
	// Search for the value with key 177 in ProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 

	start = std::chrono::high_resolution_clock::now();
	p = PPPhash.at(177);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 117 " << time_taken << endl;
	output << "time taken to search for 117 : " << time_taken << "  : Value : " << p << endl;
	// Search for the value with key 2,000,000 in ProbingHash table. Report the time required to find the value in each table by writing it to the file.  

	start = std::chrono::high_resolution_clock::now();
	p = PPPhash.at(20000);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to search for 20000 " << time_taken << endl;
	output << "time taken to search for 20000 : " << time_taken << "  : Value : " << p << endl;
	// Remove the value with key 177 from ProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

	start = std::chrono::high_resolution_clock::now();
	PPPhash.erase(117);
	end = std::chrono::high_resolution_clock::now();
	time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
	cout << "Time taken to delete 117 " << time_taken << endl;
	output << "time taken to delete 117 : " << time_taken << endl;
	// Also, write to the file the final size, bucket count, and load factor of the hash for ProbingHash table. 
	output << "TableSize : " << PPPhash.getcurrentSize() << "\nBucketCount: " << PPPhash.bucket_count() << "\nLoadFactor: " << PPPhash.load_factor() << endl;
	// Set the number of threads (omp_set_num_threads()) to 1 
	return 0;
}