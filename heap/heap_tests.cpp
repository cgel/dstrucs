#include "gtest/gtest.h"
#include "heap.h"

double root(double val) { return 1.0; }

TEST(test_heap, heap) {
  Heap<int> h;
  h.insert(7);
  h.insert(2);
  EXPECT_EQ(7, h.top());
  h.pop();
  EXPECT_EQ(2, h.top());
  h.print();
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
