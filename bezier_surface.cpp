#include "bezier_surface.h"

void BezierFace::init(int prec,int xlen,int ylen)
{

	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++)
	{
		vertices.push_back(glm::vec3());
		normals.push_back(glm::vec3());
		texCoords.push_back(glm::vec2());
	}
	for (int i = 0; i < numIndices; i++)
	{
		indices.push_back(0);
	}
	for (int i = 0; i < (step + 1) * (step + 1) * 3; i += 3)
	{
		controlPointsVector.push_back(glm::vec3(controlPoints[i], controlPoints[i + 1], controlPoints[i + 2]));
	}
	for (int i = 0; i <= prec; i++)
	{
		for (int j = 0; j <= prec; j++)
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			float u = (float)i / prec;
			float v = (float)j / prec;

			for (int i = 0; i < xlen; i++)
			{
				for (int j = 0; j < ylen; j++)
				{
					int index = i * xlen + j;
					if (xlen == 4)
					{
						x += controlPointsVector[index].x * Bernstein(u, i) * Bernstein(v, j);
						y += controlPointsVector[index].y * Bernstein(u, i) * Bernstein(v, j);
						z += controlPointsVector[index].z * Bernstein(u, i) * Bernstein(v, j);
					}
					else if (xlen == 5)
					{
						x += controlPointsVector[index].x * Bernstein4(u, i) * Bernstein4(v, j);
						y += controlPointsVector[index].y * Bernstein4(u, i) * Bernstein4(v, j);
						z += controlPointsVector[index].z * Bernstein4(u, i) * Bernstein4(v, j);
					}
				}
			}
			vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
			normals[i * (prec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i * (prec + 1) + j] = glm::vec2((float)j / prec, (float)i / prec);
		}
	}
	//¼ÆËãË÷Òý
	for (int i = 0; i < prec; i++) {
		for (int j = 0; j < prec; j++) {
			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}
}
float BezierFace::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

float BezierFace::Bernstein(float t, int index)
{
	switch (index)
	{
	default:
	case 0:
		return pow(1.0 - t, 3);
		break;
	case 1:
		return 3 * t * pow(1.0 - t, 2);
		break;
	case 2:
		return 3 * pow(t, 2) * (1 - t);
		break;
	case 3:
		return pow(t, 3);
		break;
	}
}

float BezierFace::Bernstein4(float t, int index)
{
	switch (index)
	{
	default:
	case 0:
		return pow(1.0 - t, 4);
		break;
	case 1:
		return 4 * t * pow(1.0 - t, 3);
		break;
	case 2:
		return 6 * pow(t, 2) * pow(1 - t,2);
		break;
	case 3:
		return 4 * pow(t, 3) * (1 - t);
		break;
	case 4:
		return pow(t, 4);
		break;
	}
}


unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
BezierFace::BezierFace(int step, float controlPoints[], int prec,const char* texturepath,int x,int y)
{
	this->step = step;
	this->controlPoints = controlPoints;
	init(prec,x,y);

	auto vec_vir = this->getVertices();
	auto vec_nor = this->getNormals();
	auto vec_tex = this->getTexCoords();
	vector<Vertex>vertices(vec_vir.size());

	for (int i = 0; i < vec_vir.size(); ++i)
	{
		vertices[i].Position = vec_vir[i];
		vertices[i].Normal = vec_nor[i];
		vertices[i].TexCoords = vec_tex[i];
	}
	vector<Texture> textures;
	Texture texture;
	texture.id = TextureFromFile(texturepath, ".",false);
	texture.type = "";
	texture.path = texturepath;
	textures.push_back(texture);

	mesh = Mesh(vertices, this->getIndices(), textures);


}

int BezierFace::getNumVertices()
{
	return numVertices;
}

int BezierFace::getNumIndices()
{
	return numIndices;
}

std::vector<glm::vec3> BezierFace::getVertices()
{
	return vertices;
}

std::vector<glm::vec3> BezierFace::getNormals()
{
	return normals;
}

std::vector<glm::vec2> BezierFace::getTexCoords()
{
	return texCoords;
}

std::vector<unsigned> BezierFace::getIndices()
{
	return indices;
}



