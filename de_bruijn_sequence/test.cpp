#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Solution.h"

// description (from wikipedia):
// In combinatorial mathematics, a De Bruijn sequence of order n on a size-k alphabet A
// is a cyclic sequence in which every possible length-n string on A occurs exactly once
// as a substring (i.e., as a contiguous subsequence).
class checker
{
public:
    checker(size_t alphabet_size, size_t sequence_order)
        : alphabet_size(alphabet_size)
        , sequence_order(sequence_order)
    {}

    bool is_valid_de_bruijn_sequence(const std::vector<size_t>& sequence)
    {
        if(sequence_order == 0)
        {
            return sequence.empty();
        }
        if(sequence_order == 1)
        {
            return sequence.size()==1 && sequence[0]==0;
        }
        if(sequence.size() < sequence_order)
        {
            return false;
        }

        auto subsequences_ids = std::unordered_set<size_t>{};
        auto subsequence = std::vector<size_t>{};
        subsequence.reserve(alphabet_size);
        for(size_t begin_idx=0; begin_idx<sequence.size(); ++begin_idx)
        {
            subsequence.clear();
            for(size_t i=0; i<sequence_order; ++i)
            {
                auto idx = (begin_idx + i) % sequence.size();
                subsequence.push_back(sequence[idx]);
            }
            auto subsequence_id = get_subsequence_id(subsequence, alphabet_size);
            subsequences_ids.insert(subsequence_id);
        }

        auto max_subsequence_id_plus_one = get_max_subsequence_id_plus_one(alphabet_size, sequence_order);
        for(size_t id=0; id<max_subsequence_id_plus_one; ++id)
        {
            auto pos = subsequences_ids.find(id);
            if(pos == subsequences_ids.cend())
            {
                return false;
            }
            subsequences_ids.erase(pos);
        }
        return subsequences_ids.empty();
    }

private:
    size_t get_subsequence_id(const std::vector<size_t>& subsequence, size_t alphabet_size)
    {
        size_t id = 0;
        size_t factor = 1;
        for(auto symbol : subsequence)
        {
            id += symbol * factor;
            factor *= alphabet_size;
        }
        return id;
    }

    size_t get_max_subsequence_id_plus_one(size_t alphabet_size, size_t sequence_order)
    {
        size_t max_id = 1;
        for(size_t i=0; i<sequence_order; ++i)
        {
            max_id *= alphabet_size;
        }
        return max_id;
    }

private:
    size_t alphabet_size;
    size_t sequence_order;
};

TEST_CASE("alphabet size=2, sequence order=0")
{
    auto expected_sequence = std::vector<size_t>{ };
    auto actual_sequence = Solution{}.solveDeBruijnSequence(2, 0);
    REQUIRE((checker{2, 0}.is_valid_de_bruijn_sequence(actual_sequence)));
    REQUIRE(actual_sequence == expected_sequence);
}

TEST_CASE("alphabet size=2, sequence order=1")
{
    auto expected_sequence = std::vector<size_t>{ 0 };
    auto actual_sequence = Solution{}.solveDeBruijnSequence(2, 1);
    REQUIRE((checker{2, 1}.is_valid_de_bruijn_sequence(actual_sequence)));
    REQUIRE(actual_sequence == expected_sequence);
}

TEST_CASE("alphabet size=2, sequence order=2")
{
    auto expected_sequence = std::vector<size_t>{ 0, 0, 1, 1 };
    auto actual_sequence = Solution{}.solveDeBruijnSequence(2 , 2);
    REQUIRE((checker{2, 2}.is_valid_de_bruijn_sequence(actual_sequence)));
    REQUIRE(actual_sequence == expected_sequence);
}

TEST_CASE("alphabet size=2, sequence order=3")
{
   auto actual_sequence = Solution{}.solveDeBruijnSequence(2, 3);
   REQUIRE((checker{2, 3}.is_valid_de_bruijn_sequence(actual_sequence)));
   auto expected_sequence = std::vector<size_t>{ 0, 0, 0, 1, 0, 1, 1, 1 };
   REQUIRE(actual_sequence == expected_sequence);
}

TEST_CASE("alphabet size=2, sequence order=4")
{
   auto actual_sequence = Solution{}.solveDeBruijnSequence(2, 4);
   REQUIRE((checker{2, 4}.is_valid_de_bruijn_sequence(actual_sequence)));
}

TEST_CASE("alphabet size=3, sequence order=4")
{
   auto actual_sequence = Solution{}.solveDeBruijnSequence(3, 4);
   REQUIRE((checker{3, 4}.is_valid_de_bruijn_sequence(actual_sequence)));
}

//I used this sequence with alphabet {A, M, S, X} to make "merry Christmas" wishes
TEST_CASE("alphabet size=4, sequence order=4")
{
   auto actual_sequence = Solution{}.solveDeBruijnSequence(4, 4);
   REQUIRE((checker{4, 4}.is_valid_de_bruijn_sequence(actual_sequence)));
}

TEST_CASE("alphabet size=4, sequence oder=10 (output length = 2^20)")
{
    auto actual_sequence = Solution{}.solveDeBruijnSequence(4, 10);
    REQUIRE((checker{4, 10}.is_valid_de_bruijn_sequence(actual_sequence)));
}

TEST_CASE("alphabet size=10, sequence oder=6 (output length = 10^6)")
{
    auto actual_sequence = Solution{}.solveDeBruijnSequence(10, 6);
    REQUIRE((checker{10, 6}.is_valid_de_bruijn_sequence(actual_sequence)));
}
