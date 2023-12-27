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
#include "../../inc/AlterCameraSpeedCmd.h"
#include "../../inc/AlterGridCmd.h"
#include "../../inc/PrintCameraPositionCmd.h"
#include "../../../stage/test/mocks/StageMock.h"
#include "../../../view/test/mocks/ViewMock.h"

using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;

class CommandTest: public ::testing::Test {

protected:

  CommandTest()
  {
  }

  virtual ~CommandTest()
  {

  }

  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
  }
};

TEST_F(CommandTest, AlterCameraSpeed)
{
  ViewMock viewMock;
  AlterCameraSpeedCmd speed(viewMock);

  EXPECT_CALL(viewMock, getSpeed()).WillOnce(Return(0.2));
  EXPECT_CALL(viewMock, setSpeed(0.01)).Times(1);
  speed.execute();
}

TEST_F(CommandTest, AlterCameraSpeed_2)
{
  ViewMock viewMock;
  AlterCameraSpeedCmd speed(viewMock);

  EXPECT_CALL(viewMock, getSpeed()).WillOnce(Return(0.015));
  EXPECT_CALL(viewMock, setSpeed(0.2)).Times(1);
  speed.execute();
}

TEST_F(CommandTest, AlterGrid)
{
  StageMock stageMock;
  AlterGridCmd alterGridCommand(stageMock);
  glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f);
  EXPECT_CALL(stageMock, createCoordinateLines(pos, 20000)).Times(1);
  alterGridCommand.execute();
}

TEST_F(CommandTest, PrintCameraPosition)
{
  ViewMock viewMock;
  PrintCameraPositionCmd printCameraPositionCmd(viewMock);
  glm::mat4 mat = glm::mat4(1.0,0.0f,0.0f,0.0f,1.0,0.0f,0.0f,0.0f,1.0,0.0f,0.0f,0.0f,1.0,0.0f,0.0f,0.0f);
  EXPECT_CALL(viewMock, getViewMatrix()).WillRepeatedly(Return(mat));
  printCameraPositionCmd.execute();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
