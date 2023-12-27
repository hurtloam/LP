#include "LPGui.h"
#include "../inc/ResObj.h"
#include "imgui.h"
#include <string.h>
//#include "LPGuiLearningPlatform.h"
//void LPGui::ShowExampleMenuFile()
//{
//  ShowExampleMenuFile();
//}


LPGui::LPGui(ViewIf* view, StageIf* stage, ResObj* resObj) :
    view(view), stage(stage), resObj(resObj), currentObject(nullptr)
{
 fPerson = nullptr;
// following set to true in Glycolysis
// statusOfCreateMoleculesDialog = true;
 statusOfDetachFromFPS = false;
 statusOfMoveObjEnabled = false;


 }

void LPGui::ShowActiveObjects()
{
  //  ShowActiveObjects(info1,info2, info3,
  //                    sdlInfo1, sdlInfo2,
  //                    sdlInfo3, mInfo1,
  //                    mInfo2, mInfo3);

  static bool no_titlebar = false;
  static bool no_border = true;
  static bool no_resize = false;
  static bool no_move = false;
  static bool no_scrollbar = false;
  static bool no_collapse = false;
  static bool no_menu = false;


  // Demonstrate the various window flags. Typically you would just use the default.
  ImGuiWindowFlags window_flags = 0;
  if (no_titlebar)
    window_flags |= ImGuiWindowFlags_NoTitleBar;
  if (!no_border)
    window_flags |= ImGuiWindowFlags_ShowBorders;
  if (no_resize)
    window_flags |= ImGuiWindowFlags_NoResize;
  if (no_move)
    window_flags |= ImGuiWindowFlags_NoMove;
  if (no_scrollbar)
    window_flags |= ImGuiWindowFlags_NoScrollbar;
  if (no_collapse)
    window_flags |= ImGuiWindowFlags_NoCollapse;
  if (!no_menu)
    window_flags |= ImGuiWindowFlags_MenuBar;


  ImGui::SetNextWindowSize (ImVec2 (500, 100), ImGuiSetCond_FirstUseEver);
  ImGui::Begin ("Objects");
  //    ImGui::SetWindowFontScale(2.0);
  // PEB BONES
//  currentObject = stage->getObject(14001);
  if (currentObject != nullptr)
    {
    ImGui::Text ("Selected object: id=%d, obj type= %d, name=%s, ", currentObject->getId (), currentObject->getObjType (), currentObject->getMoleculeInfo1 ().c_str ());
    ImGui::Text ("Trans(%f,%f,%f)", currentObject->getTrans ().x, currentObject->getTrans ().y, currentObject->getTrans ().z);
    ImGui::TextWrapped (currentObject->getMoleculeInfo1 ().c_str ());
    ImGui::TextWrapped (currentObject->getMoleculeInfo2 ().c_str ());
    ImGui::TextWrapped (currentObject->getMoleculeInfo3 ().c_str ());

    ImGui::Text ("Texture Information");
    ImGui::Bullet ();
    ImGui::Text ("Texture Id: %d", currentObject->getTexture());

    ImGui::Text ("Bullet Physics parameters");
    ImGui::Bullet ();
    ImGui::Text ("ActivationState: %d", currentObject->getRigidBody ()->getActivationState ());
    ImGui::Bullet ();
    ImGui::Text ("CollisionFlags: %d", currentObject->getRigidBody ()->getCollisionFlags ());
    ImGui::Bullet ();
    ImGui::Text ("HitFraction: %d", currentObject->getRigidBody ()->getHitFraction ());
    ImGui::Bullet ();
    ImGui::Text ("Margin: %d", currentObject->getRigidBody ()->getCollisionShape ()->getMargin ());
    ImGui::Bullet ();
    ImGui::Text ("CenterOfMassPosition: (%f, %f, %f)", currentObject->getRigidBody ()->getCenterOfMassPosition ().getX (), currentObject->getRigidBody ()->getCenterOfMassPosition ().getY (),
                 currentObject->getRigidBody ()->getCenterOfMassPosition ().getZ ());
    ImGui::Bullet ();
    ImGui::Text("CenterOfMassTransform: (%f, %f, %f)", currentObject->getRigidBody()->getCenterOfMassTransform().getOrigin().getX(),
                 currentObject->getRigidBody ()->getCenterOfMassTransform ().getOrigin ().getY (), currentObject->getRigidBody ()->getCenterOfMassTransform ().getOrigin ().getZ ());

    ImGui::Text("Shader parameters");
    ImGui::Bullet();
    ImGui::Text("useColor: %f", ((StaticObj*) currentObject)->getUseColor());
    ImGui::Bullet();
    ImGui::Text("objColor: (%f, %f, %f)", ((StaticObj*) currentObject)->getObjColor().x, ((StaticObj*) currentObject)->getObjColor().y, ((StaticObj*) currentObject)->getObjColor().z);
    ImGui::Bullet();
    ImGui::Text("useColorID: %d", ((StaticObj*) currentObject)->getUseColorId());
    ImGui::Bullet();
    ImGui::Text("colorID: %d", ((StaticObj*) currentObject)->getColorId());
    ImGui::Bullet();
    ImGui::Text("LPUniform colorID: %d", ((StaticObj*) currentObject)->getLpUniform().colorID);
    ImGui::Bullet();
    ImGui::Text("LPUniform LightID: %d", ((StaticObj*) currentObject)->getLpUniform().LightID);
    }
  else
    {
      ImGui::Text ("");
      ImGui::Text ("");
      ImGui::Text ("");
    }

  ImGui::End ();
}

