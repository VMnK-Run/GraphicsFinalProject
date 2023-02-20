#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "mesh.h"
class BezierFace
{

	unsigned int VAO;

	//顶点个数
	int numVertices;
	//索引个数
	int numIndices;
	//顶点
	std::vector<glm::vec3> vertices;
	//法线
	std::vector<glm::vec3> normals;
	//纹理
	std::vector<glm::vec2> texCoords;
	//索引
	std::vector<unsigned> indices;
	//计算数据
	void init(int prec,int x,int y);
	//控制点
	float* controlPoints;
	std::vector<glm::vec3> controlPointsVector;
	//曲线阶数
	int step;
	float toRadians(float degrees);
	float Bernstein(float u, int index);
	float Bernstein4(float t, int index);

	Mesh mesh;
public:

	
	BezierFace();
	BezierFace(int step, float controlPoints[], int prec,const char* texturepath,int x,int y);
	int getNumVertices();
	int getNumIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec2> getTexCoords();
	std::vector<unsigned> getIndices();
	void draw(Shader& shader)
	{
		mesh.Draw(shader);
	}
	

};
