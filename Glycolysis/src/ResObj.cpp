/*
 * ResObj.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: peter
 */
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../inc/ResObj.h"
//#include "../inc/objloader.hpp"
#include "../inc/vboindexer.hpp"
#include "../inc/texture.hpp"
#include "../inc/shader.hpp"
#include  <string>
#include <list>
#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "../inc/SDL_base.h"
#include "../inc/logging.h"
#include <memory>
#include <pthread.h>

#include "../inc/LuaIf.h"

//#define STRINGIFY(x) #x
//#define LINE_TO_STR(x) STRINGIFY (x)
//#define TRACE_DEBUG(...) TRACE_DEBUG2(fmt, __VA_ARGS__)
//#define TRACE_DEBUG(fmt, ...)  SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)
//#define TRACE_ERROR(fmt, ...)  SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)
//#define TRACE_INFO(fmt, ...)  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)
//#define TRACE_WARN(fmt, ...)  SDL_LogWarn(SDL_LOG_CATEGORY_CUSTOM, __FILE__ ":" LINE_TO_STR(__LINE__) ", " fmt, ##__VA_ARGS__)


using namespace std;

ResObj::ResObj ()
{
  luaIf = new LuaIf(nullptr, this);
 logOutputPtr = new int (1);
 setLogging (logOutputPtr, 1);
}

ResObj::~ResObj ()
{
  TRACE_DEBUG("ENTER ResObj::~ResObj()");
 // TODO Auto-generated destructor stub
 for (int i = 0; i < 64; i++)
  {
   glDeleteBuffers (1, &vertexbuffer[i]);
   glDeleteBuffers (1, &uvbuffer[i]);
   glDeleteBuffers (1, &normalbuffer[i]);
  }
 for (int i = 0; i < objArray_length; i++)
  {
   for (std::vector<obj*>::iterator iter = meshArray[i].mesh.begin ();
     iter != meshArray[i].mesh.end (); iter++)
    {
     meshArray[i].mesh.erase (iter);
     
     delete *iter;
    }
  }
 for (int i = 0; i < objArray_length; i++)
  {
   for (std::vector<buffer*>::iterator iter = meshArray[i].buf.begin ();
     iter != meshArray[i].buf.end (); iter++)
    {
     meshArray[i].buf.erase (iter);
     delete *iter;
    }
  }
// TRACE_DEBUG("END ResObj::~ResObj()");
}

bool
ResObj::loadObjFiles_maze ()
{
//  loadStaticObjFiles("resources/obj/zombie/mutant_jump_attack.dae", zombie);
//  loadStaticObjFiles("resources/obj/zombie/zombie2_1/walking.dae", zombie);
//  loadStaticObjFiles("resources/obj/zombie/zombie2.obj", zombie);

//      loadStaticObjFiles("resources/obj/ghost/ghost.obj", ghost);
  loadStaticObjFiles("resources/obj/skybox/skybox.blend", skybox, "skybox", "skybox");
  loadStaticObjFiles("resources/obj/plate/plate_round_4x8.blend", plate, "plate", "");
//      loadStaticObjFiles("resources/obj/stone_brick/cliff_3.obj", plane);
//      loadStaticObjFiles("resources/obj/plane/plane3.obj", plane);
//      loadStaticObjFiles("resources/obj/plane/plane4.obj", plane);
  loadStaticObjFiles("resources/obj/plane/plane003.obj", plane, "plane", "");
  loadStaticObjFiles("cube.obj", cube, "cube", "cube");
  loadStaticObjFiles("resources/obj/maze/maze_floor_3x1.blend", maze_floor_3x1, "maze_floor_3x1", "");
  loadStaticObjFiles("resources/obj/maze/maze_floor_3x5.blend", maze_floor_3x5, "maze_floor_3x5", "");
 loadStaticObjFiles ("resources/obj/maze/maze_floor_3x10.blend",
                     maze_floor_3x10, "maze_floor_3x10", "");
 loadStaticObjFiles ("resources/obj/maze/maze_floor_3x20.blend",
                     maze_floor_3x20, "maze_floor_3x20", "");
  loadStaticObjFiles("resources/obj/maze/maze_floor_3x3.blend", maze_floor_3x3, "maze_floor_3x3", "");
  loadStaticObjFiles("resources/obj/maze/maze_floor_5x5.blend", maze_floor_5x5, "maze_floor_5x5", "");

  loadStaticObjFiles("resources/obj/maze/maze_door_3x2.blend", maze_door_3x2, "maze_door_3x2", "");
 loadStaticObjFiles ("resources/obj/maze/maze_door_x_3x3.blend",
                     maze_door_x_3x3, "maze_door_x_3x3", "");
 loadStaticObjFiles ("resources/obj/maze/maze_door_y_3x3.blend",
                     maze_door_y_3x3, "maze_door_y_3x3", "");

// disabled 3 below testing menu myGUI
//      loadStaticObjFiles("resources/obj/phosphoglycerate/phosphoglycerate2.obj", phospho_glycerate);

//  loadStaticObjFiles("resources/obj/glucose/glucose_wrl_4.blend", glucose);
//  loadStaticObjFiles("resources/obj/glucose/myGlucose1.obj", glucose);

// -- EPEBROR Below temp commented out in order to test Lua
// Temporary commented out

// loadStaticObjFiles (
//   "resources/obj/glucose6-phosphate/glucose6-phosphate_7.blend",
//   glucose6_phosphate);
// loadStaticObjFiles ("resources/obj/glucose/alpha_D_glucopyranose.obj",
//                     alpha_D_glucopyranose);
// loadStaticObjFiles (
//   "resources/obj/fructose-6-phosphate/fructose-6-phosphate.obj",
//   fructose6_phosphate);
// loadStaticObjFiles (
//   "resources/obj/fructose1_6_bisphosphate/fructose1_6-bisphosphate.obj",
//   fructose1_6_bisphosphate);
// loadStaticObjFiles (
//   "resources/obj/glyceraldehyde_3_phosphate/glyceraldehyde_3_phosphate.obj",
//   glyceraldehyde_3_phosphate);
// loadStaticObjFiles (
//   "resources/obj/dihydroxyacetone_phosphate/dihydroxyacetone_phosphate.obj",
//   dihydroxyacetone_phosphate);
// loadStaticObjFiles (
//   "resources/obj/1_3_bisphosphoglycerate/1_3_bisphosphoglycerate.obj",
//   one_three_bisphosphoglycerate);
// loadStaticObjFiles ("resources/obj/3_phosphoglycerate/3_phosphoglycerate.obj",
//                     three_phosphoglycerate);
// loadStaticObjFiles ("resources/obj/2_phosphoglycerate/2_phosphoglycerate.obj",
//                     two_phosphoglycerate);
// loadStaticObjFiles (
//   "resources/obj/phosphoenolpyruvate/phosphoenolpyruvate.obj",
//   phosphoenolpyruvate);
// loadStaticObjFiles ("resources/obj/pyruvate/pyruvate.obj", pyruvate);

//  loadStaticObjFiles("resources/obj/atp/atp.obj", atp);

// -- EPEBROR End

//      loadStaticObjFiles("resources/obj/hexokinase/hexokinase_wrl_1glk-ribbon-secondary.blend", hexokinase);

//      loadStaticObjFiles("resources/obj/phosphofructokinase/PDB-4OMT-ribbon-secondary.wrl", phosphofructokinase);
//      loadStaticObjFiles("resources/obj/phosphofructokinase/PDB-4OMT-xxx.blend", phosphofructokinase);

// disabled  below testing menu myGUI
//      loadStaticObjFiles("resources/obj/phosphofructokinase/PDB-4OMT-yyy.blend", phosphofructokinase);

//      loadStaticObjFiles("resources/obj/phosphofructokinase/PDB-4OMT-surf-coulombic.wrl", phosphofructokinase);
//      loadStaticObjFiles("resources/obj/phosphofructokinase/PDB-4OMT-ribbon.stl", phosphofructokinase);

//      loadStaticObjFiles("resources/obj/phosphofructokinase/PDB-4OMT-surf-hydropathy.blend", phosphofructokinase);

// loadStaticObjFiles("resources/obj/plane/plane003.obj", plane);
//      loadStaticObjFiles("resources/obj/box/blender_cube.obj", box);
//  loadStaticObjFiles ("resources/obj/box/box.obj", box);
  loadStaticObjFiles("resources/obj/wall/wall.obj", wall, "wall", "");
  loadStaticObjFiles("resources/obj/wall/wall_2x32x32.obj", wall_2x32x32, "wall_2x32x32", "");

 // EPEBROR disabled below testing imgui
//loadStaticObjFiles("resources/obj/arrow/arrow.obj", arrow);
//loadStaticObjFiles("resources/obj/arrow/arrow2.obj", arrow2);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle.blend", arrow3);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_single.blend", arrow_rectangle_down_single);

//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_single4.blend", arrow_rectangle_down_single1);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_single5.blend", arrow_rectangle_down_single1);

// disabled x below testing menu myGUI

// temporary commented out
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_single_bent9.obj", arrow_rectangle_down_single1);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_up_bent.obj", arrow_rectangle_down_up_bent);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_up_halfside_bent.obj", arrow_rectangle_down_up_halfside_bent);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_up_bent_long.obj", arrow_rectangle_down_up_bent_long);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_up2.obj", arrow_rectangle_down_up);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_side.obj", arrow_rectangle_down_side);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_side_long.obj", arrow_rectangle_down_side_long);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_up_45.obj", arrow_rectangle_down_up_45);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_down_up_45_1.obj", arrow_rectangle_down_up_45_1);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_up_single.blend", arrow_rectangle_up_single);
//loadStaticObjFiles("resources/obj/arrow/arrow_rectangle_up_double.blend", arrow_rectangle_up_double);

