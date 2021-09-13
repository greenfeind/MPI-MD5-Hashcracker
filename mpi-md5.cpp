#include <cstring>
#include <ctime>
#include <iostream>
#include <numeric> 
#include <sstream>
#include <string>
#include <mpi.h>
#include "md5.h"

#define min(a,b)	(((a)<(b)?(a):(b))
#define BStart(rank, p, n)	((rank)*(n)/(p))
#define BEnd(rank, p, n)	(BStart(((rank)+1),p,n)-1)
#define BSize(rank, p, n)	((BStart(((rank)+1), p, n)) - (BStart(rank, p, n)))
#define BOwner(index, p, n)	(((p)*(index)+1)-1)/(n))

using namespace std;

int test_hash(std::string hString, std::string tString){

	MD5 md5;
	char *tstr = new char[tString.length() + 1];
	strcpy(tstr, tString.c_str());
	if ( hString == md5.digestString(tstr) ){
		std::cout << "Match found: " << tString << std::endl; 
		return 10;}
		else { return 1; }
}

int main(int argc, char *argv[]){
	
	char cars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int carlen = 62;
	char inmsg[33];
	int tPassLen = 1;
	MD5 md5;
	std::string utString;
	std::string uHash;
	std::string tHash;
	std::string tPass;
	std::clock_t start;
	int test_res = 2;
	int size, rank;
	double sTime;
	char pName[MPI_MAX_PROCESSOR_NAME];
	char* inbuf;
	int szBuf = sizeof(inbuf) / sizeof(inbuf[0]);
	int name_len;
	uHash.assign("d891b1af94468381589ca9cc50e848f5") ;
	int hLen = uHash.length();
	
	MPI_Init(&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(pName, &name_len);
	
	int pStart = BStart(rank, size, (carlen));
	int pEnd = BEnd(rank, size, (carlen));
	int pSize = BSize(rank, size, (carlen));
	
	if (pEnd == 61){ pEnd = 61;}
	
	std::cout << pName << " has strings between " << cars[pStart] << " and " << cars[pEnd] << endl;
	
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) { 
		std::cout << "This program makes use of the md5.h file available from: \n";
		std::cout << "github.com/Ex094/HashcrackerV.2/blob/master/md5.h\n\n";
		std::cout << "The shorter the inital string, the longer its going to take" << endl;
		std::cout << "Regex for expected string: [0-9,A-Z,a-z,\" \"]{1,7}" << std::endl;
		std::cout << "Enter a MD5 hash to be cracked: " << std::endl; 
		fflush(stdout);
		std::cin >> uHash;
		std::cout << endl << endl;
		for ( int f = 1 ; f < size ; f++ ){
		MPI_Send(&uHash, hLen, MPI_CHAR, f, 1, MPI_COMM_WORLD);
		}} else {
		memset(inmsg, 0, hLen);
		MPI_Recv(&inmsg, hLen, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		uHash.assign(inmsg);
		}
	
		std::cout << endl << endl;
				
	MPI_Barrier(MPI_COMM_WORLD);
	
	if (rank == 0){ sTime = MPI_Wtime();}
			
	
	for(int i = (pStart) ; i <= pEnd ; i+=size){
		for(int j = 0 ; j < carlen ; j++){
			for(int k = 0 ; k < carlen ; k++){
				for(int l = 0 ; l < carlen ; l++){
					for(int m = 0 ; m < carlen ; m++){
						for(int n = 0 ; n < carlen ; n++){
							for(int o = 0 ; o < carlen ; o++){
								std::stringstream sstr;
								sstr << cars[i] << cars[j] << cars[k] << cars[l]; 
								sstr << cars[m] << cars[n] << cars[o];
								std::string tPass = sstr.str();
								if ( test_res ==  10 ) {
									break;
								} else { test_res = test_hash(uHash, tPass);
									if (test_res == 10) {
										MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
										break;
										}}
									
							}
							std::stringstream sstr;
							sstr << cars[i] << cars[j] << cars[k] << cars[l]; 
							sstr << cars[m] << cars[n];
							std::string tPass = sstr.str();
							if ( test_res ==  10 ) {
								break;
								} else { test_res = test_hash(uHash, tPass);
								if (test_res == 10) {
									MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
									break; }}
						}
						std::stringstream sstr;
						sstr << cars[i] << cars[j] << cars[k] << cars[l]; 
						sstr << cars[m];
						std::string tPass = sstr.str();
						if ( test_res ==  10 ) {
							break;
							} else { test_res = test_hash(uHash, tPass);
								if (test_res == 10) {
								MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
								break;}}
					}
					std::stringstream sstr;
					sstr << cars[i] << cars[j] << cars[k] << cars[l]; 
					std::string tPass = sstr.str();
					if ( test_res ==  10 ) {
						break;
					} else { test_res = test_hash(uHash, tPass);
						if (test_res == 10) {
							MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
							break;}}
				}
				std::stringstream sstr;
				sstr << cars[i] << cars[j] << cars[k]; 
				std::string tPass = sstr.str();
				if ( test_res ==  10 ) {
					break;
				} else { test_res = test_hash(uHash, tPass);
					if (test_res == 10) {
						MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
						break;}}
			}
			std::stringstream sstr;
			sstr << cars[i] << cars[j]; 
			std::string tPass = sstr.str();
			if ( test_res ==  10 ) {
				break;
			} else { test_res = test_hash(uHash, tPass);
				if (test_res == 10) {
					MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
					break;}
			}}
		std::stringstream sstr;
		sstr << cars[i]; 
		std::string tPass = sstr.str();
		if ( test_res ==  10 ) {
			break;
		} else { test_res = test_hash(uHash, tPass);
			if (test_res == 10) {
				MPI_Bcast(&test_res, 1, MPI_INT, 0, MPI_COMM_WORLD);
				break;}
		}
	}
	if (rank == 0){ 
		sTime = MPI_Wtime() - sTime;
		std::cout << "This program took " << sTime << "ms" << endl;
	}
	MPI_Finalize();
	return 0; 
			}
