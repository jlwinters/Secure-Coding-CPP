// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// Test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Confirm that the size of the collection is 0 when empty
    ASSERT_EQ(collection->size(), 0);
    // Add 1 entry to the collection
    add_entries(1);
    // Ensure that the collection is no longer empty after adding an entry
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is now 1
    ASSERT_EQ(collection->size(), 1);
}

// Test to verify adding five values to the collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Confirm that the size of the collection is 0 when empty
    ASSERT_EQ(collection->size(), 0);
    // Add 5 entries to the collection
    add_entries(5);
    // Ensure that the collection is no longer empty after adding entries
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is now 5
    ASSERT_EQ(collection->size(), 5);
}

// Test to verify that max size is greater than or equal to size for 0, 1, 5, and 10 entries
TEST_F(CollectionTest, IsMaxSizeGreaterOrEqualSize)
{
    // Check for 0 entries
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Confirm that the size of the collection is 0 when empty
    ASSERT_EQ(collection->size(), 0);
    // Ensure that the max size is greater than or equal to the size
    ASSERT_GE(collection->max_size(), collection->size());

    // Check for 1 entry
    add_entries(1);
    // Ensure that the collection is not empty after adding an entry
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
    // Ensure that the max size is greater than or equal to the size
    ASSERT_GE(collection->max_size(), collection->size());

    // Check for 5 entries
    add_entries(4);
    // Ensure that the collection is not empty after adding entries
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Ensure that the max size is greater than or equal to the size
    ASSERT_GE(collection->max_size(), collection->size());

    // Check for 10 entries
    add_entries(5);
    // Ensure that the collection is not empty after adding entries
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 10
    ASSERT_EQ(collection->size(), 10);
    // Ensure that the max size is greater than or equal to the size
    ASSERT_GE(collection->max_size(), collection->size());
}

// Test to verify that capacity is greater than or equal to size for 0, 1, 5, and 10 entries
TEST_F(CollectionTest, IsCapacityGreaterOrEqualSize)
{
    // Check for 0 entries
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Validate that the size of the collection is 0 when empty
    ASSERT_EQ(collection->size(), 0);
    // Ensure that the capacity is greater than or equal to the size
    ASSERT_GE(collection->capacity(), collection->size());

    // Check for 1 entry
    add_entries(1);
    // Verify that the collection is not empty after adding an entry
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
    // Ensure that the capacity is greater than or equal to the size
    ASSERT_GE(collection->capacity(), collection->size());

    // Check for 5 entries
    add_entries(4);
    // Verify that the collection is not empty after adding entries
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Ensure that the capacity is greater than or equal to the size
    ASSERT_GE(collection->capacity(), collection->size());

    // Check for 10 entries
    add_entries(5);
    // Verify that the collection is not empty after adding entries
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 10
    ASSERT_EQ(collection->size(), 10);
    // Ensure that the capacity is greater than or equal to the size
    ASSERT_GE(collection->capacity(), collection->size());
}

// Test to verify that resizing increases the collection
TEST_F(CollectionTest, CanResizeIncreaseCollection)
{
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Validate that the size of the collection is 0 when empty
    ASSERT_EQ(collection->size(), 0);
    // Add 5 entries
    collection->resize(5);
    // Ensure that the collection is not empty after resizing
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
}

// Test to verify that resizing decreases the collection
TEST_F(CollectionTest, CanResizeDecreaseCollection)
{
    // Add 5 entries
    add_entries(5);
    // Verify that the collection is not empty
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Resize to 1
    collection->resize(1);
    // Ensure that the collection is not empty after resizing
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
}

// Test to verify that resizing decreases the collection to zero
TEST_F(CollectionTest, CanResizeDecreaseCollectionToZero)
{
    // Add 5 entries
    add_entries(5);
    // Verify that the collection is not empty
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Resize to 0
    collection->resize(0);
    // Ensure that the collection is empty after resizing
    ASSERT_TRUE(collection->empty());
    // Validate that the size of the collection is 0
    ASSERT_EQ(collection->size(), 0);
}

// Test to verify that clear erases the collection
TEST_F(CollectionTest, CanClearCollection)
{
    // Add 5 entries
    add_entries(5);
    // Verify that the collection is not empty
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Call the clear function
    collection->clear();
    // Check if the collection is empty
    ASSERT_TRUE(collection->empty());
    // Check that the size of the collection is 0 after clearing
    ASSERT_EQ(collection->size(), 0);
}

// Test to verify that erase(begin, end) erases the collection
TEST_F(CollectionTest, CanEraseClearCollection)
{
    // Add 5 entries
    add_entries(5);
    // Verify that the collection is not empty
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Call the erase function
    collection->erase(collection->begin(), collection->end());
    // Check if the collection is empty
    ASSERT_TRUE(collection->empty());
    // Check that the size of the collection is 0 after erasing
    ASSERT_EQ(collection->size(), 0);
}

// Test to verify that reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CanReserveIncreaseCapacity)
{
    // Add 5 entries
    add_entries(1);
    // Verify that the collection is not empty
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
    // Get the initial capacity
    int initialCapacity = collection->capacity();
    // Call the reserve function
    collection->reserve(6);
    // Check the capacity after reserving
    ASSERT_EQ(collection->capacity(), 6);
    // Check that the size remains the same
    ASSERT_EQ(collection->size(), 1);
}

// Test to verify that the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, CanThrowAtOutOfRange)
{
    // Add 5 entries
    add_entries(1);
    // Verify that the collection is not empty
    ASSERT_FALSE(collection->empty());
    // Validate that the size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
    // Check if the collection throws std::out_of_range
    ASSERT_THROW(collection->at(2), std::out_of_range);
}

// Positive Test: Verify that the collection contains a specific value after adding it
TEST_F(CollectionTest, ContainsSpecificValue)
{
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Add a specific value to the collection
    collection->push_back(42);
    // Check if the collection contains the specific value
    ASSERT_TRUE(std::find(collection->begin(), collection->end(), 42) != collection->end());
}

// Negative Test: Verify that the collection does not contain a specific value that was not added
TEST_F(CollectionTest, DoesNotContainMissingValue)
{
    // Verify that the collection is initially empty
    ASSERT_TRUE(collection->empty());
    // Add a different value to the collection
    collection->push_back(123);
    // Check if the collection contains a missing value
    ASSERT_FALSE(std::find(collection->begin(), collection->end(), 42) != collection->end());
}