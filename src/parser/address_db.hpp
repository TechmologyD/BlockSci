//
//  address_db.hpp
//  blocksci
//
//  Created by Harry Kalodner on 7/27/17.
//
//

#ifndef address_db_h
#define address_db_h

#include "address_traverser.hpp"

#include <blocksci/scripts/script_type.hpp>

#include <sqlite3.h>
#include <unordered_map>

struct ParserConfiguration;

class AddressDB : public AddressTraverser {
    sqlite3 *db;
    bool firstRun;
    std::unordered_map<blocksci::ScriptType::Enum,  sqlite3_stmt *> insertStatements;
    std::vector<blocksci::script::ScriptHash> p2shesToAdd;
    
    AddressDB(const ParserConfiguration &config, std::pair<sqlite3 *, bool> init);
    
    void addAddress(const blocksci::Address &address, const blocksci::OutputPointer &pointer);
    
    void sawAddress(const blocksci::Address &address, const blocksci::OutputPointer &pointer) override;
    void revealedP2SH(blocksci::script::ScriptHash &scriptHash, const blocksci::ScriptAccess &scripts) override;
    
    void tearDown(const blocksci::ScriptAccess &scripts) override;
    
public:
    AddressDB(const ParserConfiguration &config);
    
    void rollback(uint32_t maxTxIndex);
};

#endif /* address_db_h */
