#ifndef VARIABLES_H
#define VARIABLES_H

#include <cstring>
#include <iostream>

class Variables
{
protected:
    uint32_t blockid;         // Block ID
    std::string voter_id;     // Voter ID
    std::string name;         // Name
    std::string token;        // Token
    std::string ip;           // IP Address
    uint64_t nonce;           // Nonce
    time_t timestamp;         // Timestamp
    std::string voting_party; // Voting Party
    std::string prev_hash;    // Previous Block's Hash
    std::string hash;         // Current Block's Hash
};

#endif