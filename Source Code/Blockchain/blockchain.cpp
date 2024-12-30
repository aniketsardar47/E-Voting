#include<iostream>
#include<fstream>
#include<cstdint>
#include "includes/json.hpp"
#include "SHA256.h"
#include "VARIABLES.h"
using namespace std;
using json = nlohmann::json;
class Blockchain : public Variables{
public:
    void createBlock();
    void checkBlock();
    void createGenesisBlock();
    void getTopBlock();
    void getdatafromjson();
};

void Blockchain :: createBlock(){
    fstream f2("../../VotingQueueList/nonce.txt", ios::in);
    if (!f2.is_open()) {
        cerr << "Failed to open the file: nonce.txt" << endl;
    }

    string count;
    f2 >> count;
    
    f2.close();


}

void Blockchain :: createGenesisBlock(){
    blockid = 0;
    prev_hash = "00000000";
  
    fstream f2("../../VotingQueueList/nonce.txt", ios::in);
    if (!f2.is_open()) {
        cerr << "Failed to open the file: nonce.txt" << endl;
    }

    string count;
    while (getline(f2, count)) {
        cout << "Nonce: " << count << endl; 
    }
    f2.close();

}

void Blockchain:: getdatafromjson(){
    fstream f1;
    f1.open("../../VotingQueueList/toplist.json");
    json blockchainData;
   try {
        f1 >> blockchainData; // Parse the JSON file
    } catch (const json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        f1.close();
        return;
    }

    // Loop through the JSON array
    for (const auto& block : blockchainData) {

        // Extract data from each JSON object and store in BlockchainBlock
        blockid = block["blockid"].get<int>();
        name = block["name"].get<string>();
        voter_id = block["votingid"].get<int>();
        token = block["token"].get<string>();
        ip = block["ip"].get<string>();
        timestamp = block["timestamp"].get<time_t>();
        voting_party = block["voting_party"].get<string>();

        // Output the data
        std::cout << "Block ID: " << blockid << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Voting ID: " << voter_id << std::endl;
        std::cout << "Token: " << token << std::endl;
        std::cout << "IP: " << ip << std::endl;
        std::cout << "Timestamp: " << timestamp << std::endl;
        std::cout << "Voting Party: " << voting_party << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
    f1.close();
}