/*
 * ResObj.h
 *
 *  Created on: Apr 21, 2014
 *      Author: peter
 */

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include "../inc/objloader.hpp"
#include "../inc/vboindexer.hpp"
#include "../inc/LPObject.h"
#include <list>

#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H

#include <string.h>
#include <iostream>
#include <assimp/scene.h>

#include "../inc/SDL_base.h"
#include "../inc/LuaIf.h"

#ifndef RESOBJ_H_
#define RESOBJ_H_

#define SOLVED_ID 22200
#define NO_ID 22201

#define NUM_BONES_PER_VERTEX 4
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

//static const uint MAX_BONES = 100;

using namespace std;

enum TextureName {
 tx_undefined = 0,
 tx_wood = 1,
 tx_ice = 2,
 tx_red_floor = 3,
 tx_wall = 4,
 tx_wall_2x32x32 = 5,
 tx_glykolysen = 6,
 tx_glykolysen_plane = 7,
 tx_glykolysen_text = 8,
 tx_arrow_red = 9,
 tx_plane_skar = 10,
 tx_dirt = 11,
 tx_zombie = 12,
 tx_sniper = 13,
 tx_sandstone = 14,
 tx_sandstone3 = 15,
 tx_sandstone4 = 16,
 tx_sandstone5 = 17,
 tx_sandstone5_normal = 18,
 tx_sandstone5_specular = 19,
 tx_question2 = 20,
 tx_blue24 = 21,
 tx_skybox = 22,

};



struct BoneInfo {
  glm::mat4 BoneOffset;
  glm::mat4 FinalTransformation;


  BoneInfo()
  {
    BoneOffset = {
      { 0.0f, 0.0f, 0.0f, 0.0f},
      { 0.0f, 0.0f, 0.0f, 0.0f},
      { 0.0f, 0.0f, 0.0f, 0.0f},
      { 0.0f, 0.0f, 0.0f, 0.0f}};


    FinalTransformation = {
      { 0.0f, 0.0f, 0.0f, 0.0f},
      { 0.0f, 0.0f, 0.0f, 0.0f},
      { 0.0f, 0.0f, 0.0f, 0.0f},
      { 0.0f, 0.0f, 0.0f, 0.0f}};
  }

};

struct VertexBoneData {
  GLuint IDs[NUM_BONES_PER_VERTEX];
  GLfloat Weights[NUM_BONES_PER_VERTEX];

  VertexBoneData()
  {
    ZERO_MEM(IDs);
    ZERO_MEM(Weights);
  }

  void AddBoneData(GLuint BoneID, float Weight);
};

struct _object {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
  std::vector<GLuint> indices;
  std::vector<VertexBoneData> bones;
	GLfloat meshColor[4];

//  map<string, GLuint> m_BoneMapping; // maps a bone name to its index
//  GLuint m_NumBones;
//  vector<BoneInfo> m_BoneInfo;
//  glm::mat4 m_GlobalInverseTransform;
//
  map<string, GLuint> m_BoneMapping; // maps a bone name to its index
  GLuint m_NumBones;
  GLuint m_NumAnimations;
  vector<BoneInfo> m_BoneInfo;


//  GLuint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
//  GLuint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
//  GLuint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
//  void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//  void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//  void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
//  void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);
//  const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
//public:
//  void BoneTransform(float TimeInSeconds, vector<glm::mat4>& Transforms);

	};

struct _buffer {
  GLuint vertices; //identifies the generated buffer that holds vertices
  GLuint uvs;      //identifies the generated buffer that holds uvs
  GLuint normals;  //identifies the generated buffer that holds normals
  GLuint indices;  //identifies the generated buffer that holds indices
  GLuint bones;  //identifies the generated buffer that holds bones
  GLuint sizeOfVertices;
  GLuint sizeOfIndices;
  GLfloat meshColor[4];
  glm::vec3 trans;
  };

typedef struct _object obj;
typedef struct _buffer buffer;
typedef struct _vertex_bone_data vertexBoneData;

//std::vector<obj> MeshList;
//std::vector<buffer> bufferList;