//      loadActorObjFiles("resources/obj/creature/creature_walk", creature0, 23);
//        loadStaticObjFiles("resources/obj/landscape/landscape.obj", landscape);
//      loadStaticObjFiles("resources/obj/blenderguy/guy_texture_01.obj", boy);

//  loadActorObjFiles("resources/obj/sniper/injured-walk6/sniper-inj-walk_joined", sniper1, 29);

//  loadStaticObjFiles("resources/obj/sniper/injured-walk6/sniper-inj-walk_joined_000003.obj", sniper1);

  loadStaticObjFiles("resources/obj/zombie//mutant_run.dae", sniper1, "sniper1", "");
//  loadStaticObjFiles("resources/obj/zombie//mutant_breathing_idle.dae", sniper1);

//  loadStaticObjFiles("resources/obj/bob/boblampclean.md5mesh", zombie);

//  loadStaticObjFiles("resources/obj/zombie_attack.dae", sniper1);

//  loadStaticObjFiles("resources/obj/zombie/zombie2_1/walking.dae", sniper3);

//  loadStaticObjFiles("resources/obj/zombie/mutant_dying.dae", sniper1);

//  loadStaticObjFiles("resources/obj/zombie/zombie2.obj", zombie);
//  loadStaticObjFiles("resources/obj/zombie/mutant_walking.dae", zombie);

//  loadStaticObjFiles("resources/obj/sniper/injured-walk5/sniper-inj-walk_joined_000001.obj", sniper1);

//      loadStaticObjFiles("resources/obj/pilot2/pilot2.obj", pilot);

  loadStaticObjFiles("resources/obj/box/blender_ball.obj", ball, "ball", "ball");

//      loadStaticObjFiles("resources/obj/ball/blender_ball.obj", ball);

 return true;
}

bool ResObj::loadObjFiles()
{
  if (luaIf->config("biomolcraft_config_resobj.lua") != 0) {
    TRACE_ERROR("ResObj::loadObjFiles(): failed to load file biomolcraft_config_resobj.lua, probably syntax error in file.");
    return false;
  }
  return true;
}

bool
ResObj::loadObjFilesMultiThreading()
{
  if (luaIf->config("biomolcraft_config_resobj_multithreading.lua") != 0) {
    TRACE_ERROR("ResObj::loadObjFilesMultiThreading(): failed to load file biomolcraft_config_resobj_multithreading.lua, probably syntax error in file.");
    return false;
  }
 return true;
}

void
ResObj::loadActorObjFiles (const char * objpath, ObjectType objType,
                           int stream_length)
{
 char file[128];
 int obj_path_length = 0;
 while (objpath[obj_path_length] != '\0')
  {
   obj_path_length++;
  }

 memcpy (file, objpath, obj_path_length);
 int j = 0;
 file[obj_path_length] = '_';
 file[obj_path_length + 1] = 48;
 file[obj_path_length + 2] = 48;
 file[obj_path_length + 3] = 48;
 file[obj_path_length + 4] = 48;
//	printf("objpath: %s\n", objpath);
//	printf("File: %s\n", file);
 for (int i = 1; i <= stream_length; i++)
  {
   // load the object with vertices from file
   if (i < 10)
    {
     file[obj_path_length + 5] = 48;
     file[obj_path_length + 6] = i + 48;
     file[obj_path_length + 7] = '.';
     file[obj_path_length + 8] = 'o';
     file[obj_path_length + 9] = 'b';
     file[obj_path_length + 10] = 'j';
    }
   else if (i < 20)
    {
     file[obj_path_length + 5] = 49;
     file[obj_path_length + 6] = i - 10 + 48;
     file[obj_path_length + 7] = '.';
     file[obj_path_length + 8] = 'o';
     file[obj_path_length + 9] = 'b';
     file[obj_path_length + 10] = 'j';
    }
   else if (i < 30)
    {
     file[obj_path_length + 5] = 50;
     file[obj_path_length + 6] = i - 20 + 48;
     file[obj_path_length + 7] = '.';
     file[obj_path_length + 8] = 'o';
     file[obj_path_length + 9] = 'b';
     file[obj_path_length + 10] = 'j';
    }
   printf ("File: %s\n", file);
   file[obj_path_length + 11] = '\0';
   printf ("File: %s\n", file);
   j = objType + i - 1;
   printf ("j= %d\n", j);
   loadOBJ (file, objArray[j].vertices, objArray[j].uvs, objArray[j].normals,
            false);

   // vertexbuffer;
   glGenBuffers (1, &vertexbuffer[j]);
   glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer[j]);
   glBufferData (GL_ARRAY_BUFFER,
                 objArray[j].vertices.size () * sizeof(glm::vec3),
                 &objArray[j].vertices[0], GL_STREAM_DRAW);

   //uvbuffer
   glGenBuffers (1, &uvbuffer[j]);
   glBindBuffer (GL_ARRAY_BUFFER, uvbuffer[j]);
   glBufferData (GL_ARRAY_BUFFER, objArray[j].uvs.size () * sizeof(glm::vec2),
                 &objArray[j].uvs[0], GL_STREAM_DRAW);

   //normalbuffer;
   glGenBuffers (1, &normalbuffer[j]);
   glBindBuffer (GL_ARRAY_BUFFER, normalbuffer[j]);
   glBufferData (GL_ARRAY_BUFFER,
                 objArray[j].normals.size () * sizeof(glm::vec3),
                 &objArray[j].normals[0], GL_STREAM_DRAW);
  }
}

