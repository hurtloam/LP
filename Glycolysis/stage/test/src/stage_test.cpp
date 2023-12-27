/*
 * command_test.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: peter
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../../stage/test/mocks/StageMock.h"
#include "../../../view/test/mocks/ViewMock.h"

using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;

class StageTest: public ::testing::Test {

protected:

  StageTest()
  {
  }

  virtual ~StageTest()
  {

  }

  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(StageTest, AlterCameraSpeed)
{

}

TEST_F(StageTest, AlterCameraSpeed_2)
{

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
