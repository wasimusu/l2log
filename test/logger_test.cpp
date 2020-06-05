#include <bits/stdc++.h>
#include "gtest/gtest.h"
#include "../src/logger.h"

TEST(construction, c1) {

    // Construction for logging into file
    std::string filename = "testlog.csv";
    Logger logger(filename, false, true);

    EXPECT_EQ(logger.get_priority(), 0);

    // Construction for console logging
    Logger logger1;
    EXPECT_EQ(logger1.get_priority(), 0);

    // Construction for logging into file and console
    Logger logger2("testlog2.csv", true, true);
}


TEST(construction, bad_construction) {
    EXPECT_THROW(Logger logger("", false, false), std::invalid_argument);

}

TEST(priority, change_priority) {
    std::string filename = "testlog.csv";
    Logger logger(filename);

    EXPECT_EQ(logger.get_priority(), 0);

    logger.set_priority(PRIORITY::INFO);
    EXPECT_EQ(logger.get_priority(), static_cast<int>(PRIORITY::INFO));

    logger.set_priority(PRIORITY::CRITICAL);
    EXPECT_EQ(logger.get_priority(), static_cast<int>(PRIORITY::CRITICAL));

    logger.set_priority(PRIORITY::ERROR);
    EXPECT_EQ(logger.get_priority(), static_cast<int>(PRIORITY::ERROR));

    logger.set_priority(PRIORITY::DEBUG);
    EXPECT_EQ(logger.get_priority(), static_cast<int>(PRIORITY::DEBUG));

    logger.set_priority(PRIORITY::WARNING);
    EXPECT_EQ(logger.get_priority(), static_cast<int>(PRIORITY::WARNING));

    logger.set_priority(PRIORITY::NOTSET);
    EXPECT_EQ(logger.get_priority(), static_cast<int>(PRIORITY::NOTSET));
}

TEST(priority, should_not_log) {

}

TEST(message, variadic_message) {
    // This is not to be used this way. Just for testing purpose.

    Logger logger;
    std::string r1 = "hello", r2 = "how", r3 = "are";
    auto result = logger.build_message(r1, r2, r3);
    EXPECT_EQ(result, "hello, how, are");

    auto result2 = logger.build_message(r1);
    EXPECT_EQ(result2, r1);
}