bool
ResObj::loadOBJWithAssimp (const char * path, ObjectType objType, Mesh& mesh)
{
 SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM,
              "Enter function loadOBJWithAssimp, Loading OBJ file %s...\n",
              path);

//  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
//  std::vector<glm::vec3> temp_vertices;
//  std::vector<glm::vec2> temp_uvs;
//  std::vector<glm::vec3> temp_normals;

 // Load the object from file
//  const aiScene * resScene;

 //  loadObj(path, resScene);

 /////////////////////////////////////////////////////////////////
 Assimp::Importer importer;
 // And have it read the given file with some example postprocessing
 // Usually - if speed is not the most important aspect for you - you'll
 // propably to request more postprocessing than we do in this example.
 resScene = importer.ReadFile (
   path,
   aiProcess_CalcTangentSpace | aiProcess_Triangulate
     | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
     | aiProcess_RemoveRedundantMaterials | aiProcess_FindInvalidData
     | aiProcess_FixInfacingNormals);

 resScene = importer.GetOrphanedScene ();
 // If the import failed, report it
 if (!resScene)
  {
   SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "ERROR ASSIMP FAILED: %s",
                importer.GetErrorString ());
   resScene = NULL;
   //      return NULL;
  }

 int noOfBones = 0;
 for (int g = 0; g < resScene->mNumMeshes; g++)
  {
//    for (unsigned int g = 0; g < 2; g++) {
   noOfBones += resScene->mMeshes[g]->mNumBones;
  }

 int noOfVertices = 0;
 for (int g = 0; g < resScene->mNumMeshes; g++)
  {
//    for (unsigned int g = 0; g < 2; g++) {
   noOfVertices += resScene->mMeshes[g]->mNumVertices;
  }

//  mesh.name.assign(path);
 TRACE_DEBUG ("loadObj method: Loaded object: %s", path);
 TRACE_DEBUG("number OF MESHES: %d", resScene->mNumMeshes);
 TRACE_DEBUG("number OF TEXTURES: %d", resScene->mNumTextures);
 TRACE_DEBUG("number OF VERTICES: %d", resScene->mMeshes[0]->mNumVertices);
 TRACE_DEBUG("number OF FACES: %d", resScene->mMeshes[0]->mNumFaces);
 TRACE_DEBUG("number OF BONES: %d", noOfBones);
 TRACE_DEBUG("number OF ANIMATIONS: %d", resScene->mNumAnimations);
 /////////////////////////////////////////////////////////////////
//  GLuint NumVertices = 0;
//  for (unsigned int meshCount = 0; meshCount < resScene->mNumMeshes; meshCount++) {
//    NumVertices += resScene->mMeshes[meshCount]->mNumVertices;
//  }
//  mesh[objType]

 if (resScene->mNumAnimations == 0)
  { // No Animations
   for (unsigned int meshCount = 0; meshCount < resScene->mNumMeshes;
     meshCount++)
    {
     const aiMesh * paiMesh = resScene->mMeshes[meshCount];
     obj* singelMesh = new (obj);
     singelMesh->m_NumAnimations = 0;
     singelMesh->m_NumBones = 0;
     singelMesh->bones.resize (paiMesh->mNumVertices);

     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "Name: %s, Has Materials: %d",
                   paiMesh->mName.C_Str (), resScene->HasMaterials ());
     if (resScene->HasMaterials ())
      {
       GLuint mIndex = paiMesh->mMaterialIndex;
       SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "MaterialIndex: %d",
                     paiMesh->mMaterialIndex);
       aiColor4D color;
       aiMaterial* mtl = resScene->mMaterials[mIndex];
       aiGetMaterialColor (mtl, AI_MATKEY_COLOR_DIFFUSE, &color);
       SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM,
                     "Mesh index= %d, Colors: (%f,%f,%f)", meshCount, color.r,
                     color.g, color.b);
       singelMesh->meshColor[0] = color.r;
       singelMesh->meshColor[1] = color.g;
       singelMesh->meshColor[2] = color.b;
       singelMesh->meshColor[3] = color.a;
      }
     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM,
                   "Number of Meshes=%d, number of vertices=%d\n",
                   resScene->mNumMeshes, paiMesh->mNumVertices);
     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "Number of Faces=%d\n",
                   paiMesh->mNumFaces);
     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "Face:numOfIndices= %d",
                   paiMesh->mFaces[0].mNumIndices);
//    if (paiMesh->mNumBones > 0) {
//      aiBone* bone = paiMesh->mBones[0];
//      if (bone->mNumWeights > 0) {
//        SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "bone[0] %s with mVertexId=%d, weight=%f", bone->mName.C_Str(), bone->mWeights[0].mVertexId, bone->mWeights[0].mWeight);
//        for (int w = 0; w < bone->mNumWeights; ++w) {
//          SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "[%d] number of weights=%d, weight=%f, mVertexId=%d, #bones=%d", w, bone->mNumWeights, bone->mWeights[w].mWeight, bone->mWeights[w].mVertexId, paiMesh->mNumBones);
//        }
//      }
//    }

//-- New way, retrieveing everything via vertices

     for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
      {
       glm::vec3 vertex = glm::vec3 (paiMesh->mVertices[i].x,
                                     paiMesh->mVertices[i].y,
                                     paiMesh->mVertices[i].z);
       singelMesh->vertices.push_back (vertex);
       if (paiMesh->HasTextureCoords (0))
        {
         glm::vec2 uv = glm::vec2 (paiMesh->mTextureCoords[0][i].x,
                                   paiMesh->mTextureCoords[0][i].y);
         singelMesh->uvs.push_back (uv);
        }
       else
        {
         glm::vec2 uv = glm::vec2 (0.0f, 0.0f);
         singelMesh->uvs.push_back (uv);
        }
       if (paiMesh->HasNormals ())
        {
         glm::vec3 normal = glm::vec3 (paiMesh->mNormals[i].x,
                                       paiMesh->mNormals[i].y,
                                       paiMesh->mNormals[i].z);
         singelMesh->normals.push_back (normal);
        }
       else
        {
         glm::vec3 normal = glm::vec3 (1.0f, 1.0f, 1.0f);
         singelMesh->normals.push_back (normal);
        }
      }

     // Populate the index buffer
     int iMeshFaces = paiMesh->mNumFaces;
     for (int j = 0; j < iMeshFaces; j++)
      {
       const aiFace& face = paiMesh->mFaces[j];
       assert(face.mNumIndices == 3);
       singelMesh->indices.push_back ((GLuint) face.mIndices[0]);
       singelMesh->indices.push_back ((GLuint) face.mIndices[1]);
       singelMesh->indices.push_back ((GLuint) face.mIndices[2]);
      }

      SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "SingelMesh: pushing vertex meshCount=%d", meshCount);
     mesh.mesh.push_back (singelMesh);
