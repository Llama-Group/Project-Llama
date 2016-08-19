
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <gtest/gtest.h>
#include <Utility/DataGenerator.h>

#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

using llama::DataGenerator;

TEST(DataGeneratorCorrectnessTest, GenerateRandomDataBool) {
    vector<bool> randomBool;

    DataGenerator::generateRandomData(&randomBool, 100000);

    int trueCount = 0;
    for (const bool &b : randomBool) {
        trueCount += static_cast<int>(b);
    }
    double trueRatio = trueCount * 0.00001;

    EXPECT_NEAR(0.5, trueRatio, 0.001) << "Boolean not distributed equally.";
}

//
// DataGenerator Exception Tests.
//

TEST(DataGeneratorExceptionTest, GenerateSingleDatumMinimumInteger) {
    int minimumInt = std::numeric_limits<int>::min();

    EXPECT_THROW(DataGenerator::generateSingleDatum(minimumInt, LT), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum(minimumInt, LT);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("The given value is the minimum of the specified type."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }

    DataGenerator::generateSingleDatum(minimumInt, EQ);
    DataGenerator::generateSingleDatum(minimumInt, NE);
    DataGenerator::generateSingleDatum(minimumInt, LE);
    DataGenerator::generateSingleDatum(minimumInt, GE);
    DataGenerator::generateSingleDatum(minimumInt, GT);
    DataGenerator::generateSingleDatum(minimumInt, RD);
}

TEST(DataGeneratorExceptionTest, GenerateSingleDatumMaximumInteger) {
    int maximumInt = std::numeric_limits<int>::max();

    EXPECT_THROW(DataGenerator::generateSingleDatum(maximumInt, GT), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum(maximumInt, GT);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("The given value is the maximum of the specified type."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }

    DataGenerator::generateSingleDatum(maximumInt, EQ);
    DataGenerator::generateSingleDatum(maximumInt, NE);
    DataGenerator::generateSingleDatum(maximumInt, LE);
    DataGenerator::generateSingleDatum(maximumInt, LT);
    DataGenerator::generateSingleDatum(maximumInt, GE);
    DataGenerator::generateSingleDatum(maximumInt, RD);
}

TEST(DataGeneratorExceptionTest, GenerateSingleDatumMinimumDouble) {
    double minimumDouble = std::numeric_limits<double>::min();

    EXPECT_THROW(DataGenerator::generateSingleDatum(minimumDouble, LT), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum(minimumDouble, LT);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("The given value is the minimum of the specified type."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }

    DataGenerator::generateSingleDatum(minimumDouble, EQ);
    DataGenerator::generateSingleDatum(minimumDouble, NE);
    DataGenerator::generateSingleDatum(minimumDouble, LE);
    DataGenerator::generateSingleDatum(minimumDouble, GE);
    DataGenerator::generateSingleDatum(minimumDouble, GT);
    DataGenerator::generateSingleDatum(minimumDouble, RD);
}

TEST(DataGeneratorExceptionTest, GenerateSingleDatumMaximumDouble) {
    double maximumDouble = std::numeric_limits<double>::max();

    EXPECT_THROW(DataGenerator::generateSingleDatum(maximumDouble, GT), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum(maximumDouble, GT);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("The given value is the maximum of the specified type."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }

    DataGenerator::generateSingleDatum(maximumDouble, EQ);
    DataGenerator::generateSingleDatum(maximumDouble, NE);
    DataGenerator::generateSingleDatum(maximumDouble, LE);
    DataGenerator::generateSingleDatum(maximumDouble, LT);
    DataGenerator::generateSingleDatum(maximumDouble, GE);
    DataGenerator::generateSingleDatum(maximumDouble, RD);
}

TEST(DataGeneratorExceptionTest, GenerateSingleDatumUnrecognisedCase) {
    // Never do this cast in actual code.
    Cases unrecognisedMode = static_cast<Cases>(19950207);
    EXPECT_THROW(DataGenerator::generateSingleDatum<int>(int(), unrecognisedMode), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum<int>(int(), unrecognisedMode);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Unrecognised arguement."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
    EXPECT_THROW(DataGenerator::generateSingleDatum<double>(double(), unrecognisedMode), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum<double>(double(), unrecognisedMode);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Unrecognised arguement."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
    EXPECT_THROW(DataGenerator::generateSingleDatum("", unrecognisedMode), std::invalid_argument);
    try {
        DataGenerator::generateSingleDatum("", unrecognisedMode);
    } catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Unrecognised arguement."));
    } catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

// TEST(DataGeneratorException, GenerateSingleDatumNullPointer) {
//
// }
