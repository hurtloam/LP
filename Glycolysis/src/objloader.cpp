#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/material.h>

#include "../inc/objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals,
		bool useDDS
){
	//	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("loadOBJ: Impossible to open the file: %s! Are you in the right path ? See Tutorial 1 for details\n", path);
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );

			if (useDDS) {
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			}

			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			uvIndex[0] = 0;
			uvIndex[1] = 0;
			uvIndex[2] = 0;
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			//			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
			if (matches != 9){
				//			if (matches != 6){
				printf("File can't be read by our simple parser :-( Try exporting with other options, matches = %d\n", matches);
				return false;
			}
			//			printf("matches = %d\n", matches);
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);

	}

	return true;
}


//bool loadOBJWithAssimp(
//		const char * path,
//		std::vector<glm::vec3> & out_vertices,
//		std::vector<glm::vec2> & out_uvs,
//		std::vector<glm::vec3> & out_normals
//)
//{
//	printf("Enter function loadOBJWithAssimp, Loading OBJ file %s...\n", path);
//
//	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
//	std::vector<glm::vec3> temp_vertices;
//	std::vector<glm::vec2> temp_uvs;
//	std::vector<glm::vec3> temp_normals;
//
//	// Load the object from file
//	const aiScene * resScene;
//	//	loadObj(path, resScene);
//
//	/////////////////////////////////////////////////////////////////7
//	Assimp::Importer importer;
//	// And have it read the given file with some example postprocessing
//	// Usually - if speed is not the most important aspect for you - you'll
//	// propably to request more postprocessing than we do in this example.
//	resScene = importer.ReadFile( path,
//			aiProcess_CalcTangentSpace       |
//			aiProcess_Triangulate            |
//			aiProcess_JoinIdenticalVertices  |
//			aiProcess_SortByPType            |
//			aiProcess_FixInfacingNormals     //|
//			/*aiProcess_GenNormals*/);
//
//	// If the import failed, report it
//	if( !resScene)
//	{
//		std::cout << "ERROR ASSIMP FAILED: " << importer.GetErrorString() << std::endl;
//		resScene = NULL;
//		//	    return NULL;
//	}
//
//	std::cout << "loadObj method: Loaded object: " << path << std::endl;
//	std::cout << "number OF VERTICES: " << resScene->mMeshes[0]->mNumVertices << std::endl;
//	std::cout << "number OF FACES: " << resScene->mMeshes[0]->mNumFaces << std::endl;
//	/////////////////////////////////////////////////////////////////
//	for (int meshCount = 0; meshCount < resScene->mNumMeshes; meshCount++)
//	{
//		const aiMesh * paiMesh = resScene->mMeshes[meshCount];
//		std::cout << "Name: " << paiMesh->mName.C_Str() << ", Has Materials: " << resScene->HasMaterials() << std::endl;
//		if (resScene->HasMaterials())
//		{
//			std::cout << "MaterialIndex: " << paiMesh->mMaterialIndex << std::endl;
//
//			aiColor4D color;
//			aiMaterial* mtl = resScene->mMaterials[0];
//			aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &color);
//
//
//			std::cout << "Has Vertex Colors: " << paiMesh->HasVertexColors(0) << std::endl;
//			std::cout << "Colors: (" << color.r <<", " << color.g << ", " << color.b << ")" << std::endl;
//
//		}
//		printf("Number of Meshes=%d, number of vertices=%d\n", resScene->mNumMeshes, paiMesh->mNumVertices);
//
//
//		int iMeshFaces = paiMesh->mNumFaces;
//		printf("Number of Faces=%d\n",paiMesh->mNumFaces);
//		std::cout << "Face:numOfIndices= " << paiMesh->mFaces[0].mNumIndices << std::endl;
//		for (int j = 0; j < iMeshFaces; j++)
//		{
//			const aiFace& face = paiMesh->mFaces[j];
//			for(int k = 0; k < 3; k++)
//			{
//				glm::vec3 vertex = glm::vec3(paiMesh->mVertices[face.mIndices[k]].x, paiMesh->mVertices[face.mIndices[k]].y, paiMesh->mVertices[face.mIndices[k]].z);
//				if (paiMesh->HasTextureCoords(0))
//				{
//					glm::vec2 uv =	glm::vec2(paiMesh->mTextureCoords[0][face.mIndices[k]].x, paiMesh->mTextureCoords[0][face.mIndices[k]].y);
//					out_uvs     .push_back(uv);
//				}
//				else
//				{
//					glm::vec2 uv = glm::vec2(0.0f, 0.0f);
//					out_uvs.push_back(uv);
//				}
//
//				//			std::cout << "Face3, "<< std::endl;
//				if (paiMesh->HasNormals())
//				{
//					glm::vec3 normal = glm::vec3(paiMesh->mNormals[face.mIndices[k]].x, paiMesh->mNormals[face.mIndices[k]].y, paiMesh->mNormals[face.mIndices[k]].z);
//					out_normals .push_back(normal);
//				}
//				else
//				{
//					glm::vec3 normal = glm::vec3(1.0f, 1.0f, 1.0f);
//					out_normals .push_back(normal);
//				}
//				//			std::cout << "Face4, "<< std::endl;
//				out_vertices.push_back(vertex);
//			}
//		}
//	}
//	std::cout << "number of out_vertices="<< out_vertices.size()<< std::endl;
//	std::cout << "number of out_normals="<< out_normals.size()<< std::endl;
//	std::cout << "number of out_uvs="<< out_uvs.size()<< std::endl;
//	return true;
//}