//      LoadBones(meshCount, paiMesh, mesh, objType);
    }
  }
 else
  { // Animations > 0

   obj* singelMesh = new (obj);
   singelMesh->m_NumBones = 0;
   singelMesh->m_NumAnimations = resScene->mNumAnimations;
   singelMesh->bones.resize (noOfVertices);
   for (unsigned int meshCount = 0; meshCount < resScene->mNumMeshes;
     meshCount++)
    {
//    for (unsigned int meshCount = 0; meshCount < 1; meshCount++) {
     //    for (unsigned int meshCount = 0; meshCount < 2; meshCount++) {
     const aiMesh * paiMesh = resScene->mMeshes[meshCount];

     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "Name: %s, Has Materials: %d",
                   paiMesh->mName.C_Str (), resScene->HasMaterials ());
     if (resScene->HasMaterials ())
      {
       GLuint mIndex = paiMesh->mMaterialIndex;
       SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "MaterialIndex: %d",
                     paiMesh->mMaterialIndex);
       aiColor4D color;
       aiMaterial* mtl = resScene->mMaterials[mIndex];
       aiGetMaterialColor (mtl, AI_MATKEY_COLOR_DIFFUSE, &color);
       SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM,
                     "Mesh index= %d, Colors: (%f,%f,%f)", meshCount, color.r,
                     color.g, color.b);
       singelMesh->meshColor[0] = color.r;
       singelMesh->meshColor[1] = color.g;
       singelMesh->meshColor[2] = color.b;
       singelMesh->meshColor[3] = color.a;
      }
     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM,
                   "Number of Meshes=%d, number of vertices=%d\n",
                   resScene->mNumMeshes, paiMesh->mNumVertices);
     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "Number of Faces=%d\n",
                   paiMesh->mNumFaces);
     SDL_LogDebug (SDL_LOG_CATEGORY_CUSTOM, "Face:numOfIndices= %d",
                   paiMesh->mFaces[0].mNumIndices);
     //    if (paiMesh->mNumBones > 0) {
     //      aiBone* bone = paiMesh->mBones[0];
     //      if (bone->mNumWeights > 0) {
     //        SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "bone[0] %s with mVertexId=%d, weight=%f", bone->mName.C_Str(), bone->mWeights[0].mVertexId, bone->mWeights[0].mWeight);
     //        for (int w = 0; w < bone->mNumWeights; ++w) {
     //          SDL_LogDebug(SDL_LOG_CATEGORY_CUSTOM, "[%d] number of weights=%d, weight=%f, mVertexId=%d, #bones=%d", w, bone->mNumWeights, bone->mWeights[w].mWeight, bone->mWeights[w].mVertexId, paiMesh->mNumBones);
     //        }
     //      }
     //    }

     //-- New way, retrieveing everything via vertices

     for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
      {
       glm::vec3 vertex = glm::vec3 (paiMesh->mVertices[i].x,
                                     paiMesh->mVertices[i].y,
                                     paiMesh->mVertices[i].z);
       singelMesh->vertices.push_back (vertex);
       if (paiMesh->HasTextureCoords (0))
        {
         glm::vec2 uv = glm::vec2 (paiMesh->mTextureCoords[0][i].x,
                                   paiMesh->mTextureCoords[0][i].y);
         singelMesh->uvs.push_back (uv);
        }
       else
        {
         glm::vec2 uv = glm::vec2 (0.0f, 0.0f);
         singelMesh->uvs.push_back (uv);
        }
       if (paiMesh->HasNormals ())
        {
         glm::vec3 normal = glm::vec3 (paiMesh->mNormals[i].x,
                                       paiMesh->mNormals[i].y,
                                       paiMesh->mNormals[i].z);
         singelMesh->normals.push_back (normal);
        }
       else
        {
         glm::vec3 normal = glm::vec3 (1.0f, 1.0f, 1.0f);
         singelMesh->normals.push_back (normal);
        }
      }

     int offset = 0;
     // indices probably needs to be increased by an offset off of previous meshes:
      for (unsigned int i = 0; i < meshCount; i++)
      {
       offset += resScene->mMeshes[i]->mNumVertices;
      }

     // Populate the index buffer
     int iMeshFaces = paiMesh->mNumFaces;
     for (int j = 0; j < iMeshFaces; j++)
      {
       const aiFace& face = paiMesh->mFaces[j];
       assert(face.mNumIndices == 3);
       //        SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "MFACES SIZE: %d", face.mNumIndices);
       singelMesh->indices.push_back ((GLuint) face.mIndices[0] + offset);
       singelMesh->indices.push_back ((GLuint) face.mIndices[1] + offset);
       singelMesh->indices.push_back ((GLuint) face.mIndices[2] + offset);
      }
//      int BaseVertex = 0;
//      for (int b = 1; b < (meshCount + 1); b++) {
//        SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "ResObj::LoadBones: 5");
//        BaseVertex += mesh.mesh[b - 1]->vertices.size();
//      }
     std::cout << "LoadBones for meshCount= " << meshCount << std::endl;
     LoadBones (meshCount, paiMesh, singelMesh, objType, offset);
    }
   mesh.mesh.push_back (singelMesh);
  }

 // Read animation as well
//  if (resScene->mNumAnimations > 0) {
//    for (unsigned int animationCount = 0; animationCount < resScene->mNumAnimations; ++animationCount) {
//      aiAnimation* singleAnimation = resScene->mAnimations[animationCount];
//
//      singleAnimation->mDuration;
//    }
//  }

//  std::cout << "number of out_vertices="<< mesh[0]->vertices.size()<< std::endl;
//  std::cout << "vertex 0: " << mesh[0]->vertices[0].r << ", " << mesh[0]->vertices[0].g << ", " << mesh[0]->vertices[0].b << std::endl;
//  std::cout << "vertex 1: " << mesh[0]->vertices[1].r << ", " << mesh[0]->vertices[1].g << ", " << mesh[0]->vertices[1].b << std::endl;
 return true;
}

