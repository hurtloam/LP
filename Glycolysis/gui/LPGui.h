#pragma once
#include "imgui.h"
#include "../inc/ResObj.h"
#include "../inc/ViewIf.h"
#include "../inc/LPObject.h"
#include "../inc/StaticObj.h"
#include <glm/detail/type_vec3.hpp>

#include "../stage/inc/StageIf.h"
class LPGui {
public:

  LPGui(ViewIf* view, StageIf* stage, ResObj* resObj);
  virtual
  ~LPGui () = default;

  bool statusOfObjectWindow = false;
  bool statusOfStatusWindow = false;
  bool statusOfChangeLight = false;
  bool statusOfCreateWindow = false;
  bool statusOfCreateTextDialog = false;
  bool statusOfCreateMoleculesDialog = false;
  bool statusOflistResources = false;
  bool statusOfCreateMoleculesWindow = false;
  bool statusOfActorListWindow = false;
  bool showTextureListWindow = false;
  bool statusOfConfigRayTrace = false;

  bool statusOfShowGrid = false;
  bool statusOfMoveObjEnabled = false;
  bool statusOfAdjustToGridEnabled = false;
  bool statusOfDebugBullet = false;
  bool statusOfDetachFromFPS = false;
  bool statusOfDeactivatingMovements = false;

  void
  runGui(bool show_test_window, bool show_another_window, bool show_object_window, ImVec4 clear_color, ImGuiIO io);

  void
  ShowActiveObjects();

  // Demonstrate creating a fullscreen menu bar and populating it.
  void MainMenuBar();

  void ShowExampleMenuFile();
  bool getStatusOfObjectWindow();
  bool getStatusOfStatusWindow();

  // Implemented in Stage

  // Implemented in LearningPlatform
  virtual void OnGuiMainMenuFileQuit() = 0;
  virtual void OnGuiWindowShowObject(bool*) = 0;
  virtual void OnGuiWindowShowStatus(bool*) = 0;
  virtual void OnGuiMainMenuShowGrid(bool* statusOfShowGrid) = 0;
  virtual void OnGuiMainMenuMoveObjEnabled(bool* statusOfMoveObjEnabled) = 0;
  virtual void OnGuiMainMenuAdjustToGridEnabled(bool* statusOfAdjustToGridEnabled) = 0;
  virtual void OnGuigetRegulationQuestionState(bool isRegulationQuestionStateActive) = 0;

  virtual bool OnGuigetRegulationQuestion1Active() = 0;
  virtual bool OnGuigetRegulationQuestion1ActiveAndSuccessful() = 0;
  virtual bool OnGuigetRegulationQuestion2Active() = 0;
  virtual bool OnGuigetRegulationQuestion2ActiveAndSuccessful() = 0;
  virtual bool OnGuigetRegulationQuestion3Active() = 0;
  virtual bool OnGuigetRegulationQuestion3ActiveAndSuccessful() = 0;

  virtual void OnGuiMainMenuDebugBullet(bool* statusOfDebugBullet) = 0;
  virtual void OnGuiMainMenuDetachFromFPS(bool* statusOfDetachFromFPS) = 0;
  virtual void OnGuiWindowShowChangeLight(bool*) = 0;
//  virtual void OnGuiWindowActorList(bool*) = 0;
  virtual void OnGuiWindowCreateObjectsWindow(bool*) = 0;
  virtual void OnGuiMainMenuRestart() = 0;
  void ShowExampleAppFixedOverlay();
  void ShowExampleAppFixedOverlay2();
  void ShowCurrentObject();
  void ShowQuestionWindow();
  void ShowBackWindow1();
  void ShowBackWindow2();
  void ShowBackWindow3();

  void ActorListWindow();
  void TextureListWindow();

  void callBrowser(std::string wikiSearch);
  void Winning();

  void updateGuiOnCurrentObjData(LPObject* obj);
  void updateGuiOnProcessCompleted(int progress);
  void updateGuiOnFPersonData(LPObject* obj);

  void ProcessCompleted ();

  void Test2(bool* p_open);

  void setView(ViewIf* v)
  {
    this->view = v;
  }
  void setStage(StageIf* s)
  {
    this->stage = s;
  }

  virtual void
  OnGuiMainMenuDeactivatingMovements(bool *statusOfDeactivatingMovements) = 0;

  virtual void
  OnGuiWindowMenuConfigRayTrace(bool*) = 0;

  void setResObj(ResObj* r)
  {
    this->resObj = r;
  }

  void
  GameOver();

  void createWindowDialog();
  void listResourcesDialog();
  void createTextDialog();
  void createMolecules();
  int getProcessCompleted() const;

private:
  ViewIf* view;
  StageIf* stage;
  ResObj* resObj;
  LPObject* currentObject;
  LPObject* fPerson;
  bool isShowStatusWindow = false;
  float lightPower;
  glm::vec3 gOrientation = glm::vec3(0.0f, 0.0f, 0.0f);

  float vAngle;
  float yAngle;

  float xKatet;
  float zKatet;

  glm::vec3 position;

  int processCompleted;

  bool regulationQuestion1State = false;
  bool regulationQuestion2State = false;
  bool regulationQuestion3State = false;

  };

