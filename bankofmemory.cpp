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
         require_auth( debtor );
         bankofmemory::tests existing(bankofmemory::code_account, debtor);
         eosio_assert(num <= 100, "100k at most");
         print("hahaahah");
         for( unsigned int i = 0; i < num; i++) {
           existing.emplace(debtor, [&](auto& o) {
             o.id = existing.available_primary_key();
           });
         }
      }

      /// @abi action 
      void release(account_name debtor, uint64_t num) {
         require_auth( debtor );
         bankofmemory::tests existing(bankofmemory::code_account, debtor);
         auto itr = existing.rend();
         print("num:", num);
         for( unsigned int i = 0; i < num; i++) {
           //eosio_assert(itr != existing.end(), "Address for account not found");
           //existing.erase(itr);
           //eosio_assert(itr != existing.end(), "Address not erased properly");
           itr--;
           print("i:", i);
         }
         // auto itr = existing.find(num);
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