class Mesh {
public:
  std::vector<obj*> mesh;
  std::vector<buffer*> buf;
  std::string name;
  std::string wikiName;
  // Moved the bones vector in here
//  std::vector<VertexBoneData> bones;

  GLuint bonesBuffer;  //identifies the generated buffer that holds bones

  // every obj is a singleMesh and the vector of singleMesh:es make up the whole object
  // bone data
//  map<string, GLuint> m_BoneMapping; // maps a bone name to its index
//  GLuint m_NumBones;
//  vector<BoneInfo> m_BoneInfo;
  glm::mat4 m_GlobalInverseTransform;

//    const aiScene* m_pScene;
  const aiScene * resScene = nullptr;

  Mesh()
  {
//      m_pScene = nullptr;
//    m_NumBones = 0;
  }

  GLuint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
  GLuint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
  GLuint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
  void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
  void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
  void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
  void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);
  const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
public:
  float BoneTransform(float TimeInSeconds, vector<glm::mat4>& Transforms);
};



struct _txtObj {
	list<GLuint> text_tex;
	list<GLuint> text_vbo;
	float width;
  std::string name;
  std::string wikiName;
};

typedef struct _txtObj txtObj;

struct Txt {
	string textLine;
  string wikiName;
	string fontPath;
	int size = 999;
};

using std::list;

enum ColorStates {
  S_DEFAULT,
  S_RED,
  S_GREEN,
  S_BLUE,
  S_MAGENTA
};

enum GamePlay {
  EASY,
  MEDIUM,
  HARD,
  HARD_CORE,
  HURT_ME
};


enum lp_sound{
	SoundX,
	SoundO,
	Soundwin,
	Soundloose,
	concreteStep,
        StepTap, SonnyStep, EllbellekcStep,
        horror,
};

enum lp_class{
	c_FallingCube = 0,
	c_Ball = 2000,
	c_Creature = 4000,
	c_IceCube = 6000,
	c_Sniper = 8000,
	c_WallCube = 10000,
	c_WooddenCube = 12000,
	c_WooddenCube2 = 14000,
	c_glucose = 16000,
	c_wall = 18000,
	c_line = 20000,
	c_text = 22000,
	c_plane = 24000,
	c_arrow = 26000,
	c_sign = 28000,
	c_plate = 30000,
	c_lightSource = 32000,
	c_menuItem = 34000,
	c_menuContainer = 36000,
	c_cell = 38000,
  c_skybox = 40000,
  c_maze_floor_3x1 = 50000,
  c_maze_floor_3x5 = 51000,
  c_maze_floor_3x10 = 52000,
  c_maze_floor_3x3 = 53000,
  c_maze_floor_5x5 = 54000,
  c_maze_floor_3x20 = 55000,
  c_maze_door_3x2 = 56000,
  c_maze_door_x_3x3 = 57000,
  c_maze_door_y_3x3 = 58000,
  c_winning_area = 59000,
  c_zombie = 60000,
  c_molecule_spot = 61000,
  c_text_spot = 62000,
};

static int lp_falling_cube = c_FallingCube;
static int lp_creature = c_Creature;
static int lp_ball = c_Ball;
static int lp_ice_cube = c_IceCube;
static int lp_sniper = c_Sniper;
static int lp_wall_cube = c_WallCube;
static int lp_woodden_cube = c_WooddenCube;
static int lp_woodden_cube2 = c_WooddenCube2;
static int lp_wall = c_wall;
static int lp_glucose = c_glucose;
static int lp_line = c_line;
static int lp_text = c_text;
static int lp_plane = c_plane;
static int lp_arrow = c_arrow;
static int lp_sign = c_sign;
static int lp_plate = c_plate;
static int lp_lightSource = c_lightSource;
static int lp_menuContainer = c_menuContainer;
static int lp_cell = c_cell;
static int lp_skybox = c_skybox;
static int lp_maze_floor_3x1 = c_maze_floor_3x1;
static int lp_maze_floor_3x5 = c_maze_floor_3x5;
static int lp_maze_floor_3x10 = c_maze_floor_3x10;
static int lp_maze_floor_3x3 = c_maze_floor_3x3;
static int lp_maze_floor_5x5 = c_maze_floor_5x5;
static int lp_maze_floor_3x20 = c_maze_floor_3x20;
static int lp_maze_door_3x2 = c_maze_door_3x2;
static int lp_maze_door_x_3x3 = c_maze_door_x_3x3;
static int lp_maze_door_y_3x3 = c_maze_door_y_3x3;
static int lp_winning_area = c_winning_area;
static int lp_zombie = c_zombie;
static int lp_molecule_spot = c_molecule_spot;
static int lp_text_spot = c_text_spot;