void LPGui::ActorListWindow()
{
 static bool no_titlebar = false;
 static bool no_border = true;
 static bool no_resize = false;
 static bool no_move = false;
 static bool no_scrollbar = false;
 static bool no_collapse = false;
 static bool no_menu = false;


 // Demonstrate the various window flags. Typically you would just use the default.
 ImGuiWindowFlags window_flags = 0;
 if (no_titlebar)
  window_flags |= ImGuiWindowFlags_NoTitleBar;
 if (!no_border)
  window_flags |= ImGuiWindowFlags_ShowBorders;
 if (no_resize)
  window_flags |= ImGuiWindowFlags_NoResize;
 if (no_move)
  window_flags |= ImGuiWindowFlags_NoMove;
 if (no_scrollbar)
  window_flags |= ImGuiWindowFlags_NoScrollbar;
 if (no_collapse)
  window_flags |= ImGuiWindowFlags_NoCollapse;
 if (!no_menu)
  window_flags |= ImGuiWindowFlags_MenuBar;


 ImGui::SetNextWindowSize (ImVec2 (500, 100), ImGuiSetCond_FirstUseEver);
 ImGui::Begin ("ActorList");
 if (stage!= nullptr)
  {
   for (LPObject* obj : stage->getActorList()) {
     ImGui::Bullet ();
     ImGui::Text ("id=%d, obj type=%d, name=%s, textureId=%d", obj->getId (), obj->getObjType (), obj->getMoleculeInfo1 ().c_str(), obj->getTexture());

   }
    for (LPObject* text_obj : stage->getActorTextList()) {
      ImGui::Bullet();
      ImGui::Text("id=%d, obj type=%d, name=%s, textureId=%d", text_obj->getId(), text_obj->getObjType(), text_obj->getMoleculeInfo1().c_str(), text_obj->getTexture());

    }
  }
 else
  {
  }
 ImGui::End ();
}

void LPGui::TextureListWindow()
{
 static bool no_titlebar = false;
 static bool no_border = true;
 static bool no_resize = false;
 static bool no_move = false;
 static bool no_scrollbar = false;
 static bool no_collapse = false;
 static bool no_menu = false;


 // Demonstrate the various window flags. Typically you would just use the default.
 ImGuiWindowFlags window_flags = 0;
 if (no_titlebar)
  window_flags |= ImGuiWindowFlags_NoTitleBar;
 if (!no_border)
  window_flags |= ImGuiWindowFlags_ShowBorders;
 if (no_resize)
  window_flags |= ImGuiWindowFlags_NoResize;
 if (no_move)
  window_flags |= ImGuiWindowFlags_NoMove;
 if (no_scrollbar)
  window_flags |= ImGuiWindowFlags_NoScrollbar;
 if (no_collapse)
  window_flags |= ImGuiWindowFlags_NoCollapse;
 if (!no_menu)
  window_flags |= ImGuiWindowFlags_MenuBar;


 ImGui::SetNextWindowSize (ImVec2 (500, 100), ImGuiSetCond_FirstUseEver);
 ImGui::Begin ("TextureList");
 if (stage!= nullptr)
  {
   for (auto texture : stage->getTextureList()) {
     ImGui::Bullet ();
     ImGui::Text ("id=%d, textureId= %d", texture.first, texture.second);
   }
  }
 else
  {
  }
 ImGui::End ();
}

// Demonstrate creating a fullscreen menu bar and populating it.
void LPGui::MainMenuBar()
{
  //  MainMenuBar();



  if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
        {
          ShowExampleMenuFile();
          ImGui::EndMenu();
        }
//      if (ImGui::BeginMenu("Edit"))
//        {
//          if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
//          if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
//          ImGui::Separator();
//          if (ImGui::MenuItem("Cut", "CTRL+X")) {}
//          if (ImGui::MenuItem("Copy", "CTRL+C")) {}
//          if (ImGui::MenuItem("Paste", "CTRL+V")) {}
//          ImGui::EndMenu();
//        }
      if (ImGui::BeginMenu("Show"))
        {
          if (ImGui::MenuItem ("Show selected Object Information", NULL,
                               statusOfObjectWindow))
            {
              OnGuiWindowShowObject (&statusOfObjectWindow);
            }
          if (ImGui::MenuItem ("Show Status window", NULL,
                               statusOfStatusWindow))
            {
              isShowStatusWindow ^= 1;
              OnGuiWindowShowObject (&statusOfStatusWindow);
            }

      if (ImGui::MenuItem("Show grid", NULL, statusOfShowGrid))
            {
        OnGuiMainMenuShowGrid(&statusOfShowGrid);
            }
          ImGui::EndMenu ();
        }
      if (ImGui::BeginMenu ("Create"))
       {
        if (ImGui::MenuItem ("Create Objects", NULL, statusOfCreateWindow))
         {
          OnGuiWindowCreateObjectsWindow (&statusOfCreateWindow);
         }
        if (ImGui::MenuItem ("Create Molecules", NULL, statusOfCreateMoleculesWindow))
         {
          if (statusOfCreateMoleculesWindow == true) {
            statusOfCreateMoleculesWindow = false;
          } else {
            statusOfCreateMoleculesWindow = true;
          }
         }
      if (ImGui::MenuItem("Create TextMolecules", NULL, statusOfCreateTextDialog)) {
        if (statusOfCreateTextDialog == true) {
          statusOfCreateTextDialog = false;
        }
        else {
          statusOfCreateTextDialog = true;
        }
      }

      if (ImGui::MenuItem("Create TextMolecules2", NULL, statusOfCreateMoleculesDialog)) {
        if (statusOfCreateMoleculesDialog == true) {
          statusOfCreateMoleculesDialog = false;
        }
        else {
          statusOfCreateMoleculesDialog = true;
        }
      }

        ImGui::EndMenu ();
       }

//    if (ImGui::BeginMenu("Resources")) {
//      if (ImGui::MenuItem("list resources", NULL, statusOflistResources)) {
//        OnGuiMainMenuDetachFromFPS(&statusOflistResources);
//      }
//      ImGui::EndMenu();
//    }

    if (ImGui::BeginMenu ("View"))
    {
      if (ImGui::MenuItem("detach from FPS", NULL, statusOfDetachFromFPS))
      {
        OnGuiMainMenuDetachFromFPS(&statusOfDetachFromFPS);
      }
      ImGui::EndMenu ();
    }

    if (ImGui::BeginMenu ("Edit"))
    {
      if (ImGui::MenuItem("Deactivate movements", NULL,
          statusOfDeactivatingMovements))
      {
        OnGuiMainMenuDeactivatingMovements(&statusOfDeactivatingMovements);
      }
      if (ImGui::MenuItem ("Configure Ray Tracing", NULL, statusOfConfigRayTrace))
      {
        OnGuiWindowMenuConfigRayTrace (&statusOfConfigRayTrace);
      }
      if (ImGui::MenuItem("Debug Bullet", NULL, statusOfDebugBullet))
      {
        OnGuiMainMenuDebugBullet(&statusOfDebugBullet);
      }

      if (ImGui::MenuItem("Enable move Objects with mouse", NULL,
          statusOfMoveObjEnabled))
      {
        OnGuiMainMenuMoveObjEnabled(&statusOfMoveObjEnabled);
      }

      if (ImGui::MenuItem("Adjust Objects to grid", NULL,
          statusOfAdjustToGridEnabled))
      {
        OnGuiMainMenuAdjustToGridEnabled(&statusOfAdjustToGridEnabled);
      }

      ImGui::EndMenu ();
    }
      if (ImGui::BeginMenu("Light"))
        {
          if (ImGui::MenuItem ("Change light parameters", NULL,
                               statusOfChangeLight))
            {
              OnGuiWindowShowChangeLight (&statusOfChangeLight);
            }
          ImGui::EndMenu ();
        }


      if (ImGui::BeginMenu ("ActorList"))
       {
        if (ImGui::MenuItem ("List all objects", NULL, statusOfActorListWindow))
         {
          if (statusOfActorListWindow == true) {
            statusOfActorListWindow = false;
          } else {
            statusOfActorListWindow = true;
          }
         }
        ImGui::EndMenu ();
       }

      if (ImGui::BeginMenu ("TextureList"))
       {
        if (ImGui::MenuItem ("List all textures", NULL, showTextureListWindow))
         {
          if (showTextureListWindow == true) {
            showTextureListWindow = false;
          } else {
            showTextureListWindow = true;
          }
         }
        ImGui::EndMenu ();
       }

      ImGui::EndMainMenuBar();
    }
}

