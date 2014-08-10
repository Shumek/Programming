#include "functions.h"

coordinate::coordinate(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

face::face(int facen, int f1, int f2, int f3) {
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	four = false;
}

face::face(int facen, int f1, int f2, int f3, int f4) {
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	four = true;
}

int loadObject(const char* filename)
{
	std::vector<std::string*> coord;
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;
	std::ifstream in(filename);
	if (!in.is_open())
	{
		std::cout << "Not Opened" << std::endl;
		return -1;
	}
	char buf[256];
	while (!in.eof())
	{
		in.getline(buf, 256);
		coord.push_back(new std::string(buf));
	}

	for (int i = 0; i < coord.size(); i += 1)
	{
		if ((*coord[i])[0] == '#')
			continue;
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == ' ')
		{
			float tmpx, tmpy, tmpz;
			sscanf_s(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			vertex.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == 'n')
		{
			float tmpx, tmpy, tmpz;
			sscanf_s(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normals.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if ((*coord[i])[0] == 'f')
		{
			int a, b, c, d, e;
			if (count(coord[i]->begin(), coord[i]->end(), ' ') == 3)
			{
				sscanf_s(coord[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
				faces.push_back(new face(b, a, c, d));
			}
			else
			{
				sscanf_s(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
				faces.push_back(new face(b, a, c, d, e));
			}
		}
	}
	// draw
	int num;
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);
	for (int i = 0; i < faces.size(); i += 1)
	{
		if (faces[i]->four)
		{
			glBegin(GL_QUADS);
			glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);
			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);
			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);
			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);
			glVertex3f(vertex[faces[i]->faces[3] - 1]->x, vertex[faces[i]->faces[3] - 1]->y, vertex[faces[i]->faces[3] - 1]->z);
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);
			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);
			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);
			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);
			glEnd();
		}
	}

	glEndList();

	for (int i = 0; i < coord.size(); i += 1)
		delete coord[i];
	for (int i = 0; i < faces.size(); i += 1)
		delete faces[i];
	for (int i = 0; i < normals.size(); i += 1)
		delete normals[i];
	for (int i = 0; i < vertex.size(); i += 1)
		delete vertex[i];

	return num;
}

void drawCube(float size)
{
	glBegin(GL_QUADS);
	// front face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	// left face
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	// back face
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	// right face
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// top face
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// bottom face
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
}