enum ObjectType {
cube = 0,
	creature0 = 1,
	creature1 = 2,
	creature2 = 3,
	creature3 = 4,
	creature4 = 5,
	creature5 = 6,
	creature6 = 7,
	creature7 = 8,
	creature8 = 9,
	creature9 = 10,
	creature10 = 11,
	creature11 = 12,
	creature12 = 13,
	creature13 = 14,
	creature14 = 15,
	creature15 = 16,
	creature16 = 17,
	creature17 = 18,
	creature18 = 19,
	creature19 = 20,
	creature20 = 21,
	creature21 = 22,
	creature22 = 23,
	creature23 = 24,
	boy = 25,
	landscape = 26,
	sniper1 = 27,
	sniper2 = 28,
	sniper3 = 29,
	sniper4 = 30,
	sniper5 = 31,
	sniper6 = 32,
	sniper7 = 33,
	sniper8 = 34,
	sniper9 = 35,
	sniper10 = 36,
	sniper11 = 37,
	sniper12 = 38,
	sniper13 = 39,
	sniper14 = 40,
	sniper15 = 41,
	sniper16 = 42,
	sniper17 = 43,
	sniper18 = 44,
	sniper19 = 45,
	sniper20 = 46,
	sniper21 = 47,
	sniper22 = 48,
	sniper23 = 49,
	sniper24 = 50,
	sniper25 = 51,
	sniper26 = 52,
	sniper27 = 53,
	sniper28 = 54,
	sniper29 = 55,
	pilot = 56,
	cylinder = 57,
	ball = 58,
	box = 59,
	glucose = 60,
	picture = 61,
	glyphs = 62,
	wall = 63,
	wall_2x32x32 = 64,
	plane = 65,
	arrow = 66,
	arrow2 = 67,
	mitochondria = 68,
	dna = 69,
	skybox = 70,
	ghost = 71,
	plate = 72,
	arrow3 = 73,
	arrow_rectangle_up_single = 74,
	arrow_rectangle_down_single = 75,
	arrow_rectangle_up_double = 76,
	arrow_rectangle_down_single1 = 77,
	arrow_rectangle_down_up = 78,
	arrow_rectangle_down_side = 79,
	arrow_rectangle_down_up_45 = 80,
	arrow_rectangle_down_up_45_1 = 81,
	arrow_rectangle_down_up_bent = 82,
	arrow_rectangle_down_side_long = 83,
	arrow_rectangle_down_up_bent_long = 84,
	arrow_rectangle_down_up_halfside_bent = 85,
	glucose6_phosphate = 86,
	hexokinase = 87,
	phosphofructokinase = 88,
	phospho_glycerate = 89,
	fructose6_phosphate = 90,
	fructose1_6_bisphosphate = 91,
	glyceraldehyde_3_phosphate = 92,
	alpha_D_glucopyranose = 93,
	dihydroxyacetone_phosphate = 94,
	one_three_bisphosphoglycerate = 95,
	three_phosphoglycerate = 96,
	two_phosphoglycerate = 97,
	phosphoenolpyruvate = 98,
	pyruvate = 99,
	atp = 100,
	animal_cell = 201,
  phosphoglucoseisomerase = 202,
  enolase = 203,
	line = 301,

	zombie = 101,
  maze_floor_3x1 = 102,
  maze_floor_3x5 = 103,
  maze_floor_3x10 = 104,
  maze_floor_3x3 = 105,
  maze_floor_5x5 = 106,
  maze_floor_3x20 = 107,
  maze_door_3x2 = 108,
  maze_door_x_3x3 = 109,
  maze_door_y_3x3 = 110,
  winning_area = 111,
  coordinate_lines = 112,
  molecule_spot = 113,
  text_spot = 114,

