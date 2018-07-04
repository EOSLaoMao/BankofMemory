#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <helloworld.hpp>
using namespace eosio;

class BankofStaked : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void create( account_name debtor, asset amount, asset interest, uint64_t affected_blocks) {
         require_auth( debtor );
         print( "Hello, ", name{debtor}, "\n" );
         print( "amount, ", amount, "\n" );
         print( "interest, ", interest, "\n" );
         bankofstaked::offersv12 existing(bankofstaked::code_account, debtor);
         print("affected_blocks: ", affected_blocks, "\n");
         existing.emplace(debtor, [&](auto& o) {
           print("inner called!!!\n");
           o.debtor = debtor;
           print("1st call!!!\n");
           o.affected_blocks = affected_blocks;
           print("2nd call!!!\n");
           o.amount = amount;
           print("3rd call!!!\n");
           o.interest = interest;
           print("4th call!!!\n");
           o.id = existing.available_primary_key();
           print("5th call!!!\n");
         });
      }
};


/**
*  The apply() methods must have C calling convention so that the blockchain can lookup and
*  call these methods.
*/
extern "C" {

   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      print("tx recieved inside bankofstaked!!!!\n", receiver);
      if(code == receiver) {
        print("GOT IT!!");
        BankofStaked thiscontract(receiver);
        execute_action( &thiscontract, &BankofStaked::create );
      } else {
        print("not mine business......");
      }
   }

} // extern "C"
