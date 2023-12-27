#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <assimp/scene.h>


bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals,
	bool useDDS
);

bool loadOBJWithAssimp(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

void loadObj(const std::string& pFile, aiScene* assimp_scene);


#endif
