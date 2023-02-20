#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "mesh.h"
class BezierFace
{

	unsigned int VAO;

	//�������
	int numVertices;
	//��������
	int numIndices;
	//����
	std::vector<glm::vec3> vertices;
	//����
	std::vector<glm::vec3> normals;
	//����
	std::vector<glm::vec2> texCoords;
	//����
	std::vector<unsigned> indices;
	//��������
	void init(int prec,int x,int y);
	//���Ƶ�
	float* controlPoints;
	std::vector<glm::vec3> controlPointsVector;
	//���߽���
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