void
ResObj::loadStaticObjFiles(const char * objpath, ObjectType objType, const char* name, const char* wikiName)
{
 printf ("Enter method ResObj::loadStaticObjFiles, loading file = %s\n",
         objpath);
  meshArray[objType].name.assign(name);
  meshArray[objType].wikiName.assign(name);
 loadOBJWithAssimp (objpath, objType, meshArray[objType]);

//	std::vector<unsigned int> Indices;
//  numIndices = Indices.size();

 meshArray[objType].resScene = resScene;
 aiMatrix4x4 mTransformation = resScene->mRootNode->mTransformation;
 mTransformation.Inverse ();

 meshArray[objType].m_GlobalInverseTransform =
  {
    {mTransformation.a1, mTransformation.a2, mTransformation.a3, mTransformation.a4},
    {mTransformation.b1, mTransformation.b2, mTransformation.b3, mTransformation.b4},
    {mTransformation.c1, mTransformation.c2, mTransformation.c3, mTransformation.c4},
    {mTransformation.d1, mTransformation.d2, mTransformation.d3, mTransformation.d4}
  };

 meshArray[objType].m_GlobalInverseTransform = glm::inverse (
   meshArray[objType].m_GlobalInverseTransform);
 std::cout << "number of out_vertices="
   << meshArray[objType].mesh[0]->vertices.size () << std::endl;
 std::cout << "vertex 0: " << meshArray[objType].mesh[0]->vertices[0].r << ", "
   << meshArray[objType].mesh[0]->vertices[0].g << ", "
   << meshArray[objType].mesh[0]->vertices[0].b << std::endl;
 std::cout << "vertex 1: " << meshArray[objType].mesh[0]->vertices[1].r << ", "
   << meshArray[objType].mesh[0]->vertices[1].g << ", "
   << meshArray[objType].mesh[0]->vertices[1].b << std::endl;

//  for (std::vector<obj>::iterator* it =  meshArray[objType].begin(); it !=  meshArray[objType].end() ;it++) {
 for (int i = 0; i < meshArray[objType].mesh.size (); i++)
  {
   TRACE_DEBUG("Start Gen buffers for vertices, i=%d", i);

   buffer* buf = new buffer;
   glGenBuffers (1, &buf->vertices);
   glBindBuffer (GL_ARRAY_BUFFER, buf->vertices);
   glBufferData (
     GL_ARRAY_BUFFER,
     meshArray[objType].mesh[i]->vertices.size () * sizeof(glm::vec3),
     &meshArray[objType].mesh[i]->vertices[0], GL_STATIC_DRAW);
   TRACE_DEBUG("Start Gen buffers for uvs, i=%d", i);
   // uvbuffer
   glGenBuffers (1, &(buf->uvs));
   glBindBuffer (GL_ARRAY_BUFFER, buf->uvs);
   glBufferData (GL_ARRAY_BUFFER,
                 meshArray[objType].mesh[i]->uvs.size () * sizeof(glm::vec2),
                 &(meshArray[objType].mesh[i]->uvs[0]), GL_STATIC_DRAW);
   TRACE_DEBUG("Start Gen buffers for normals, i=%d", i);
   // normalbuffer;
   glGenBuffers (1, &(buf->normals));
   glBindBuffer (GL_ARRAY_BUFFER, buf->normals);
   glBufferData (
     GL_ARRAY_BUFFER,
     meshArray[objType].mesh[i]->normals.size () * sizeof(glm::vec3),
     &(meshArray[objType].mesh[i]->normals[0]), GL_STATIC_DRAW);
   TRACE_DEBUG("Start Gen buffers for indices, i=%d", i);
   // indicesbuffer;
   glGenBuffers (1, &(buf->indices));
   glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, buf->indices);
   glBufferData (
     GL_ELEMENT_ARRAY_BUFFER,
     meshArray[objType].mesh[i]->indices.size ()
       * sizeof(meshArray[objType].mesh[i]->indices[0]),
     &(meshArray[objType].mesh[i]->indices[0]), GL_STATIC_DRAW);

   TRACE_DEBUG("Start Gen buffers for bones, i=%d", i);
   // bonesbuffer;
   glGenBuffers (1, &(buf->bones));
   glBindBuffer (GL_ARRAY_BUFFER, buf->bones);
   glBufferData (
     GL_ARRAY_BUFFER,
     meshArray[objType].mesh[i]->bones.size ()
       * sizeof(meshArray[objType].mesh[i]->bones[0]),
     &(meshArray[objType].mesh[i]->bones[0]), GL_STATIC_DRAW);
   TRACE_DEBUG("Finished Gen buffers for bones, i=%d", i);
   if (glGetError () != GL_NO_ERROR)
    {
     TRACE_ERROR("ERROR in OpenGL: OpenGL returned an Error:%d", glGetError());
    }
   buf->sizeOfVertices = meshArray[objType].mesh[i]->vertices.size ();
   buf->sizeOfIndices = meshArray[objType].mesh[i]->indices.size ();
   TRACE_DEBUG("VERTICES SIZE: %d",
                buf->sizeOfVertices);
   TRACE_DEBUG("INDICES SIZE: %d",
                buf->sizeOfIndices);
   buf->meshColor[0] = meshArray[objType].mesh[i]->meshColor[0];
   buf->meshColor[1] = meshArray[objType].mesh[i]->meshColor[1];
   buf->meshColor[2] = meshArray[objType].mesh[i]->meshColor[2];
   buf->meshColor[3] = meshArray[objType].mesh[i]->meshColor[3];
   TRACE_DEBUG("ResObj::loadStaticObjFiles push_back buf into meshArray");
   meshArray[objType].buf.push_back (buf);
  }
}

bool
ResObj::loadTextFile (char *path)
{
 FILE * file = fopen (path, "r");
 int res;

 if (file == NULL)
  {
   TRACE_ERROR("loadTextFile: Impossible to open the file: %s! Are you in the right path ? See Tutorial 1 for details\n", path);
   getchar ();
   return false;
  }
 //	int count = 1;
 while (1)
  {
   struct Txt myTxt;
   char text[256];
    char wikiName[256];
   char font[256];
   char c;
   int i = 0;
   // read the first word of the line
    do {
      c = fgetc(file);
      if (c == EOF) {
        res = EOF;
        break;
      }
      text[i] = c;
      i++;
    }
    while (c != '\n');

    text[i - 1] = '\0';

    i = 0;
    do {
      c = fgetc(file);
      if (c == EOF) {
        res = EOF;
        break;
      }
      wikiName[i] = c;
      i++;
    }
    while (c != '\n');

    wikiName[i - 1] = '\0';

//    res = fscanf(file, "%s\n", &text);
//    res = fscanf(file, "%s\n", &wikiName);
   res = fscanf (file, "%s\n", &font);
   res = fscanf (file, "%d\n\n", &myTxt.size);
   if (res == EOF)
    {
     printf ("Found EOF\n");
     break; // EOF = End Of File. Quit the loop.
    }
   if (res)
    {
     myTxt.textLine.assign (text);
      myTxt.wikiName.assign(wikiName);
     myTxt.fontPath.assign (font);
     textList.push_back (myTxt);
    }
  }
 fclose (file);
 return true;
}