void LPGui::ShowExampleMenuFile()
{
  if (ImGui::MenuItem ("Restart"))
    {
      OnGuiMainMenuRestart ();
    }
  if (ImGui::MenuItem ("Save", "Ctrl+S"))
    {
    }
  if (ImGui::MenuItem ("Save As.."))
    {
    }
  ImGui::Separator ();
  if (ImGui::BeginMenu ("Disabled", false)) // Disabled
    {
      IM_ASSERT(0);
    }
  if (ImGui::MenuItem ("Checked", NULL, true))
    {
    }
  if (ImGui::MenuItem ("Quit", "Alt+F4"))
    {
      OnGuiMainMenuFileQuit ();
    }
}




bool LPGui::getStatusOfObjectWindow()
{
  return getStatusOfObjectWindow();
}


bool LPGui::getStatusOfStatusWindow()
{
  return getStatusOfStatusWindow();
}


// implemented here, used in LearningPlatform
void LPGui::updateGuiOnCurrentObjData(LPObject* obj)
{
  currentObject = obj;
}



// Implemented here, used in LearningPlatform
void LPGui::updateGuiOnFPersonData(LPObject* obj)
{
  fPerson = obj;
}
// void LPGui::updateGuiOnCurrentViewData(ViewIf* view) {currentView = obj;}

void LPGui::updateGuiOnProcessCompleted(int progress) {

  processCompleted = progress;
}


