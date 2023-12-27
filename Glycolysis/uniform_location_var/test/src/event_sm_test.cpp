/*
 * event_sm_test.cpp
 *
 *  Created on: Dec 27, 2018
 *      Author: peter
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../../test/mocks/LearningPlatformMock.h"
#include "../../../uniform_location_var/inc/InitSM.h"
#include "../../../uniform_location_var/inc/ObjSelectedSM.h"

using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;
using ::testing::_;

class EventSMTest : public ::testing::Test {

protected:
	EventSM* initSM;
	EventSM* objSelectedSM;

	LearningPlatformMock learningPlatformMock;


	EventSMTest() {
		initSM = InitSM::Instance();
		objSelectedSM = ObjSelectedSM::Instance();
	}

	virtual ~EventSMTest() {
		delete initSM;
		delete objSelectedSM;
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(EventSMTest, changeState_initSM) {
	EXPECT_CALL(learningPlatformMock, changeState(objSelectedSM));
	initSM->onLeftButtonDown(&learningPlatformMock);

  std::cout << "new state: " << initSM->getName() << std::endl;
}

//TEST_F(EventSMTest, changeState_objSelectedSM) {
//	int relX = 10;
//	int relY = 20;
//	LPObject* obj = nullptr;
////	EXPECT_CALL(learningPlatformMock, changeState(moveObjInXYPlaneSM));
//  objSelectedSM->onMouseMove(&learningPlatformMock, relX, relY, obj);
//}


//TEST_F(EventSMTest, changeState_moveObjInXYPlaneSM) {
//	EXPECT_CALL(learningPlatformMock, changeState(initSM));
//	moveObjInXYPlaneSM->onLeftButtonUp(&learningPlatformMock);
//}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