	// Below values are only used for text,
	// the values will actually be changed to "x - 1000" before being used
	// this way the index will still fit inside a vector of 128 or 256 elements.

	txt_1 = 1001,
	txt_2 = 1002,
	txt_3 = 1003,
	txt_4 = 1004,
	txt_5 = 1005,
	txt_6  = 1006,
	txt_7  = 1007,
	txt_8  = 1008,
	txt_9  = 1009,
	txt_10  = 1010,
	txt_11  = 1011,
	txt_12  = 1012,
	txt_13  = 1013,
	txt_14  = 1014,
	txt_15  = 1015,
	txt_16  = 1016,
	txt_17  = 1017,
	txt_116 = 1116, // only because of GameLogic2 solution with menucontainers for ADP, ATP
	txt_117 = 1117, // only because of GameLogic2 solution with menucontainers for ADP, ATP
	txt_216 = 1216, // only because of GameLogic2 solution with menucontainers for ADP, ATP
	txt_217 = 1217, // only because of GameLogic2 solution with menucontainers for ADP, ATP
  txt_316 = 1316, // only because of GameLogic2 solution with menucontainers for ADP, ATP
  txt_317 = 1317, // only because of GameLogic2 solution with menucontainers for ADP, ATP
  txt_416 = 1416, // only because of GameLogic2 solution with menucontainers for ADP, ATP
  txt_417 = 1417, // only because of GameLogic2 solution with menucontainers for ADP, ATP
  txt_516 = 1516, // only because of GameLogic2 solution with menucontainers for ADP, ATP
  txt_517 = 1517, // only because of GameLogic2 solution with menucontainers for ADP, ATP
	txt_18  = 1018,
	txt_19  = 1019,
	txt_20  = 1020,
	txt_21  = 1021,
	txt_22  = 1022,
	txt_23  = 1023,
	txt_24  = 1024,
	txt_25  = 1025,
	txt_26  = 1026,
	txt_27  = 1027,
	txt_28  = 1028,
	txt_29  = 1029,
	txt_30  = 1030,
	txt_31  = 1031,
	txt_32  = 1032,
	txt_33  = 1033,
	txt_34  = 1034,

	// Solved:
	txt_35  = 1035,

	// numbers 0-9:
	txt_36  = 1036,
	txt_37  = 1037,
	txt_38  = 1038,
	txt_39  = 1039,
	txt_40  = 1040,
	txt_41  = 1041,
	txt_42  = 1042,
	txt_43  = 1043,
	txt_44  = 1044,
	txt_45  = 1045,
	txt_SELECT_OBJECT = 1046,
	txt_LESS = 1047,
	txt_MORE = 1048,
	txt_TITLE = 1049,
	txt_BIOMOLCRAFT = 1050,
	txt_Regulation_Qestion = 1051,
	txt_Glucose_6_phosphate = 1052,
	txt_Citrate = 1053,
	txt_AMP = 1054,
	txt_Alanin = 1055,
	txt_Regulation_phosphofructokinase_Qestion = 1056,
	txt_Regulation_pyruvate_kinase_Qestion = 1057,


	// Undefined value
	undefined_object = 2051,
};

class ResObj {
public:
	ResObj();
	virtual ~ResObj();

	const aiScene* loadObj(const std::string& pFile);
	bool loadObjFiles();
  bool loadObjFilesMultiThreading();
  bool
  loadObjFiles_maze ();

  void LoadBones(unsigned int meshCount, const aiMesh* pMesh, obj* mesh, ObjectType objType, int BaseVertex);

	//void loadObjIntoBuffer();

