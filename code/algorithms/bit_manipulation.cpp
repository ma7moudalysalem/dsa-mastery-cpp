// Bit Manipulation (Week 16)
//
// Builds a small set of bit-level routines: population count, power-of-two
// test, single-number search via XOR, single-bit get/set/clear/toggle, and a
// cumulative set-bit count over a range.
//
// Compile: g++ -std=c++17 -Wall bit_manipulation.cpp -o out
// Run:     ./out
//
// Implement every method marked TODO until main() prints All checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

// Count the number of bits set to 1 in x.
// Params: x - value to inspect.
// Return: number of 1-bits in the binary representation of x.
// Bit trick: x &= (x - 1) clears the lowest set bit each iteration, so the
//   loop runs once per set bit.
// Complexity: O(number of set bits).
int count_set_bits(unsigned int x) {
    throw std::logic_error("TODO: implement count_set_bits");
}

// Test whether x is a power of two (1, 2, 4, 8, ...).
// Params: x - value to test.
// Return: true iff exactly one bit is set.
// Bit trick: a positive power of two has a single set bit, so
//   x > 0 and (x & (x - 1)) == 0.
// Complexity: O(1).
bool is_power_of_two(unsigned int x) {
    throw std::logic_error("TODO: implement is_power_of_two");
}

// Find the value that appears exactly once when every other value appears
// twice.
// Params: a - vector in which all values but one occur an even number of
//   times (twice), and one value occurs once.
// Return: the value that appears only once.
// Bit trick: XOR is associative and commutative, and v ^ v == 0, so XOR-ing
//   every element cancels the paired values and leaves the unique one.
// Complexity: O(n).
int single_number(const std::vector<int>& a) {
    throw std::logic_error("TODO: implement single_number");
}

// Read the value of bit i in x.
// Params: x - source value; i - bit index (0 = least significant).
// Return: true if bit i is 1, false if it is 0.
// Bit trick: shift x right by i and mask the low bit: (x >> i) & 1u.
// Complexity: O(1).
bool get_bit(unsigned int x, int i) {
    throw std::logic_error("TODO: implement get_bit");
}

// Produce x with bit i forced to 1.
// Params: x - source value; i - bit index (0 = least significant).
// Return: x with bit i set; other bits unchanged.
// Bit trick: OR with a single-bit mask: x | (1u << i).
// Complexity: O(1).
unsigned int set_bit(unsigned int x, int i) {
    throw std::logic_error("TODO: implement set_bit");
}

// Produce x with bit i forced to 0.
// Params: x - source value; i - bit index (0 = least significant).
// Return: x with bit i cleared; other bits unchanged.
// Bit trick: AND with the inverse mask: x & ~(1u << i).
// Complexity: O(1).
unsigned int clear_bit(unsigned int x, int i) {
    throw std::logic_error("TODO: implement clear_bit");
}

// Produce x with bit i flipped.
// Params: x - source value; i - bit index (0 = least significant).
// Return: x with bit i toggled; other bits unchanged.
// Bit trick: XOR with a single-bit mask: x ^ (1u << i).
// Complexity: O(1).
unsigned int toggle_bit(unsigned int x, int i) {
    throw std::logic_error("TODO: implement toggle_bit");
}

// Sum the number of set bits across every integer in the range 0..n
// inclusive.
// Params: n - upper bound of the range (n >= 0).
// Return: total count of 1-bits in 0, 1, 2, ..., n.
// Bit trick: accumulate count_set_bits(v) for each v in [0, n]; treat each v
//   as unsigned when counting its bits.
// Complexity: O(n * bits per value).
int count_bits_up_to(int n) {
    throw std::logic_error("TODO: implement count_bits_up_to");
}

int main() {
    try {
        // population count
        assert(count_set_bits(0) == 0);
        assert(count_set_bits(7) == 3);
        assert(count_set_bits(255) == 8);

        // power-of-two test
        assert(is_power_of_two(1) == true);
        assert(is_power_of_two(16) == true);
        assert(is_power_of_two(0) == false);
        assert(is_power_of_two(6) == false);

        // single number via XOR
        assert(single_number({4, 1, 2, 1, 2}) == 4);
        assert(single_number({7}) == 7);

        // single-bit access
        assert(get_bit(0b1010u, 1) == true);
        assert(get_bit(0b1010u, 0) == false);
        assert(set_bit(0u, 3) == 8u);
        assert(clear_bit(0b1111u, 0) == 0b1110u);
        assert(toggle_bit(0b1010u, 2) == 0b1110u);

        // cumulative set bits over 0..5 -> 0,1,1,2,1,2 -> 7
        assert(count_bits_up_to(5) == 7);

        std::cout << "All checks passed" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        return 1;
    }
}