void
ResObj::loadText (char * filePath, int screenWidth, int screenHeight)
{
 /* Initialize the FreeType2 library */
 if (FT_Init_FreeType (&ft))
  {
   cerr << "Could not init freetype library" << endl;
  }

//	cout << "TextObject Constructor Init font library " << endl;

 // Load all texts from file
 loadTextFile (filePath);
  for (auto l : textList) {
    TRACE_DEBUG("Text=%s, wiki=%s, font=%s, size=%d", l.textLine.c_str(), l.wikiName.c_str(), l.fontPath.c_str(), l.size);
  }
 cout << "Finished Loading text from file " << endl;
 int index = 1;
 for (auto tList : textList)
  {
   const char *p;
   int size = tList.size;
   FT_Long fSize = 0;
   strcpy (text, tList.textLine.c_str ());
   fontBuffer = loadFile (tList.fontPath.c_str (), &fSize);
//		std::cout << "loadFile finished" << std::endl;
   float sx = 2.0 / screenWidth;
   float sy = 2.0 / screenHeight;
   x = 0.0f;
//   y = 0.1 - 1 * sy;
   y = 0.0f;

   FT_Face face;
   FT_Face face2;
   GLuint texture;
   GLuint vbo;
   txtObjArray[index].width = 0;
   float first_width = 0;
   bool first_width_flag = true;
   for (p = text; *p; p++)
    {
     if (int err = FT_New_Memory_Face (ft, (const FT_Byte*) fontBuffer, fSize,
                                       0, &face2))
      {
       cout << "FT_New_Memory_Face failed with error code=" << err << endl;
      }
     FT_Set_Pixel_Sizes (face2, 0, size);
     if (FT_Load_Char (face2, *p, FT_LOAD_RENDER))
      {
       //      continue;
      }
     txtObjArray[index].width += 0.70 * face2->glyph->bitmap.width * sx;
//      txtObjArray[index].width += face->glyph->bitmap_left * sx;
     txtObjArray[index].width += 0.70
       * (0.01f + (face2->glyph->advance.x >> 6) * sx);
//      if (first_width_flag)
//      {
//        first_width_flag = false;
//        txtObjArray[index].width += face2->glyph->bitmap.width * sx;
//      }
    }
    txtObjArray[index].name = tList.textLine;
    txtObjArray[index].wikiName = tList.wikiName;
   x = -txtObjArray[index].width / 2;

   for (p = text; *p; p++)
    {
//		  y = (face->glyph->bitmap.rows * sy)/2;
//		  y = (face->glyph->advance.y >> 6) * sy;
     /* Try to load and render the character */
     if (int err = FT_New_Memory_Face (ft, (const FT_Byte*) fontBuffer, fSize,
                                       0, &face))
      {
       cout << "FT_New_Memory_Face failed with error code=" << err << endl;
      }
     FT_Set_Pixel_Sizes (face, 0, size);

     if (FT_Load_Char (face, *p, FT_LOAD_RENDER))
      {
       //			continue;
      }
//			 y = (face->glyph->bitmap.rows * sy)/2;
     glGenTextures (1, &texture);
//			getText_tex((ObjectType)index).push_back(texture);
     txtObjArray[index].text_tex.push_back (texture);
//			text_tex[index].push_back(texture);
     glBindTexture (GL_TEXTURE_2D, texture);

     /* We require 1 byte alignment when uploading texture data */
     glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

     glTexImage2D (GL_TEXTURE_2D, 0, GL_R8, face->glyph->bitmap.width,
                   face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                   face->glyph->bitmap.buffer);

     /* Clamping to edges is important to prevent artifacts when scaling */
     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

     /* Linear filtering usually looks best for text */
     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     //				FT_GlyphSlot tmp_g = new FT_GlyphSlot(g);
//			cout << "TextObject Constructor: push new face into list" << endl;

     float x2 = x + face->glyph->bitmap_left * sx;
     float y2 = -y - face->glyph->bitmap_top * sy;
     float w = face->glyph->bitmap.width * sx;
     float h = face->glyph->bitmap.rows * sy;
//			txtObjArray[index].width += w;

     point box[4] =
      {
       { x2, -y2, 0, 0 },
       { x2 + w, -y2, 1, 0 },
       { x2, -y2 - h, 0, 1 },
       { x2 + w, -y2 - h, 1, 1 }, };
     glGenBuffers (1, &vbo);
//			getText_vbo((ObjectType)index).push_back(vbo);
     txtObjArray[index].text_vbo.push_back (vbo);
//			text_vbo[index].push_back(vbo);
     glBindBuffer (GL_ARRAY_BUFFER, vbo);
     glBufferData (GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
//			vbo_index++;
//			cout << "vbo_index=" << vbo_index << endl;

     x += 0.01f + (face->glyph->advance.x >> 6) * sx;
//			txtObjArray[index].width += 0.01f + (face->glyph->advance.x >> 6) * sx;
//	EPEBROR testing to remove this line 21 aug 2016		y += (face->glyph->advance.y >> 6) * sy;
//			y = (face->glyph->advance.y >> 6) * sy;

     //			boxes.push_back(box);
     //			faces.push_back(face);
    }
   index++;
   //		cout << "faces size:" << faces.size() << endl;
  }
 free (fontBuffer);
}

unsigned char *
ResObj::loadFile (std::string fileName, long *count_size)
{
 FILE *fh;
 unsigned char *buffer;

 cout << "LoadFile: " << fileName << endl;
 fh = fopen (fileName.c_str (), "rb");
 if (fh == nullptr)
  {
   std::cout << "Cannot open file";
   exit(1);
  }

 // obtain file size:
 fseek (fh, 0, SEEK_END);
 int lSize = ftell (fh);
 if (lSize == -1) {
   std::cout << "Error: ftell returned -1, a failure occurred\n";
 }
 rewind (fh);
 // allocate memory to contain the whole file:
 buffer = (unsigned char*) malloc (sizeof(unsigned char) * lSize);
 if (buffer == NULL)
  {
   std::cout << "Cannot allocate memory of size = " << sizeof(unsigned char) * lSize <<  " with malloc\n";
   fputs ("Memory error", stderr);

   exit (2);
  }

 // copy the file into the buffer:
 size_t result = fread (buffer, 1, lSize, fh);
 if (result != lSize)
  {
   fputs ("Reading error", stderr);
   exit (3);
  }
 /* the whole file is now loaded in the memory buffer. */

 *count_size = lSize;

 // terminate
 fclose (fh);
 return buffer;
}

void
ResObj::saveScene (const char * file_path, list<std::string> *objList)
{
 static int no_of_files = 1;
 FILE * file;

 file = fopen (file_path, "w");
 for (std::list<std::string>::iterator it = objList->begin ();
   it != objList->end (); ++it)
  {
   fprintf (file, "%s", it->c_str ());
  }
 fclose (file);
}

void
ResObj::loadScene (const char * file_path, list<std::string> *objList)
{
 FILE * file;

 int scanned = 0;
 file = fopen (file_path, "r");
 do
  {
   char buf[256];
   scanned = fscanf (file, "%s", &buf);
   if (scanned == 1)
    {
     objList->push_back (buf);
    }
  }
 while (scanned > 0);
}

list<GLuint> ResObj::getText_vbo (ObjectType obj) const
{
 return txtObjArray[obj - 1000].text_vbo;
//	return txtObjArray[obj].text_vbo;
}

list<GLuint>
ResObj::getText_tex (ObjectType obj) const
{
//	return txtObjArray[obj - 1000].text_tex;
 return txtObjArray[obj].text_tex;
}

void
VertexBoneData::AddBoneData (GLuint BoneID, float Weight)
{
 for (GLuint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++)
  {
   SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM,
                "AddBoneData: Weights[%d]=%f, Weight=%f", i, Weights[i],
                Weight);
   if (Weights[i] == 0.0)
    {
     IDs[i] = BoneID;
     Weights[i] = Weight;
     return;
    }
  }
  TRACE_WARN("VertexBoneData::AddBoneData, we should NOT get here. BoneID = %d, Weight = %f, ARRA_SIZE_IN_ELEMENTS(IDs)=%d",
       BoneID, Weight, ARRAY_SIZE_IN_ELEMENTS(IDs));

 // should never get here - more bones than we have space for
// PETER: commented out,  assert(0);
//  assert(0);
}

