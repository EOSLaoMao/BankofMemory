#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <bankofmemory.hpp>

using namespace eosio;
//using namespace print;

class BankofMemory : public eosio::contract {
  public:
      using contract::contract;

      // create offer record
      /// @abi action 
      void polute(account_name debtor, uint64_t num) {
         print("polute called!!!");
         require_auth( debtor );
         bankofmemory::tests existing(bankofmemory::code_account, debtor);
         eosio_assert(num <= 100, "100k at most");
         for( unsigned int i = 0; i < num; i++) {
           existing.emplace(debtor, [&](auto& o) {
             o.id = existing.available_primary_key();
              for( unsigned int i = 0; i < 128; i++) {
                  print(" | i:", i);
                  print(" board[i]:", o.board[i]);
              }
           });
         }
      }

      /// @abi action 
      void release(account_name debtor, uint64_t num) {
         print("release called!!!");
         require_auth( debtor );
         bankofmemory::tests existing(bankofmemory::code_account, debtor);
         for( unsigned int i = 0; i < num; i++) {
           auto itr = existing.end();
           itr--;
           //eosio_assert(itr != existing.end(), "Address for account not found");
           existing.erase(itr);
           //eosio_assert(itr != existing.end(), "Address not erased properly");
         }
      }
};


/**
*  The apply() methods must have C calling convention so that the blockchain can lookup and
*  call these methods.
*/
extern "C" {

   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      print("tx recieved inside bankofmemory!!!!", receiver);
      print(" | code:", code);
      print(" | action:", action);
      if(code == receiver) {
        print(" | GOT IT!!");
        BankofMemory thiscontract(receiver);
        if (action == N(polute)){
          print(" | gonna call polute!!!");
          execute_action( &thiscontract, &BankofMemory::polute );
        } else if (action == N(release)){
          print(" | another action called!!!!");
          execute_action( &thiscontract, &BankofMemory::release );
        }
      } else {
        print(" | not mine business......");
      }
   }

} // extern "C"
