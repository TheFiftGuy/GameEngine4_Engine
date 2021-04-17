#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(vector<vec3>()), normals(vector<vec3>()), textureCoords(vector<vec2>()), indices(vector<unsigned int>()),
normalIndices(vector<unsigned int>()), textureIndices(vector<unsigned int>()), meshVertices(vector<Vertex>()), subMeshes(vector<SubMesh>()), currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
	
}

LoadOBJModel::~LoadOBJModel()	{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const string& objFilePath_, const string& mtlFilePath_)	{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()	{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]-1];
		vert.normal = normals[normalIndices[i]-1];
		vert.textureCoordinates = textureCoords[textureIndices[i]-1];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const string& filePath_)	{
	ifstream in(filePath_.c_str(), ios::in);
	if(!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, " in LoadOBJModel.cpp", __LINE__);
		return;
	}

	string line;

	while (getline(in, line)) {
		//Vertex data
		if (line.substr(0, 2) == "v ") {
			stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(vec3(x, y, z));
		}
		//Normal data
		else if (line.substr(0, 3) == "vn ") {
			stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(vec3(x, y, z));
		}
		//TextureCoords data
		else if (line.substr(0, 3) == "vt ") {
			stringstream vt(line.substr(3));
			float x, y, z;
			vt >> x >> y >> z;
			textureCoords.push_back(vec2(x, y));
		}

		//Face data
		if (line.substr(0, 2) == "f ") {
			stringstream f(line.substr(2));

			char s;
			unsigned int verts1, verts2, verts3, texs1, texs2, texs3, norms1, norms2, norms3;
			
			f >> verts1 >> s >> texs1 >> s >> norms1 >> verts2 >> s >> texs2 >> s >> norms2 >> verts3 >> s >> texs3 >> s >> norms3;
			indices.push_back(verts1);
			indices.push_back(verts2);
			indices.push_back(verts3);
			
			textureIndices.push_back(texs1);
			textureIndices.push_back(texs2);
			textureIndices.push_back(texs3);
			
			normalIndices.push_back(norms1);
			normalIndices.push_back(norms2);
			normalIndices.push_back(norms3);
		}
		
		//New Mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if(!indices.empty()) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}

		
	}
	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.0f;
	for (auto &v : vertices) {
		if (v.x <= minX) {
			boundingBox.minVert.x = v.x;
			minX = v.x;
		}
		else if(v.x >= maxX) {
			boundingBox.maxVert.x = v.x;
			maxX = v.x;
		}
		if (v.y <= minY) {
			boundingBox.minVert.y = v.y;
			minY = v.y;
		}
		else if (v.y >= maxY) {
			boundingBox.maxVert.y = v.y;
			maxY = v.y;
		}
		if (v.z <= minZ) {
			boundingBox.minVert.z = v.z;
			minZ = v.z;
		}
		else if (v.z >= maxZ) {
			boundingBox.maxVert.z = v.z;
			maxZ = v.z;
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const string& matName_)	{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const string& matFilePath_)	{
	MaterialLoader::LoadMaterial(matFilePath_);
}