void
ResObj::LoadBones (unsigned int meshCount, const aiMesh* pMesh, obj* mesh,
                   ObjectType objType, int BaseVertex)
{
 SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "ENTER ResObj::LoadBones");
 for (GLuint i = 0; i < pMesh->mNumBones; i++)
  {
   GLuint BoneIndex = 0;
   string BoneName (pMesh->mBones[i]->mName.data);

   if (mesh->m_BoneMapping.find (BoneName) == mesh->m_BoneMapping.end ())
    {
     SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM,
                  "ResObj::LoadBones: bone %d=%s, no of bones in pMesh[%d]:%d",
                  i, BoneName.c_str (), meshCount, pMesh->mNumBones);
     BoneIndex = mesh->m_NumBones;
     mesh->m_NumBones++;
     SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "ResObj::LoadBones: BoneIndex=%d",
                  BoneIndex);
     BoneInfo bi;
     bi.BoneOffset =
      {
        {pMesh->mBones[i]->mOffsetMatrix.a1, pMesh->mBones[i]->mOffsetMatrix.a2, pMesh->mBones[i]->mOffsetMatrix.a3, pMesh->mBones[i]->mOffsetMatrix.a4},
        {pMesh->mBones[i]->mOffsetMatrix.b1, pMesh->mBones[i]->mOffsetMatrix.b2, pMesh->mBones[i]->mOffsetMatrix.b3, pMesh->mBones[i]->mOffsetMatrix.b4},
        {pMesh->mBones[i]->mOffsetMatrix.c1, pMesh->mBones[i]->mOffsetMatrix.c2, pMesh->mBones[i]->mOffsetMatrix.c3, pMesh->mBones[i]->mOffsetMatrix.c4},
        {pMesh->mBones[i]->mOffsetMatrix.d1, pMesh->mBones[i]->mOffsetMatrix.d2, pMesh->mBones[i]->mOffsetMatrix.d3, pMesh->mBones[i]->mOffsetMatrix.d4},
      };
     mesh->m_BoneInfo.push_back (bi);
     mesh->m_BoneMapping[BoneName] = BoneIndex;
    }
   else
    {
     BoneIndex = mesh->m_BoneMapping[BoneName];
    }
   for (GLuint j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
    {
     GLuint VertexID = BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
     float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
     mesh->bones[VertexID].AddBoneData (BoneIndex, Weight);
    }
  }
 for (std::pair<std::string, GLuint> bone : mesh->m_BoneMapping)
  {
   SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM,
                "ResObj::LoadBones: boneName %s, index:%d", bone.first.c_str (),
                bone.second);
  }
}