void
LPGui::runGui (bool show_test_window, bool show_another_window,
               bool show_object_window, ImVec4 clear_color, ImGuiIO io)
{

  // The top Main menu bar, good idea to have this as the first thing happening here.
  MainMenuBar ();

//  OnGuiMainMenuMoveObjEnabled(&statusOfMoveObjEnabled);
//  OnGuiMainMenuDetachFromFPS(&statusOfDetachFromFPS);


  // 1. Show a simple window
  // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
  //  {
  //    static float f = 0.0f;
  //    ImGui::Text("Hello, world!");
  //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
  //    ImGui::ColorEdit3("clear color", (float*)&clear_color);
  //    if (ImGui::Button("Test Window")) show_test_window = true;
  //    if (ImGui::Button("Another Window")) show_another_window = true;
  //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  //  }
  if (statusOfStatusWindow)
    {
      ImGui::SetNextWindowSize (ImVec2 (200, 100), ImGuiSetCond_FirstUseEver);
      ImGui::Begin ("Status Window");
      static float f = 0.0f;
      ImGui::Text ("Hello, world!");
      ImGui::SliderFloat ("float", &f, 0.0f, 1.0f);
      ImGui::ColorEdit3 ("clear color", (float*) &clear_color);
      if (ImGui::Button ("Test Window"))
        show_test_window = true;
      if (ImGui::Button ("Another Window"))
        show_another_window = true;
      ImGui::Text ("Application average %.3f ms/frame (%.1f FPS)",
                   1000.0f / ImGui::GetIO ().Framerate,
                   ImGui::GetIO ().Framerate);
      ImGui::End ();
    }


  if (statusOfChangeLight)
  {
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("LightPower of object");
    static float lightAmbient = 0.0f;
    if (currentObject != nullptr) {
      lightPower = currentObject->getLightPower();
      int id = currentObject->getId();
      int objType = currentObject->getObjType();
      const char* name = currentObject->getMoleculeInfo1().c_str();
      ImGui::Text("Light Settings for object: id=%d, obj type= %d, name=%s", id, objType, name);
    }
    ImGui::SliderFloat("LightPower", &lightPower, 100, 10000);
    ImGui::SliderFloat("Ambient", &lightAmbient, 100.0f, 10000.0f);
    if (currentObject != nullptr)
    {
      currentObject->setLightPower(lightPower);
    }
    ImGui::End();
  }

  if (statusOfConfigRayTrace)
  {
    ImGui::SetNextWindowSize (ImVec2 (200, 100), ImGuiSetCond_FirstUseEver);
    //     ImVec2 size = ImVec2(200.5,200.5);
    //     ImGui::SetNextWindowContentSize(size);

    ImGui::Begin ("RayTrace settings");
    //     ImGui::SetWindowFontScale(1.5);
    static float lightAmbient = 0.0f;
    if (currentObject != nullptr)
    {
      gOrientation = currentObject->getOrientation ();
      int id = currentObject->getId ();
      int objType = currentObject->getObjType ();
      const char* name = currentObject->getMoleculeInfo1 ().c_str ();

      vAngle = currentObject->getV ();
      yAngle = currentObject->getY ();


      xKatet = currentObject->getX ();
      zKatet = currentObject->getZ ();

      position = currentObject->getPosition ();

      ImGui::Text ("Settings for object: id=%d, obj type= %d, name=%s, Trans(%f,%f,%f)", id, objType, name, currentObject->getTrans ().x, currentObject->getTrans ().y, currentObject->getTrans ().z);
    }
    ImGui::SliderFloat ("x-axis Rotation ", &gOrientation.x, 0.0f, 2 * 3.14159265);
    ImGui::SliderFloat ("y-axis Rotation ", &gOrientation.y, 0.0f, 2 * 3.14159265);
    ImGui::SliderFloat ("z-axis Rotation ", &gOrientation.z, 0.0f, 2 * 3.14159265);

    ImGui::SliderFloat ("v angle", &vAngle, 0.0f, 2 * 3.14159265);
    ImGui::SliderFloat ("y angle", &yAngle, 0.0f, 2 * 3.14159265);

    ImGui::SliderFloat ("x katet", &xKatet, 0.0f, 100.0f);
    ImGui::SliderFloat ("z katet", &zKatet, 0.0f, 100.0f);

    if (currentObject != nullptr)
    {
//      currentObject->setOrientation (gOrientation);
      currentObject->setRotationMatrix (gOrientation);
    }
    ImGui::End ();
  }

  if (statusOfCreateWindow)
    {
    createWindowDialog();
    }

  if (statusOfCreateTextDialog) {
    createTextDialog();
  }

  if (statusOfCreateMoleculesDialog) {
    createMolecules();
  }

  if (statusOflistResources) {
    listResourcesDialog();
  }

  if (statusOfCreateMoleculesWindow)
  {
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
    //     ImVec2 size = ImVec2(200.5,200.5);
    //     ImGui::SetNextWindowContentSize(size);

    ImGui::Begin("Create a molecule");

    ImGui::Bullet();
    if (ImGui::SmallButton("Create Glucose")) {
      stage->createMolecule(view->getObjPlacementInFrontOfCamera(), ++lp_glucose, alpha_D_glucopyranose, 2, string("glucose"), string("info2"), string("info3"));
    }
    ImGui::Bullet();
    if (ImGui::SmallButton("Create Glucose6Phosphate")) {
      stage->createMolecule(view->getObjPlacementInFrontOfCamera(), ++lp_glucose, glucose6_phosphate, 2, string("glucose 6 Phosphate"), string("info2"), string("info3"));
    }
    ImGui::Bullet();
    if (ImGui::SmallButton("Create Fructose6-phosphate")) {
      stage->createMolecule(view->getObjPlacementInFrontOfCamera(), ++lp_glucose, fructose6_phosphate, 2, string("fructose 6 Phosphate"), string("info2"), string("info3"));
    }
    ImGui::Bullet();
    if (ImGui::SmallButton("Create Fructose1,6-bisphosphate")) {
      stage->createMolecule(view->getObjPlacementInFrontOfCamera(), ++lp_glucose, fructose1_6_bisphosphate, 2, string("Fructose 1,6 bisphosphate"), string("info2"), string("info3"));
    }

    ImGui::Bullet();
    if (ImGui::SmallButton("Create Dihydroxyacetone phosphate")) {
      stage->createMolecule(view->getObjPlacementInFrontOfCamera(), ++lp_glucose, dihydroxyacetone_phosphate, 2, string("Dihydroxyacetone phosphate"), string("info2"), string("info3"));
    }


    ImGui::End();
  }



  //  show_another_window = false;
  // 2. Show another simple window, this time using an explicit Begin/End pair
  if (show_another_window)
    {
      ImGui::SetNextWindowSize (ImVec2 (200, 100), ImGuiSetCond_FirstUseEver);
      ImGui::Begin ("Another Window", &show_another_window);
      ImGui::Text ("Hello, this is text written in Stage::initGui");
      ImGui::End ();
    }

  //  show_test_window = false;
  // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
  //  if (show_test_window)
  //  {
//      ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
//      ImGui::ShowTestWindow(&show_test_window);
  //  }

  if (statusOfObjectWindow)
    {
    ShowActiveObjects();
    }


  if (statusOfActorListWindow) {
    ActorListWindow();
  }

  if (showTextureListWindow) {
     TextureListWindow();
   }

//  bool someFlag = false;
//  Test2 (&someFlag);

  //   bool *l_open;
  //   *l_open = true;
  ShowExampleAppFixedOverlay ();

  if (getProcessCompleted() == 1)
  {
    ProcessCompleted();
  }


  if (fPerson != nullptr)
  {
    if (fPerson->isDead ())
    {
      ShowExampleAppFixedOverlay2 ();
      //    GameOver ();
    }

    if (fPerson != nullptr)
    {
      if (fPerson->isWinning ())
      {
        Winning ();
      }
    }
  }

  ShowCurrentObject();

  if (!regulationQuestion1State && !regulationQuestion2State && !regulationQuestion3State) {
    ShowQuestionWindow();
  }

  if (regulationQuestion1State) {
    ShowBackWindow1();
  }

  if (regulationQuestion2State) {
    ShowBackWindow2();
  }

  if (regulationQuestion3State) {
    ShowBackWindow3();
  }
//    bool someFlag = false;
//    Test2 (&someFlag);


  // Rendering
  //  glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
  //  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  //  glClear(GL_COLOR_BUFFER_BIT);
  ImGui::Render (io);
}

//void
//LPGui::GameOver () {
//  ImGui::SetNextWindowPos (ImVec2 (400, 400));
//  ImGui::SetWindowFontScale (1.5);
//
//  bool p_open2 = true;
//  if (!ImGui::Begin ("Example: Fixed Overlay", &p_open2, ImVec2 (200, 300), 0.3f,
//                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow))
//  {
//    ImGui::End ();
//    return;
//  }
//  ImGui::Separator ();
//  ImGui::Text ("Game Over");
//
//  ImGui::End ();
//}

