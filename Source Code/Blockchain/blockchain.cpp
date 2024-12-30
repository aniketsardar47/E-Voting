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
    void gettophash();
    string getcurhash();
};

void Blockchain :: createBlock(){
    fstream f2("../../VotingQueueList/nonce.txt", ios::in);
    if (!f2.is_open()) {
        cerr << "Failed to open the file: nonce.txt" << endl;
    }

    string count;
    f2 >> count;
    nonce = stoi(count)+1;
    blockid = stoi(count);

    getdatafromjson();
    gettophash();
    curhash = getcurhash();

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
        std::cout << "Block ID: " << blockid << endl;
        std::cout << "Name: " << name << endl;
        std::cout << "Voting ID: " << voter_id << endl;
        std::cout << "Token: " << token << endl;
        std::cout << "IP: " << ip << endl;
        std::cout << "Timestamp: " << timestamp << endl;
        std::cout << "Voting Party: " << voting_party << endl;
        std::cout << "-----------------------" << endl;
    }
    f1.close();

}

void Blockchain:: gettophash(){
    fstream f1;
    f1.open("../../VotingQueueList/topentry.json");
    json blockchainData;

    for (const auto& block : blockchainData) {

        prev_hash = block["prev_hash"].get<string>();
        
    }

    f1.close();
}

string Blockchain:: getcurhash(){
    fstream f1;
    f1.open("../../VotingQueueList/newblock.txt");
    
    f1 << "Block ID:"<<blockid << endl;
    f1 << "Name:" <<name<< endl;
    f1 << "Voting ID:"<<voter_id << endl;
    f1 << "Token:"<<token << endl;
    f1 << "IP:"<<ip << endl;
    f1 << "Timestamp:"<<timestamp << endl;
    f1 << "Voting Party:"<<voting_party << endl;
    f1 << "Previous Hash:"<<prev_hash << endl;

    f1.close();

    return sha256();
    

}