GLuint Mesh::FindPosition (float AnimationTime, const aiNodeAnim* pNodeAnim)
{
 for (GLuint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
  {
   if (AnimationTime < (float) pNodeAnim->mPositionKeys[i + 1].mTime)
    {
     return i;
    }
  }

 assert(0);

 return 0;
}

GLuint
Mesh::FindRotation (float AnimationTime, const aiNodeAnim* pNodeAnim)
{
 assert(pNodeAnim->mNumRotationKeys > 0);

 for (GLuint i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
  {
   if (AnimationTime < (float) pNodeAnim->mRotationKeys[i + 1].mTime)
    {
     return i;
    }
  }

 assert(0);

 return 0;
}

GLuint
Mesh::FindScaling (float AnimationTime, const aiNodeAnim* pNodeAnim)
{
 assert(pNodeAnim->mNumScalingKeys > 0);

 for (GLuint i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
  {
   if (AnimationTime < (float) pNodeAnim->mScalingKeys[i + 1].mTime)
    {
     return i;
    }
  }

 assert(0);

 return 0;
}

void
Mesh::CalcInterpolatedPosition (aiVector3D& Out, float AnimationTime,
                                const aiNodeAnim* pNodeAnim)
{
 if (pNodeAnim->mNumPositionKeys == 1)
  {
   Out = pNodeAnim->mPositionKeys[0].mValue;
   return;
  }

 GLuint PositionIndex = FindPosition (AnimationTime, pNodeAnim);
 GLuint NextPositionIndex = (PositionIndex + 1);
 assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
 float DeltaTime = (float) (pNodeAnim->mPositionKeys[NextPositionIndex].mTime
   - pNodeAnim->mPositionKeys[PositionIndex].mTime);
 float Factor = (AnimationTime
   - (float) pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
 assert(Factor >= 0.0f && Factor <= 1.0f);
 const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
 const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
 aiVector3D Delta = End - Start;
 Out = Start + Factor * Delta;
 // PEB: added below in order to make him move on the same spot
  Out = pNodeAnim->mPositionKeys[0].mValue;
}

void
Mesh::CalcInterpolatedRotation (aiQuaternion& Out, float AnimationTime,
                                const aiNodeAnim* pNodeAnim)
{
 // we need at least two values to interpolate...
 if (pNodeAnim->mNumRotationKeys == 1)
  {
   Out = pNodeAnim->mRotationKeys[0].mValue;
   return;
  }

 GLuint RotationIndex = FindRotation (AnimationTime, pNodeAnim);
 GLuint NextRotationIndex = (RotationIndex + 1);
 assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
 float DeltaTime = (float) (pNodeAnim->mRotationKeys[NextRotationIndex].mTime
   - pNodeAnim->mRotationKeys[RotationIndex].mTime);
 float Factor = (AnimationTime
   - (float) pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
 assert(Factor >= 0.0f && Factor <= 1.0f);
 const aiQuaternion& StartRotationQ =
   pNodeAnim->mRotationKeys[RotationIndex].mValue;
 const aiQuaternion& EndRotationQ =
   pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
 aiQuaternion::Interpolate (Out, StartRotationQ, EndRotationQ, Factor);
 Out = Out.Normalize ();
}

void
Mesh::CalcInterpolatedScaling (aiVector3D& Out, float AnimationTime,
                               const aiNodeAnim* pNodeAnim)
{
 if (pNodeAnim->mNumScalingKeys == 1)
  {
   Out = pNodeAnim->mScalingKeys[0].mValue;
   return;
  }

 GLuint ScalingIndex = FindScaling (AnimationTime, pNodeAnim);
 GLuint NextScalingIndex = (ScalingIndex + 1);
 assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
 float DeltaTime = (float) (pNodeAnim->mScalingKeys[NextScalingIndex].mTime
   - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
 float Factor = (AnimationTime
   - (float) pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
 assert(Factor >= 0.0f && Factor <= 1.0f);
 const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
 const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
 aiVector3D Delta = End - Start;
 Out = Start + Factor * Delta;
}

void
Mesh::ReadNodeHeirarchy (float AnimationTime, const aiNode* pNode,
                         const glm::mat4& ParentTransform)
{
//  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "ENTER Mesh::ReadNodeHeirarchy");
 string NodeName (pNode->mName.data);

 const aiAnimation* pAnimation = resScene->mAnimations[0];

 glm::mat4 NodeTransformation =
  {
   { pNode->mTransformation.a1, pNode->mTransformation.a2,
     pNode->mTransformation.a3, pNode->mTransformation.a4 },
   { pNode->mTransformation.b1, pNode->mTransformation.b2,
     pNode->mTransformation.b3, pNode->mTransformation.b4 },
   { pNode->mTransformation.c1, pNode->mTransformation.c2,
     pNode->mTransformation.c3, pNode->mTransformation.c4 },
   { pNode->mTransformation.d1, pNode->mTransformation.d2,
     pNode->mTransformation.d3, pNode->mTransformation.d4 } };

 const aiNodeAnim* pNodeAnim = FindNodeAnim (pAnimation, NodeName);
//  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "ENTER Mesh::ReadNodeHeirarchy 2");

 if (pNodeAnim)
  {
   // Interpolate scaling and generate scaling transformation matrix
   aiVector3D Scaling;
   CalcInterpolatedScaling (Scaling, AnimationTime, pNodeAnim);
   glm::mat4 ScalingM (1.0f);
   glm::vec3 scaling = glm::vec3 (Scaling.x, Scaling.y, Scaling.z);
   ScalingM = glm::scale (ScalingM, scaling);

   // Interpolate rotation and generate rotation transformation matrix
   aiQuaternion RotationQ;

   CalcInterpolatedRotation (RotationQ, AnimationTime, pNodeAnim);
   glm::mat4 RotationM =
    {
     { RotationQ.GetMatrix ().a1, RotationQ.GetMatrix ().a2,
       RotationQ.GetMatrix ().a3, 0.0f },
     { RotationQ.GetMatrix ().b1, RotationQ.GetMatrix ().b2,
       RotationQ.GetMatrix ().b3, 0.0f },
     { RotationQ.GetMatrix ().c1, RotationQ.GetMatrix ().c2,
       RotationQ.GetMatrix ().c3, 0.0f },
     { 0.0f, 0.0f, 0.0f, 1.0f } };

   // Interpolate translation and generate translation transformation matrix
   aiVector3D Translation;
   CalcInterpolatedPosition (Translation, AnimationTime, pNodeAnim);
   glm::mat4 TranslationM (1.0f);

//    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "Mesh::ReadNodeHeirarchy Translation.x=%.1f, Translation.y=%.1f, Translation.z=%.1f", Translation.x, Translation.y, Translation.z);

   TranslationM = glm::translate (
     glm::transpose (TranslationM),
     glm::vec3 (Translation.x, Translation.y, Translation.z));

   // Combine the above transformations
   NodeTransformation = TranslationM * glm::transpose (RotationM) * ScalingM;
   NodeTransformation = glm::transpose (NodeTransformation);
  }

 glm::mat4 GlobalTransformation = glm::transpose (
   glm::transpose (ParentTransform) * glm::transpose (NodeTransformation));
//  glm::mat4 GlobalTransformation = NodeTransformation;
 if (mesh.size () > 0)
  {
   for (unsigned int meshCount = 0; meshCount < mesh.size (); meshCount++)
    {
     if (mesh[0]->m_BoneMapping.find (NodeName)
       != mesh[0]->m_BoneMapping.end ())
      {
       GLuint BoneIndex = mesh[0]->m_BoneMapping[NodeName];
       mesh[0]->m_BoneInfo[BoneIndex].FinalTransformation = glm::transpose (
         glm::transpose (GlobalTransformation) * glm::transpose (mesh[0]->m_BoneInfo[BoneIndex].BoneOffset));
      }
    }
  }
 else
  {
   SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM,
                "Mesh::ReadNodeHeirarchy, ERROR, meshcount > 0: meshCount=%d",
                mesh.size ());
   exit (1);
  }

//  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "Mesh::ReadNodeHeirarchy - Before 2nd for loop, mNumChildren = %d", pNode->mNumChildren);
 if (pNode->mNumChildren > 0)
  {
   for (GLuint i = 0; i < pNode->mNumChildren; i++)
    {
//      SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "Mesh::ReadNodeHeirarchy Inside for-loop, i = %d, mNumChildren = %d", i, pNode->mNumChildren);

     ReadNodeHeirarchy (AnimationTime, pNode->mChildren[i],
                        GlobalTransformation);
    }
  }
//  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "END of Mesh::ReadNodeHeirarchy");

}

float
Mesh::BoneTransform (float TimeInSeconds, vector<glm::mat4>& Transforms)
{
 float AnimationTime;
//  SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "ENTER Mesh::BoneTransform");

 glm::mat4 Identity (1.0f);

//  printf("Identity = { {%.2f,%.2f,%.2f,%.2f},", Identity[0][0], Identity[0][1], Identity[0][2], Identity[0][3]);
//  printf("Identity = {%.2f,%.2f,%.2f,%.2f},", Identity[1][0], Identity[1][1], Identity[1][2], Identity[1][3]);
//  printf("Identity = {%.2f,%.2f,%.2f,%.2f},", Identity[2][0], Identity[2][1], Identity[2][2], Identity[2][3]);
//  printf("Identity = {%.2f,%.2f,%.2f,%.2f}}", Identity[3][0], Identity[3][1], Identity[3][2], Identity[3][3]);
 if (resScene != nullptr)
  {
   if (resScene->mNumAnimations > 0)
    {
     SDL_LogInfo (
       SDL_LOG_CATEGORY_CUSTOM,
       "\nMesh::BoneTransform - mNumAnimations=%d > 0, duration[sec]=%f, tickspersec=%f",
       resScene->mNumAnimations,
       resScene->mAnimations[0]->mDuration
         / resScene->mAnimations[0]->mTicksPerSecond,
       resScene->mAnimations[0]->mTicksPerSecond);

     float TicksPerSecond = (float) (
       resScene->mAnimations[0]->mTicksPerSecond != 0 ?
         resScene->mAnimations[0]->mTicksPerSecond : 25.0f);
     float TimeInTicks = TimeInSeconds * TicksPerSecond;
     AnimationTime = fmod (TimeInTicks,
                           (float) resScene->mAnimations[0]->mDuration);
     SDL_LogInfo (
       SDL_LOG_CATEGORY_CUSTOM,
       "Mesh::BoneTransform - before ReadNodeHeirarchy, AnimationTime=%f",
       AnimationTime);

     ReadNodeHeirarchy (AnimationTime, resScene->mRootNode, Identity);
//      SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "Mesh::BoneTransform - after ReadNodeHeirarchy");

     int numBones = 0;
     for (unsigned int nb = 0; nb < mesh.size (); nb++)
      {
       numBones += mesh[nb]->m_NumBones;
      }

     SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "Mesh::BoneTransform: numBones = %d",
                  numBones);
     Transforms.resize (numBones);
     int index = 0;
     for (int nb = 0; nb < mesh.size (); nb++)
      {
       for (unsigned int k = 0; k < mesh[nb]->m_BoneInfo.size (); k++)
        {

//          for (int u = 0; u < 4; u++) {
//            for (int v = 0; v < 4; v++) {
//              SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "Mesh::BoneTransform index[%d]FinalTransformation[%d][%d]=%.3f", index, u, v, mesh[nb]->m_BoneInfo[k].FinalTransformation[u][v]);
//            }
//          }
         //          Transforms[nb * mesh[nb]->m_BoneInfo.size() + k] = mesh[nb]->m_BoneInfo[k].FinalTransformation;
         Transforms[index] = mesh[nb]->m_BoneInfo[k].FinalTransformation;
         index++;
        }
      }
//      SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "END of Mesh::BoneTransform, Transforms.size()=%d", Transforms.size());
    }
  }
 else
  {
   SDL_LogInfo (SDL_LOG_CATEGORY_CUSTOM, "resScene is null");
  }
 return AnimationTime;
}

const aiNodeAnim*
Mesh::FindNodeAnim (const aiAnimation* pAnimation, const string NodeName)
{
 for (GLuint i = 0; i < pAnimation->mNumChannels; i++)
  {
   const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

   if (string (pNodeAnim->mNodeName.data) == NodeName)
    {
     return pNodeAnim;
    }
  }

 return NULL;
}

//void ResObj::SetBoneTransform(uint Index, glm::mat4& Transform)
//{
//
//
////  SDL_Log("Scene::SetBoneTransform Input parameters : index=%d, MAX_BONES=%d", Index, MAX_BONES);
//
//  assert(Index < MAX_BONES);
//  const GLfloat m[4][4] = { { Transform[0][0], Transform[0][1], Transform[0][2], Transform[0][3] }, { Transform[1][0], Transform[1][1], Transform[1][2], Transform[1][3] }, { Transform[2][0], Transform[2][1], Transform[2][2], Transform[2][3] }, {
//      Transform[3][0], Transform[3][1], Transform[3][2], Transform[3][3] } };
//
//  //Transform.Print();
//  glUniformMatrix4fv(BoneLocationID[Index], 1, GL_TRUE, (const GLfloat*) m);
//
//}

