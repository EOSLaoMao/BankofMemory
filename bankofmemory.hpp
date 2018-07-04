/**
 *  @file bankofmemory.hpp
 */
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

namespace bankofmemory {
   static const account_name code_account = N(bankofmemory);
   static const account_name tests_account = N(tests);
   static const uint32_t board_len = 128;


   /**
    * @brief Data structure to hold offer information
    */
   //@abi table tests i64
   struct test {
      uint64_t        id;
      uint64_t        board[board_len];

      auto primary_key() const { return id; }

      EOSLIB_SERIALIZE( test, (id)(board) )
   };

   //@abi action
   struct polute {
      uint64_t    num; // the size of memory you want to deposit, in KB

      EOSLIB_SERIALIZE( polute, (num) )
   };
   //@abi action
   struct release {
      uint64_t    num; // the size of memory you want to withdraw, in KB

      EOSLIB_SERIALIZE( release, (num) )
   };
   //@abi table
   typedef eosio::multi_index< tests_account, test > tests;
}