void
LPGui::Winning () {
  ImGui::SetNextWindowPos (ImVec2 (400, 500));
  ImGui::SetWindowFontScale (2.0);

  bool p_open = true;
  if (!ImGui::Begin ("Overlay2", &p_open, ImVec2 (400, 300), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::Text ("Wrong text Overlay 2");
    ImGui::End ();
    return;
  }
  {
    ImGui::Text ("Level one Complete!");

  }
    ImGui::End ();
  }


void LPGui::ProcessCompleted () {
  ImGui::SetNextWindowPos (ImVec2 (500, 400));
  bool p_open = false;

  ImGui::Begin ("Overlay2", &p_open, ImVec2 (800, 200), 0.8f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
  ImGui::SetWindowFontScale (3.0);
  ImGui::Text ("                    %s", "Process Completed!");
  ImGui::End ();
}


void
LPGui::Test2 (bool* p_open) {
  ImGui::SetNextWindowPos (ImVec2 (10, 10));
  if (!ImGui::Begin ("Example: Fixed Overlay", p_open, ImVec2 (0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }
  ImGui::Text ("Simple overlay\non the top-left side of the screen.");
  ImGui::Separator ();
  ImGui::Text ("Mouse Position: (%.1f,%.1f)", ImGui::GetIO ().MousePos.x, ImGui::GetIO ().MousePos.y);
  ImGui::End ();
}

void
LPGui::ShowExampleAppFixedOverlay () {
  ImGui::SetNextWindowPos (ImVec2 (1600, 900));
//  ImGui::SetWindowSize (ImVec2 (100, 200));
  bool p_open = false;
  if (!ImGui::Begin ("Example: Fixed Overlay", &p_open, ImVec2 (300, 100), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }
//  ImGui::Text ("Status for the User showing here                                     ");
//  ImGui::Separator ();
  if (fPerson != nullptr)
  {
    ImGui::Text ("User Status");
    int hp = fPerson->getHp ();
    int xp = fPerson->getXp ();

    ImGui::ProgressBar (hp * 1.0f / 100.0f, ImVec2 (0.0f, 0.0f));
    ImGui::SameLine (0.0f, ImGui::GetStyle ().ItemInnerSpacing.x);
    ImGui::Text ("hp");

    ImGui::ProgressBar (xp * 1.0f / 100.0f, ImVec2 (0.0f, 0.0f));
    ImGui::SameLine (0.0f, ImGui::GetStyle ().ItemInnerSpacing.x);
    ImGui::Text ("xp");

  }
  ImGui::End ();
}

void
LPGui::ShowExampleAppFixedOverlay2 () {
  ImGui::SetWindowFontScale (2.0);
  ImGui::SetNextWindowPos (ImVec2 (350, 500));
//  ImGui::SetWindowSize (ImVec2 (100, 200));

  bool p_open = true;
  if (!ImGui::Begin ("Overlay2", &p_open, ImVec2 (1200, 300), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::Text ("Wrong text Overlay 2");
    ImGui::End ();
    return;
  }
//  ImGui::Text ("Status for the User showing here                                     ");
//  ImGui::Separator ();
//  if (fPerson != nullptr)
  {
    ImGui::Text ("Game Over");

  }
  ImGui::End ();

}

void LPGui::ShowCurrentObject() {
  ImGui::SetNextWindowPos (ImVec2 (1550, 30));
//  ImGui::SetWindowSize (ImVec2 (100, 200));
  bool p_open = false;
  if (!ImGui::Begin ("Show Current Object", &p_open, ImVec2 (350, 20), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }
//  ImGui::Text ("Status for the User showing here                                     ");
//  ImGui::Separator ();
  if (currentObject != nullptr) {
    ImGui::Text ("%s", currentObject->getMoleculeInfo1 ().c_str());
  }

  ImGui::End ();
}


void LPGui::ShowQuestionWindow() {
  ImGui::SetNextWindowPos (ImVec2 (1550, 65));


  ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button].w=0.0;
        style.Colors[ImGuiCol_Button].x=1.0;
        style.Colors[ImGuiCol_Button].y=1.0;
        style.Colors[ImGuiCol_Button].z=1.0;



//  ImGui::SetWindowSize (ImVec2 (100, 200));
  bool p_open = false;
  if (!ImGui::Begin ("Show Question Window", &p_open, ImVec2 (350, 100), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }


  style.Colors[ImGuiCol_Text].w=1.0f;
  style.Colors[ImGuiCol_Text].x=0.5f;
  style.Colors[ImGuiCol_Text].y=0.0f;
  style.Colors[ImGuiCol_Text].z=0.0f;

  style.Colors[ImGuiCol_Text].w=1.0;
  style.Colors[ImGuiCol_Text].x=0.6;
  style.Colors[ImGuiCol_Text].y=0.6;
  style.Colors[ImGuiCol_Text].z=0.6;



  if(OnGuigetRegulationQuestion1Active()) {
    style.Colors[ImGuiCol_Text].w=1.0;
    style.Colors[ImGuiCol_Text].x=1.0;
    style.Colors[ImGuiCol_Text].y=0.6;
    style.Colors[ImGuiCol_Text].z=0.6;
  }

  if(OnGuigetRegulationQuestion1ActiveAndSuccessful()) {
    style.Colors[ImGuiCol_Text].w=1.0;
    style.Colors[ImGuiCol_Text].x=0.6;
    style.Colors[ImGuiCol_Text].y=1.0;
    style.Colors[ImGuiCol_Text].z=0.6;
  }

  if (OnGuigetRegulationQuestion1Active() || OnGuigetRegulationQuestion1ActiveAndSuccessful()){

    if (ImGui::Button("How is glycolysis regulated by Hexokinase?")) {
      regulationQuestion1State = true;
      OnGuigetRegulationQuestionState(true);
      stage->createPlate(glm::vec3(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f,0.0f,4.0f)));
      stage->getTextObject(80001)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f, 0.0f, 5.4f));
      stage->getTextObject(62052)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f, -.5f, 5.4f));

      for (LPObject* obj : stage->getActorTextList()) {
        if (obj->getTrans().z == 30.4f) {
          (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, 10.4f));
        }
      }
    }
  }
    if(OnGuigetRegulationQuestion2Active()) {
      style.Colors[ImGuiCol_Text].w=1.0;
      style.Colors[ImGuiCol_Text].x=1.0;
      style.Colors[ImGuiCol_Text].y=0.6;
      style.Colors[ImGuiCol_Text].z=0.6;
    }

    if(OnGuigetRegulationQuestion2ActiveAndSuccessful()) {
      style.Colors[ImGuiCol_Text].w=1.0;
      style.Colors[ImGuiCol_Text].x=0.6;
      style.Colors[ImGuiCol_Text].y=1.0;
      style.Colors[ImGuiCol_Text].z=0.6;
    }

    if (OnGuigetRegulationQuestion2Active() || OnGuigetRegulationQuestion2ActiveAndSuccessful()){
      if (ImGui::Button("How is glycolysis regulated by Phosphofructokinase?")) {
        regulationQuestion2State = true;
        OnGuigetRegulationQuestionState(true);
        stage->createPlate(glm::vec3(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f,0.0f,4.0f)));
        stage->getTextObject(80002)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f, 0.0f, 5.4f));
        stage->getTextObject(62416)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f, -.5f, 5.4f));
        stage->getTextObject(62053)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(1.0f, -.5f, 5.4f));
        stage->getTextObject(62055)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(2.0f, -.5f, 5.4f));
      }

      for (LPObject* obj : stage->getActorTextList()) {
        if (obj->getTrans().z == 40.4f) {
          (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, 10.4f));
        }
      }
    }

    if(OnGuigetRegulationQuestion3Active()) {
      style.Colors[ImGuiCol_Text].w=1.0;
      style.Colors[ImGuiCol_Text].x=1.0;
      style.Colors[ImGuiCol_Text].y=0.6;
      style.Colors[ImGuiCol_Text].z=0.6;
    }

    if(OnGuigetRegulationQuestion3ActiveAndSuccessful()) {
      style.Colors[ImGuiCol_Text].w=1.0;
      style.Colors[ImGuiCol_Text].x=0.6;
      style.Colors[ImGuiCol_Text].y=1.0;
      style.Colors[ImGuiCol_Text].z=0.6;
    }

    if (OnGuigetRegulationQuestion3Active() || OnGuigetRegulationQuestion3ActiveAndSuccessful()){

      if (ImGui::Button("How is glycolysis regulated by Pyruvate kinase?")) {
        regulationQuestion3State = true;
        OnGuigetRegulationQuestionState(true);
        stage->createPlate(glm::vec3(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f,0.0f,4.0f)));
        stage->getTextObject(80003)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f, 0.0f, 5.4f));
        stage->getTextObject(62516)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(0.0f, -.5f, 5.4f));
        stage->getTextObject(62054)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(1.0f, -.5f, 5.4f));
        stage->getTextObject(62008)->setAbsoluteTrans(view->getObjPlacementInFrontOfCamera() + glm::vec3(2.0f, -.5f, 5.4f));
      }

      for (LPObject* obj : stage->getActorTextList()) {
              if (obj->getTrans().z == 50.4f) {
                (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, 10.4f));
              }
            }
    }
    const ImGuiStyle default_style; // Default style
    style = default_style;
  ImGui::End ();
}


