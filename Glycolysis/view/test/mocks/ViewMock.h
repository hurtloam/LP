/*
 * StageMock.h
 *
 *  Created on: Apr 1, 2018
 *      Author: peter
 */

#ifndef VIEW_TEST_MOCKS_VIEWMOCK_H_
#define VIEW_TEST_MOCKS_VIEWMOCK_H_

#include <gmock/gmock.h>
#include "../../../inc/ViewIf.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ViewMock : public ViewIf {
  public:
    MOCK_CONST_METHOD0(getSpeed, float(void));
    MOCK_METHOD1(setSpeed, void(float));
    MOCK_CONST_METHOD0(getViewMatrix, glm::mat4());
    MOCK_METHOD1(setViewMatrix, void(const glm::mat4& viewMatrix));
    MOCK_METHOD0(setDefault, void());
    MOCK_METHOD8(computeMatricesFromInputs, void(SDL_Window *window,
                                                 int xpos,
                                                 int ypos,
                                                 int relX,
                                                 int relY,
                                                 bool Left,
                                                 bool Right,
                                                 bool Middle));
    MOCK_CONST_METHOD8(ScreenPosToWorldRay, void(
      int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
      int screenWidth, int screenHeight,  // Window size, in pixels
      glm::mat4 ViewMatrix,               // Camera position and orientation
      glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
      glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
      glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
    ));
    MOCK_CONST_METHOD1(getKeyStates, bool(const int v));
    MOCK_METHOD1(setFoV, void(float fov));
    MOCK_CONST_METHOD0(getFoV, float());
    MOCK_CONST_METHOD0(getInitialFoV, float());
    MOCK_METHOD1(setInitialFoV, void(float initialFoV));
    MOCK_CONST_METHOD0(getPosition, glm::vec3());
    MOCK_METHOD1(setPosition, void(const glm::vec3& position));
    MOCK_CONST_METHOD0(getHorizontalAngle, float());
    MOCK_METHOD1(setHorizontalAngle, void(float));

    MOCK_CONST_METHOD0(getVerticalAngle, float());
    MOCK_METHOD1(setVerticalAngle, void(float));

    MOCK_METHOD1(move, void(int));
    MOCK_METHOD1(move, void(glm::vec3));
    MOCK_METHOD1(updateKeyStates, void(int));
    MOCK_CONST_METHOD0(getProjectionMatrix, glm::mat4());
    MOCK_METHOD0(printPos, void());

    MOCK_METHOD1(setProjectionMatrix, void(const glm::mat4&));
    MOCK_METHOD1(setAspectRatio, void(float aspectRatio));
    MOCK_METHOD1(setProjectionMatrix2, void(const glm::mat4&));

    MOCK_CONST_METHOD0(getMovement, int ());
    MOCK_CONST_METHOD0(isRotationAllowed, bool());

    MOCK_METHOD1(setRotationAllowed, void(bool));
    MOCK_METHOD2(setScreen, void(int, int));

    MOCK_CONST_METHOD0(getScreenHeight, int());
    MOCK_CONST_METHOD0(getScreenWidth, int());

    MOCK_CONST_METHOD3(warpMouseInWindow, void(SDL_Window*, const int, const int));

    MOCK_CONST_METHOD0(getInitialVerticalAngle, float());
    MOCK_CONST_METHOD0(getIntitialHorizontalAngle, float());

  MOCK_METHOD0(getObjPlacementInFrontOfCamera, glm::vec3());
  MOCK_CONST_METHOD0(getDirection, const glm::vec3&());
  MOCK_CONST_METHOD0(getRight, const glm::vec3&());
};



#endif /* VIEW_TEST_MOCKS_VIEWMOCK_H_ */
