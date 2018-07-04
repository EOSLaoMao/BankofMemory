#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <bankofmemory.hpp>

using namespace eosio;

class BankofMemory : public eosio::contract {
  public:
      using contract::contract;

      // create offer record
      /// @abi action 
      void polute(account_name debtor, uint64_t num) {
         print("polute called!!!");
         // static const uint64_t number = 18446744073709551615;
         static const uint64_t number = 0;
         require_auth( debtor );
         bankofmemory::tests existing(bankofmemory::code_account, debtor);
         print("num: ", num, "\n");
         existing.emplace(debtor, [&](auto& o) {
           /*
           for( unsigned int i = 0; i < 1024; i++) {
              o.board[i] = number;
           }
           */
           o.id = existing.available_primary_key();
         });
      }

      /// @abi action 
      void release(account_name debtor, uint64_t num) {
         print("polute called!!!");
         static const uint64_t number = 8423864872364234;
         print("num: ", num, "\n");
         require_auth( debtor );
         bankofmemory::tests existing(bankofmemory::code_account, debtor);
         auto itr = existing.find(num);
         eosio_assert(itr != existing.end(), "Address for account not found");
         existing.erase(itr);
         eosio_assert(itr != existing.end(), "Address not erased properly");
      }
};


/**
*  The apply() methods must have C calling convention so that the blockchain can lookup and
*  call these methods.
*/
extern "C" {

   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      print("tx recieved inside bankofmemory!!!!\n", receiver);
      if(code == receiver) {
        print("GOT IT!!");
        BankofMemory thiscontract(receiver);
        if (action == N(polute)){
          print("gonna call polute!!!");
          execute_action( &thiscontract, &BankofMemory::polute );
        } else if (action == N(release)){
          print("another action called!!!!");
          execute_action( &thiscontract, &BankofMemory::release );
        }
      } else {
        print("not mine business......");
      }
   }

} // extern "C"