void LPGui::ShowBackWindow1() {
  std::cout << "ShowBackWindow1" << std::endl;
  ImGui::SetNextWindowPos (ImVec2 (800, 800));
  //  ImGui::SetWindowSize (ImVec2 (100, 200));
  bool p_open = false;
  if (!ImGui::Begin ("Show Back Window", &p_open, ImVec2 (150, 60), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }
//  ImGui::Text ("lp_plate = %d", lp_plate);
  if (ImGui::Button("<<<--- Go Back 1")) {
    regulationQuestion1State = false;
    regulationQuestion2State = false;
    regulationQuestion3State = false;
    OnGuigetRegulationQuestionState(false);
    stage->deleteObject(++lp_plate);

//    stage->getTextObject(80001)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(80002)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(80003)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(62052)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));

    for (LPObject* obj : stage->getActorTextList()) {
        std::cout << "id=" << obj->getId() << ", z=" << obj->getTrans().z << " End" << std::endl;
      if (obj->getTrans().z == 10.4f) {
//        (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, obj->getTrans().z+20.0f));
                (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, 30.4f));
                std::cout << "INSIDE IF id=" << obj->getId() << ", z=" << obj->getTrans().z << " End" << std::endl;
      }
    }

  }
  ImGui::End ();
}

void LPGui::ShowBackWindow2() {
  std::cout << "ShowBackWindow2" << std::endl;
  ImGui::SetNextWindowPos (ImVec2 (800, 800));
  //  ImGui::SetWindowSize (ImVec2 (100, 200));
  bool p_open = false;
  if (!ImGui::Begin ("Show Back Window", &p_open, ImVec2 (150, 60), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }
//  ImGui::Text ("lp_plate = %d", lp_plate);
  if (ImGui::Button("<<<--- Go Back 2")) {
    regulationQuestion1State = false;
    regulationQuestion2State = false;
    regulationQuestion3State = false;
    OnGuigetRegulationQuestionState(false);
    stage->deleteObject(++lp_plate);

//    stage->getTextObject(80001)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(80002)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(80003)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(62052)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));

    for (LPObject* obj : stage->getActorTextList()) {
        std::cout << "id=" << obj->getId() << ", z=" << obj->getTrans().z << " End" << std::endl;
      if (obj->getTrans().z == 10.4f) {
        (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, 40.4f));
        stage->deleteObject(obj);
        std::cout << "INSIDE IF id=" << obj->getId() << ", z=" << obj->getTrans().z << " End" << std::endl;

      }
    }

  }
  ImGui::End ();
}