	const std::vector<glm::vec3>& getNormals(ObjectType objType) const { return objArray[objType].normals; }
	void setNormals(const std::vector<glm::vec3>& normals, ObjectType objType) { this->objArray[objType].normals = normals; }
	GLuint getUvbuffer(ObjectType objType) const { return uvbuffer[objType]; }
	GLuint getUvbuffer(int objType) const { return uvbuffer[objType]; }
	void setUvbuffer(GLuint uvbuffer, ObjectType objType) { this->uvbuffer[objType] = uvbuffer; }
	const std::vector<glm::vec2>& getUvs(ObjectType objType) const { return objArray[objType].uvs; }
	void setUvs(const std::vector<glm::vec2>& uvs, ObjectType objType) { this->objArray[objType].uvs = uvs;}
	GLuint getVertexbuffer(ObjectType objType) const { return this->vertexbuffer[objType]; }
	GLuint getVertexbuffer(int objType) const { return this->vertexbuffer[objType]; }
	void setVertexbuffer(GLuint vertexbuffer, ObjectType objType) { this->vertexbuffer[objType] = vertexbuffer; }
	const std::vector<glm::vec3>& getVertices(ObjectType objType) const { return objArray[objType].vertices; }
	const std::vector<glm::vec3>& getVertices(int objType) const { return objArray[objType].vertices; }
	void setVertices(const std::vector<glm::vec3>& vertices, ObjectType objType) { this->objArray[objType].vertices = vertices; }
	GLuint getNormalbuffer(ObjectType objType) const { return normalbuffer[objType]; }
	GLuint getNormalbuffer(int objType) const { return normalbuffer[objType]; }
	GLuint getElementbuffer(int objType) const { return elementbuffer[objType]; }
	void setNormalbuffer(GLuint normalbuffer, ObjectType objType) { this->normalbuffer[objType] = normalbuffer; }
	void saveScene(const char * file_path, list<std::string> * objList);
	void loadScene(const char * file_path,  list<std::string> *objList);

  std::vector<buffer*> getMesh(ObjectType obj) const
  {
    return meshArray[obj].buf;
  }

	unsigned char * loadFile(std::string fileName, long *count_size);

	list<GLuint> getText_vbo(ObjectType obj) const;
	list<GLuint> getText_tex(ObjectType obj) const;

	bool loadTextFile(char *path);
	void loadText(char * filePath, int screenWidth, int screenHeight);


	int getNumIndices() const {
		return numIndices;
	}

	void setNumIndices(int numIndices) {
		this->numIndices = numIndices;
	}

  bool loadOBJWithAssimp(const char * path, ObjectType objType,
	                       Mesh& mesh);

	GLuint vertexbuffer[256];
	txtObj txtObjArray[256];

	GLfloat const black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat const transparent_black[4] = { 0.0f, 0.0f, 0.0f, .6f };
	GLfloat const gray[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat const dark_gray[4] = { 0.7f, 0.7f, 0.7f, 0.9f };
//	GLfloat const transparent_black[4] = { 0.0f, 0.0f, 0.0f, .3f };
	GLfloat const yellow[4] = { 1.0f, 1.0f, 0.0f, .5f };
	GLfloat const red[4] = { 1.0f, 0.0f, 0.0f, 0.1f };
	GLfloat const transparent_green[4] = { 0.f, 1.f, 0.f, 10.5f };
	GLfloat const green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat const white[4] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat const blue[4] = { .1f, .5f, .4f, 1.0f };

//	std::vector<buffer*> bufferArray[256];
  void loadStaticObjFiles(const char * objpath, ObjectType objType, const char* name, const char* wikiName);

//  void SetBoneTransform(uint Index, glm::mat4& Transform);

private:

	void loadActorObjFiles(const char * objpath, ObjectType objType, int stream_length);

//  void SetBoneTransform(uint Index, const glm::mat4& Transform);
	obj objArray[256];



	int objArray_length = 0;
	GLuint uvbuffer[256];
	GLuint normalbuffer[256];
	GLuint elementbuffer[256];
	unsigned char *fontBuffer;
	FT_Library ft;
	struct point {
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};
	char text[256];
	float x;
	float y;


	int numIndices;

	std::vector<unsigned int> indices;
	std::vector<glm::vec3> indexed_vertices[256];
	std::vector<glm::vec2> indexed_uvs[256];
	std::vector<glm::vec3> indexed_normals[256];


    int *logOutputPtr;

public:
  Mesh meshArray[256];
  const aiScene * resScene;
  vector<glm::mat4> Transforms;
//  GLuint BoneLocationID[MAX_BONES];
  LuaIf *luaIf = nullptr;
  list<struct Txt> textList;

};

#endif /* RESOBJ_H_ */

