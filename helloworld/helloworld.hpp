/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

namespace bankofstaked {
   static const account_name offers_account = N(offersv12);
   static const account_name code_account = N(bankofstaked);

   /**
    * @brief Data structure to hold offer information
    */
   //@abi table offersv12 i64
   struct offer {
      // offer() { initialize_state(); }
      uint64_t         id;
      account_name     creditor = N(none);
      account_name     debtor; // amount of EOS token debtor want to be staked, TODO float
      eosio::asset     amount; // amount of EOS token debtor want to be staked, TODO float
      eosio::asset     interest; // amount of EOS token debtor want to pay for creditor, TODO float
      uint64_t         affected_blocks; // the blocks debtor want to have staked token for
      uint64_t         block_num_created; // the block number this offer generated
      /*
       * block_num_expired = block_num_created + 120 * 5 (block_num_delta, 5 mins)
       * offer will expire in 5 mins if there's no creditor to take this offer
       */
      uint64_t         block_num_expired;
      /* state of offer
       * 0 - created, waiting for creditor to take this offer
       * 1 - taken, creditor has taken this offer(will extend 5mins for creditor to stake EOS token)
       * 2 - staked, creditor has staked the required EOS token(>=amount)
       * 3 - fulfilled, creditor has staked token for required amount of time(unstake block num >= block_num_due)
       * 4 - failed, creditor has failed to staked for required amount of time(unstake block num < block_num_due)
       */
      uint8_t          state;

      auto primary_key() const { return id; }

      EOSLIB_SERIALIZE( offer, (id)(creditor)(debtor)(amount)(interest)(affected_blocks)(block_num_created)(block_num_expired)(state) )
   };

   /**
    * @brief Action to create new offer
    */
   //@abi action
   struct create {
      account_name     debtor; // amount of EOS token debtor want to be staked, TODO float
      eosio::asset     amount; // amount of EOS token debtor want to be staked, TODO float
      eosio::asset     interest; // amount of EOS token debtor want to be staked, TODO float
      uint64_t         affected_blocks; // the blocks debtor want to have staked token for

      EOSLIB_SERIALIZE( create, (debtor)(amount)(interest)(affected_blocks) )
   };


   /**
    * @brief table definition, used to store existing offers and their current state
    */
   //@abi table
   typedef eosio::multi_index< offers_account, offer> offersv12;
   // offersv12 offers;
}
/// @}