void LPGui::ShowBackWindow3() {
  std::cout << "ShowBackWindow3" << std::endl;
  ImGui::SetNextWindowPos (ImVec2 (800, 800));
  //  ImGui::SetWindowSize (ImVec2 (100, 200));
  bool p_open = false;
  if (!ImGui::Begin ("Show Back Window", &p_open, ImVec2 (150, 60), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
  {
    ImGui::End ();
    return;
  }
//  ImGui::Text ("lp_plate = %d", lp_plate);
  if (ImGui::Button("<<<--- Go Back 3")) {
    regulationQuestion1State = false;
    regulationQuestion2State = false;
    regulationQuestion3State = false;
    OnGuigetRegulationQuestionState(false);
    stage->deleteObject(++lp_plate);

//    stage->getTextObject(80001)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(80002)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(80003)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));
//    stage->getTextObject(62052)->setRelativeTrans(glm::vec3(0.0f, 0.0f, 50.0f));

    for (LPObject* obj : stage->getActorTextList()) {
        std::cout << "id=" << obj->getId() << ", z=" << obj->getTrans().z << " End" << std::endl;
      if (obj->getTrans().z == 10.4f) {
        (obj)->setAbsoluteTrans(glm::vec3(obj->getTrans().x, obj->getTrans().y, 50.4f));
        std::cout << "INSIDE IF id=" << obj->getId() << ", z=" << obj->getTrans().z << " End" << std::endl;
      }
    }

  }
  ImGui::End ();
}



void LPGui::listResourcesDialog()
{
  static bool no_titlebar = false;
  static bool no_border = true;
  static bool no_resize = false;
  static bool no_move = false;
  static bool no_scrollbar = false;
  static bool no_collapse = false;
  static bool no_menu = false;

  ImGuiWindowFlags window_flags = 0;
  if (no_titlebar)
    window_flags |= ImGuiWindowFlags_NoTitleBar;
  if (!no_border)
    window_flags |= ImGuiWindowFlags_ShowBorders;
  if (no_resize)
    window_flags |= ImGuiWindowFlags_NoResize;
  if (no_move)
    window_flags |= ImGuiWindowFlags_NoMove;
  if (no_scrollbar)
    window_flags |= ImGuiWindowFlags_NoScrollbar;
  if (no_collapse)
    window_flags |= ImGuiWindowFlags_NoCollapse;
  if (!no_menu)
    window_flags |= ImGuiWindowFlags_MenuBar;

  ImGui::SetNextWindowSize(ImVec2(500, 100), ImGuiSetCond_FirstUseEver);
  ImGui::Begin("List of available resources:");
  if (resObj != nullptr) {
    for (int i = 0; i < 256; i++) {
      if (resObj->meshArray[i].resScene != nullptr) {
        ImGui::Bullet();
        ImGui::Text("name = %s, id=%d, ", resObj->meshArray[i].name.c_str(), i);
      }
    }

  }
  else {
  }
  ImGui::End();
}

void LPGui::createTextDialog()
{
  ImGui::Begin("Create a Text Molecule");
  if (resObj != nullptr) {
    for (int i = 0; i < 256; i++) {
      if (resObj->txtObjArray[i].width != 0.0f) {
        std::string buttonText = "id=" + to_string(i) + ", name=" + resObj->txtObjArray[i].name;
        if (ImGui::SmallButton(buttonText.c_str())) {
          stage->createText(view->getObjPlacementInFrontOfCamera(), c_text + i, (ObjectType) (i + 1000), tx_red_floor);
          stage->getTextObject(c_text + i)->setMoleculeInfo1(resObj->txtObjArray[i].name);
//          callBrowser(resObj->txtObjArray[i].wikiName);
        }
        ImGui::SameLine();

        std::string wikiLabel = "Wiki link to " + resObj->txtObjArray[i].name;
        if (ImGui::SmallButton(wikiLabel.c_str())) {
//          ImGui::SameLine();
          callBrowser(resObj->txtObjArray[i].wikiName);
        }

      }
      else {
      }
    }
  }
  ImGui::End();
}

void LPGui::createMolecules()
{
  ImGui::Begin("Create a Molecule");

//  ImGuiStyle* ref = nullptr;
//  ImGuiStyle& style = ImGui::GetStyle();
////
////     // You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to the default style)
//     const ImGuiStyle default_style; // Default style
//     if (ImGui::Button("Revert Style"))
//         style = ref ? *ref : default_style;
//
//     if (ref)
//     {
//         ImGui::SameLine();
//         if (ImGui::Button("Save Style"))
//             *ref = style;
//     }
////
//     ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.55f);
//
//
//  if (ImGui::TreeNode("Colors"))
//      {
//          static int output_dest = 0;
//          static bool output_only_modified = false;
//          if (ImGui::Button("Copy Colors"))
//          {
//              if (output_dest == 0)
//                  ImGui::LogToClipboard();
//              else
//                  ImGui::LogToTTY();
//
//              for (int i = 0; i < ImGuiCol_COUNT; i++)
//              {
//                  const ImVec4& col = style.Colors[i];
//                  const char* name = ImGui::GetStyleColName(i);
//
//              }
//              ImGui::LogFinish();
//          }
//          ImGui::SameLine(); ImGui::PushItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0"); ImGui::PopItemWidth();
//          ImGui::SameLine(); ImGui::Checkbox("Only Modified Fields", &output_only_modified);
//
//          static ImGuiColorEditMode edit_mode = ImGuiColorEditMode_RGB;
//          ImGui::RadioButton("RGB", &edit_mode, ImGuiColorEditMode_RGB);
//          ImGui::SameLine();
//          ImGui::RadioButton("HSV", &edit_mode, ImGuiColorEditMode_HSV);
//          ImGui::SameLine();
//          ImGui::RadioButton("HEX", &edit_mode, ImGuiColorEditMode_HEX);
//          //ImGui::Text("Tip: Click on colored square to change edit mode.");
//
//          static ImGuiTextFilter filter;
//          filter.Draw("Filter colors", 200);
//
//          ImGui::BeginChild("#colors", ImVec2(0, 300), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
//          ImGui::PushItemWidth(-160);
//          ImGui::ColorEditMode(edit_mode);
//          for (int i = 0; i < ImGuiCol_COUNT; i++)
//          {
//              const char* name = ImGui::GetStyleColName(i);
//              if (!filter.PassFilter(name))
//                  continue;
//              ImGui::PushID(i);
//              ImGui::ColorEdit4(name, (float*)&style.Colors[i], true);
//              if (memcmp(&style.Colors[i], (ref ? &ref->Colors[i] : &default_style.Colors[i]), sizeof(ImVec4)) != 0)
//              {
//                  ImGui::SameLine(); if (ImGui::Button("Revert")) style.Colors[i] = ref ? ref->Colors[i] : default_style.Colors[i];
//                  if (ref) { ImGui::SameLine(); if (ImGui::Button("Save")) ref->Colors[i] = style.Colors[i]; }
//              }
//              ImGui::PopID();
//          }
//          ImGui::PopItemWidth();
//          ImGui::EndChild();
//
//          ImGui::TreePop();
//      }


  if (resObj != nullptr) {
    for (int i = 0; i < 256; i++) {
      if (resObj->txtObjArray[i].width != 0.0f) {
        if (resObj->txtObjArray[i].name.find("ase") != std::string::npos || resObj->txtObjArray[i].name.find("6-phosphate") != std::string::npos || resObj->txtObjArray[i].name.find("bisphosphate") != std::string::npos || resObj->txtObjArray[i].name.compare("H2O") == 0 || resObj->txtObjArray[i].name.compare("NADH") == 0 || resObj->txtObjArray[i].name.compare("Pi,NAD+") == 0
            || resObj->txtObjArray[i].name.compare("ATP") == 0 || resObj->txtObjArray[i].name.compare("ADP") == 0 || resObj->txtObjArray[i].name.compare("Alanin") == 0 || resObj->txtObjArray[i].name.compare("AMP") == 0 || resObj->txtObjArray[i].name.compare("Citrate") == 0) {
          if (resObj->txtObjArray[i].name.compare("regulated") != 0 && resObj->txtObjArray[i].name.compare("isomerase") != 0 && resObj->txtObjArray[i].name.compare("kinase") != 0 && resObj->txtObjArray[i].name.compare("mutase") != 0 && resObj->txtObjArray[i].name.compare("dehydrogenase") != 0) {
            ImGui::Separator();
            std::string buttonText = resObj->txtObjArray[i].name;
            glm::vec3 posInFrontOfCamera;

            if (ImGui::SmallButton(buttonText.c_str())) {
//              stage->createText(view->getObjPlacementInFrontOfCamera(), c_text + i, (ObjectType) (i + 1000), tx_red_floor);
              if (regulationQuestion1State || regulationQuestion2State || regulationQuestion3State) {
                posInFrontOfCamera = view->getObjPlacementInFrontOfCamera();
                posInFrontOfCamera +=glm::vec3(-0.8f, -0.5f, 5.4f);
              } else {
                posInFrontOfCamera = view->getObjPlacementInFrontOfCamera();
                posInFrontOfCamera.z = 0.0f;
              }
              if (stage->getTextObject(c_text + i) == nullptr) {
              stage->createText(glm::vec3(posInFrontOfCamera.x - 0.5f, posInFrontOfCamera.y, posInFrontOfCamera.z), c_text + i, (ObjectType) (i + 1000), tx_red_floor);
              stage->getTextObject(c_text + i)->setMoleculeInfo1(resObj->txtObjArray[i].name);
              }
              else if (stage->getTextObject(c_text + i + 100) == nullptr) {
                stage->createText(glm::vec3(posInFrontOfCamera.x - 0.5f, posInFrontOfCamera.y, posInFrontOfCamera.z), c_text + i + 100, (ObjectType) (i + 1000), tx_red_floor);
                stage->getTextObject(c_text + i + 100)->setMoleculeInfo1(resObj->txtObjArray[i].name);
              }
              else if (stage->getTextObject(c_text + i + 200) == nullptr) {
                stage->createText(glm::vec3(posInFrontOfCamera.x - 0.5f, posInFrontOfCamera.y, posInFrontOfCamera.z), c_text + i + 200, (ObjectType) (i + 1000), tx_red_floor);
                stage->getTextObject(c_text + i + 200)->setMoleculeInfo1(resObj->txtObjArray[i].name);
              }
              else if (stage->getTextObject(c_text + i + 300) == nullptr) {
                stage->createText(glm::vec3(posInFrontOfCamera.x - 0.5f, posInFrontOfCamera.y, posInFrontOfCamera.z), c_text + i + 300, (ObjectType) (i + 1000), tx_red_floor);
                stage->getTextObject(c_text + i + 300)->setMoleculeInfo1(resObj->txtObjArray[i].name);
              }
              else if (stage->getTextObject(c_text + i + 400) == nullptr) {
                stage->createText(glm::vec3(posInFrontOfCamera.x - 0.5f, posInFrontOfCamera.y, posInFrontOfCamera.z), c_text + i + 400, (ObjectType) (i + 1000), tx_red_floor);
                stage->getTextObject(c_text + i + 400)->setMoleculeInfo1(resObj->txtObjArray[i].name);
              }
              else if (stage->getTextObject(c_text + i + 500) == nullptr) {
                stage->createText(glm::vec3(posInFrontOfCamera.x - 0.5f, posInFrontOfCamera.y, posInFrontOfCamera.z), c_text + i + 500, (ObjectType) (i + 1000), tx_red_floor);
                stage->getTextObject(c_text + i + 500)->setMoleculeInfo1(resObj->txtObjArray[i].name);
              }
              else {
                //do nothing
              }
            }
            ImGui::SameLine(400);

            std::string wikiLabel = "PDB link##" + to_string(i);
            if (ImGui::SmallButton(wikiLabel.c_str())) {
              callBrowser(resObj->txtObjArray[i].wikiName);
            }
          }
        }
      }
      else {
      }
    }
  }
  ImGui::End();
}

void LPGui::callBrowser(std::string wikiSearch)
{
  std::string baseUrl("xdg-open http://www.rcsb.org/structure/");
  std::string url = baseUrl + wikiSearch;
  TRACE_DEBUG("callBrowser - baseUrl = %s", baseUrl.c_str());
  TRACE_DEBUG("callBrowser - url = %s", url.c_str());
  TRACE_DEBUG("callBrowser - molecule = %s", wikiSearch.c_str());

  system(url.c_str());
}

void LPGui::createWindowDialog()
{
  ImGui::Begin("Create an object");
  if (resObj != nullptr) {
    for (int i = 0; i < 256; i++) {
      if (resObj->meshArray[i].resScene != nullptr) {
        if (ImGui::SmallButton(resObj->meshArray[i].name.c_str())) {
          stage->createMolecule(view->getObjPlacementInFrontOfCamera(), ++lp_glucose, (ObjectType) i, 2, string(" "), string("info2"), string("info3"));
        }
      }
    }
  }
  ImGui::End();
}

int LPGui::getProcessCompleted() const
{
  return processCompleted;
}
