//#include "cSpriteRenderer.h"
//
//bool cSpriteRenderer::LoadModelFromFile(std::string name, char* file)
//{
//	cMesh * tempMesh = new cMesh;
//	std::ifstream fileInput(file);
//	if (!fileInput.fail())
//	{
//		fileInput.close();
//	}
//	else
//	{
//		printf("Couldn't open file.");
//		printf("%s\n", this->Importer.GetErrorString());
//		return false;
//	}
//
//	const aiScene * scene;
//	scene = Importer.ReadFile(file, aiProcessPreset_TargetRealtime_Quality);
//	if (!scene)
//	{
//		printf("%s\n", Importer.GetErrorString());
//		return false;
//	}
//
//	this->MapNameToScene[name] = scene;
//	return true;
//}
//
//void cSpriteRenderer::GenerateVAOandBuffers(std::string name)
//{
//	std::map<std::string, const aiScene*>::iterator iter;
//	for (iter = MapNameToScene.begin(); iter != MapNameToScene.end(); iter++)
//	{
//		for (int i = 0; i < iter->second->mNumMeshes; i++)
//		{
//			aiMesh * curMesh = iter->second->mMeshes[i];
//			cMesh* tempMesh = new cMesh;
//
//			if (curMesh->HasFaces())
//			{
//				tempMesh->Faces = new cTriangle[curMesh->mNumFaces];
//				for (int j = 0; j < curMesh->mNumFaces; j++)
//				{
//					tempMesh->Faces[j].Ind0 = curMesh->mFaces->mIndices[0];
//					tempMesh->Faces[j].Ind1 = curMesh->mFaces->mIndices[1];
//					tempMesh->Faces[j].Ind2 = curMesh->mFaces->mIndices[2];
//				}
//				tempMesh->NumFaces = curMesh->mNumFaces;
//			}
//			if (curMesh->HasPositions())
//			{
//				tempMesh->Vertices = new cVertices[curMesh->mNumVertices];
//				for (int j = 0; j < curMesh->mNumVertices; j++)
//				{
//					tempMesh->Vertices[j].x = curMesh->mVertices[j].x;
//					tempMesh->Vertices[j].y = curMesh->mVertices[j].y;
//					tempMesh->Vertices[j].z = curMesh->mVertices[j].z;
//					if (curMesh->HasNormals())
//					{
//						tempMesh->Vertices[j].nx = curMesh->mNormals[j].x;
//						tempMesh->Vertices[j].ny = curMesh->mNormals[j].y;
//						tempMesh->Vertices[j].nz = curMesh->mNormals[j].z;
//					}
//					//if (curMesh->HasTextureCoords(0))
//					//{
//					//	tempMesh->Vertices[j].tx = curMesh->mTextureCoords[0][j].x;
//					//	tempMesh->Vertices[j].ty = curMesh->mTextureCoords[0][j].y;
//					//}
//				}
//				tempMesh->NumVertices = curMesh->mNumVertices;
//			}
//
//			sVAO
//		}
//	}
//}