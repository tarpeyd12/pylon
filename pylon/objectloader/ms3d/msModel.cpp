///////////////////////////////////////////////////////////////////////
// title:          MilkShape 3D Model Viewer Sample
//
// copyright:      The programs and associated files contained in this
//                 distribution were developed by Mete Ciragan.  The
//                 programs are not in the public domain, but they are
//                 freely distributable without licensing fees.  These
//                 programs are provided without guarantee or warrantee
//                 expressed or implied.  Use at your own risk!
//
// email:          mciragan@gmx.net
// web:            http://www.milkshape3d.com
///////////////////////////////////////////////////////////////////////
#include "msModel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

msModel::msModel()
{
	Clear();
}

msModel::~msModel()
{
	Clear();
}

bool msModel::Load(const char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return false;

	Clear();

	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char id[10];
	(void)fread(id, sizeof(char), 10, fp);
	if (strncmp(id, "MS3D000000", 10) != 0)
	{
		fclose(fp);
		// "This is not a valid MS3D file format!"
		return false;
	}

	int version;
	(void)fread(&version, sizeof(int), 1, fp);
	if (version != 4)
	{
		fclose(fp);
		// "This is not a valid MS3D file version!"
		return false;
	}

	int i, j;

	// vertices
	unsigned short numVertices;
	(void)fread(&numVertices, sizeof(unsigned short), 1, fp);
	m_vertices.resize(numVertices);
	for (i = 0; i < numVertices; i++)
	{
		(void)fread(&m_vertices[i].flags, sizeof(unsigned char), 1, fp);
		(void)fread(&m_vertices[i].vertex, sizeof(float), 3, fp);
		(void)fread(&m_vertices[i].boneId, sizeof(char), 1, fp);
		(void)fread(&m_vertices[i].referenceCount, sizeof(unsigned char), 1, fp);
	}

	// triangles
	unsigned short numTriangles;
	(void)fread(&numTriangles, sizeof(unsigned short), 1, fp);
	m_triangles.resize(numTriangles);
	for (i = 0; i < numTriangles; i++)
	{
		(void)fread(&m_triangles[i].flags, sizeof(unsigned short), 1, fp);
		(void)fread(m_triangles[i].vertexIndices, sizeof(unsigned short), 3, fp);
		(void)fread(m_triangles[i].vertexNormals, sizeof(float), 3 * 3, fp);
	    (void)fread(m_triangles[i].s, sizeof(float), 3, fp);
	    (void)fread(m_triangles[i].t, sizeof(float), 3, fp);
		(void)fread(&m_triangles[i].smoothingGroup, sizeof(unsigned char), 1, fp);
		(void)fread(&m_triangles[i].groupIndex, sizeof(unsigned char), 1, fp);

		// TODO: calculate triangle normal
	}

	// groups
	unsigned short numGroups;
	(void)fread(&numGroups, sizeof(unsigned short), 1, fp);
	m_groups.resize(numGroups);
	for (i = 0; i < numGroups; i++)
	{
		(void)fread(&m_groups[i].flags, sizeof(unsigned char), 1, fp);
		(void)fread(m_groups[i].name, sizeof(char), 32, fp);

		unsigned short numGroupTriangles;
		(void)fread(&numGroupTriangles, sizeof(unsigned short), 1, fp);
		m_groups[i].triangleIndices.resize(numGroupTriangles);
		if (numGroupTriangles > 0)
			(void)fread(&m_groups[i].triangleIndices[0], sizeof(unsigned short), numGroupTriangles, fp);

		(void)fread(&m_groups[i].materialIndex, sizeof(char), 1, fp);
	}

	// materials
	unsigned short numMaterials;
	(void)fread(&numMaterials, sizeof(unsigned short), 1, fp);
	m_materials.resize(numMaterials);
	for (i = 0; i < numMaterials; i++)
	{
		(void)fread(m_materials[i].name, sizeof(char), 32, fp);
		(void)fread(&m_materials[i].ambient, sizeof(float), 4, fp);
		(void)fread(&m_materials[i].diffuse, sizeof(float), 4, fp);
		(void)fread(&m_materials[i].specular, sizeof(float), 4, fp);
		(void)fread(&m_materials[i].emissive, sizeof(float), 4, fp);
		(void)fread(&m_materials[i].shininess, sizeof(float), 1, fp);
        (void)fread(&m_materials[i].transparency, sizeof(float), 1, fp);
		(void)fread(&m_materials[i].mode, sizeof(unsigned char), 1, fp);
        (void)fread(m_materials[i].texture, sizeof(char), MAX_TEXTURE_FILENAME_SIZE, fp);
        (void)fread(m_materials[i].alphamap, sizeof(char), MAX_TEXTURE_FILENAME_SIZE, fp);

		// set alpha
		m_materials[i].ambient[3] = m_materials[i].transparency;
		m_materials[i].diffuse[3] = m_materials[i].transparency;
		m_materials[i].specular[3] = m_materials[i].transparency;
		m_materials[i].emissive[3] = m_materials[i].transparency;
	}

	// animation
	(void)fread(&m_animationFps, sizeof(float), 1, fp);
	if (m_animationFps < 1.0f)
		m_animationFps = 1.0f;
	(void)fread(&m_currentTime, sizeof(float), 1, fp);
	(void)fread(&m_totalFrames, sizeof(int), 1, fp);

	// joints
	unsigned short numJoints;
	(void)fread(&numJoints, sizeof(unsigned short), 1, fp);
	m_joints.resize(numJoints);
	for (i = 0; i < numJoints; i++)
	{
		(void)fread(&m_joints[i].flags, sizeof(unsigned char), 1, fp);
		(void)(void)fread(m_joints[i].name, sizeof(char), 32, fp);
		(void)fread(m_joints[i].parentName, sizeof(char), 32, fp);
        (void)fread(m_joints[i].rot, sizeof(float), 3, fp);
        (void)fread(m_joints[i].pos, sizeof(float), 3, fp);

		unsigned short numKeyFramesRot;
		(void)fread(&numKeyFramesRot, sizeof(unsigned short), 1, fp);
		m_joints[i].rotationKeys.resize(numKeyFramesRot);

		unsigned short numKeyFramesPos;
		(void)fread(&numKeyFramesPos, sizeof(unsigned short), 1, fp);
		m_joints[i].positionKeys.resize(numKeyFramesPos);

		// the frame time is in seconds, so multiply it by the animation fps, to get the frames
		// rotation channel
		for (j = 0; j < numKeyFramesRot; j++)
		{
			(void)fread(&m_joints[i].rotationKeys[j].time, sizeof(float), 1, fp);
			(void)fread(&m_joints[i].rotationKeys[j].key, sizeof(float), 3, fp);
			m_joints[i].rotationKeys[j].time *= m_animationFps;
		}

		// translation channel
		for (j = 0; j < numKeyFramesPos; j++)
		{
			(void)fread(&m_joints[i].positionKeys[j].time, sizeof(float), 1, fp);
			(void)fread(&m_joints[i].positionKeys[j].key, sizeof(float), 3, fp);
			m_joints[i].positionKeys[j].time *= m_animationFps;
		}
	}

	// comments
	long filePos = ftell(fp);
	if (filePos < fileSize)
	{
		int subVersion = 0;
		(void)fread(&subVersion, sizeof(int), 1, fp);
		if (subVersion == 1)
		{
			int numComments = 0;
			size_t commentSize = 0;

			// group comments
			(void)fread(&numComments, sizeof(int), 1, fp);
			for (i = 0; i < numComments; i++)
			{
				int index;
				(void)fread(&index, sizeof(int), 1, fp);
				std::vector<char> comment;
				(void)fread(&commentSize, sizeof(size_t), 1, fp);
				comment.resize(commentSize);
				if (commentSize > 0)
					(void)fread(&comment[0], sizeof(char), commentSize, fp);
				if (index >= 0 && index < (int) m_groups.size())
					m_groups[index].comment = comment;
			}

			// material comments
			(void)fread(&numComments, sizeof(int), 1, fp);
			for (i = 0; i < numComments; i++)
			{
				int index;
				(void)fread(&index, sizeof(int), 1, fp);
				std::vector<char> comment;
				(void)fread(&commentSize, sizeof(size_t), 1, fp);
				comment.resize(commentSize);
				if (commentSize > 0)
					(void)fread(&comment[0], sizeof(char), commentSize, fp);
				if (index >= 0 && index < (int) m_materials.size())
					m_materials[index].comment = comment;
			}

			// joint comments
			(void)fread(&numComments, sizeof(int), 1, fp);
			for (i = 0; i < numComments; i++)
			{
				int index;
				(void)fread(&index, sizeof(int), 1, fp);
				std::vector<char> comment;
				(void)fread(&commentSize, sizeof(size_t), 1, fp);
				comment.resize(commentSize);
				if (commentSize > 0)
					(void)fread(&comment[0], sizeof(char), commentSize, fp);
				if (index >= 0 && index < (int) m_joints.size())
					m_joints[index].comment = comment;
			}

			// model comments
			(void)fread(&numComments, sizeof(int), 1, fp);
			if (numComments == 1)
			{
				std::vector<char> comment;
				(void)fread(&commentSize, sizeof(size_t), 1, fp);
				comment.resize(commentSize);
				if (commentSize > 0)
					(void)fread(&comment[0], sizeof(char), commentSize, fp);
				m_comment = comment;
			}
		}
		else
		{
			// "Unknown subversion for comments %d\n", subVersion);
		}
	}

	// vertex extra
	filePos = ftell(fp);
	if (filePos < fileSize)
	{
		int subVersion = 0;
		(void)fread(&subVersion, sizeof(int), 1, fp);
		if (subVersion == 2)
		{
			for (int i = 0; i < numVertices; i++)
			{
				(void)fread(&m_vertices[i].boneIds[0], sizeof(char), 3, fp);
				(void)fread(&m_vertices[i].weights[0], sizeof(unsigned char), 3, fp);
				(void)fread(&m_vertices[i].extra, sizeof(unsigned int), 1, fp);
			}
		}
		else if (subVersion == 1)
		{
			for (int i = 0; i < numVertices; i++)
			{
				(void)fread(&m_vertices[i].boneIds[0], sizeof(char), 3, fp);
				(void)fread(&m_vertices[i].weights[0], sizeof(unsigned char), 3, fp);
			}
		}
		else
		{
			// "Unknown subversion for vertex extra %d\n", subVersion);
		}
	}

	// joint extra
	filePos = ftell(fp);
	if (filePos < fileSize)
	{
		int subVersion = 0;
		(void)fread(&subVersion, sizeof(int), 1, fp);
		if (subVersion == 1)
		{
			for (int i = 0; i < numJoints; i++)
			{
				(void)fread(&m_joints[i].color, sizeof(float), 3, fp);
			}
		}
		else
		{
			// "Unknown subversion for joint extra %d\n", subVersion);
		}
	}

	// model extra
	filePos = ftell(fp);
	if (filePos < fileSize)
	{
		int subVersion = 0;
		(void)fread(&subVersion, sizeof(int), 1, fp);
		if (subVersion == 1)
		{
			(void)fread(&m_jointSize, sizeof(float), 1, fp);
			(void)fread(&m_transparencyMode, sizeof(int), 1, fp);
			(void)fread(&m_alphaRef, sizeof(float), 1, fp);
		}
		else
		{
			//"Unknown subversion for model extra %d\n", subVersion);
		}
	}

	fclose(fp);

	return true;
}

void msModel::Clear()
{
	m_vertices.clear();
	m_triangles.clear();
	m_groups.clear();
	m_materials.clear();
	m_animationFps = 24.0f;
	m_currentTime = 1.0f;
	m_totalFrames = 30;
	m_joints.clear();
	m_comment.clear();
	m_jointSize = 1.0f;
	m_transparencyMode = TRANSPARENCY_MODE_SIMPLE;
	m_alphaRef = 0.5f;
}

int msModel::GetNumGroups() const
{
	return (int) m_groups.size();
}

ms3d_group_t *msModel::GetGroup(int index)
{
	return &m_groups[index];
}

int msModel::GetNumTriangles() const
{
	return (int) m_triangles.size();
}

ms3d_triangle_t *msModel::GetTriangle(int index)
{
	return &m_triangles[index];
}

int msModel::GetNumVertices() const
{
	return (int) m_vertices.size();
}

ms3d_vertex_t *msModel::GetVertex(int index)
{
	return &m_vertices[index];
}

int msModel::GetNumMaterials() const
{
	return (int) m_materials.size();
}

ms3d_material_t *msModel::GetMaterial(int index)
{
	return &m_materials[index];
}

int msModel::GetNumJoints() const
{
	return (int) m_joints.size();
}

ms3d_joint_t *msModel::GetJoint(int index)
{
    if(index > GetNumJoints())
        return NULL;
	return &m_joints[index];
}

float msModel::GetJointSize() const
{
	return m_jointSize;
}

int msModel::GetTransparencyMode() const
{
	return m_transparencyMode;
}

float msModel::GetAlphaRef() const
{
	return m_alphaRef;
}

int msModel::FindJointByName(const char *name)
{
	for (size_t i = 0; i < m_joints.size(); i++)
	{
		if (strcmp(m_joints[i].name, name) == 0)
			return i;
	}

	return -1;
}

void msModel::SetupJoints()
{
	for (size_t i = 0; i < m_joints.size(); i++)
	{
		ms3d_joint_t *joint = &m_joints[i];
		joint->parentIndex = FindJointByName(joint->parentName);
		SetupTangents(i);
	}
}

void msModel::SetupTangents(size_t j)
{
	//for (size_t j = 0; j < m_joints.size(); j++)
	{
		ms3d_joint_t *joint = &m_joints[j];
		int numPositionKeys = (int) joint->positionKeys.size();
		joint->tangents.resize(numPositionKeys);

		// if there are more than 2 keys, we can calculate tangents, otherwise we use zero derivatives
		if (numPositionKeys > 2)
		{
			for (int k = 0; k < numPositionKeys; k++)
			{
				// make the curve tangents looped
				int k0 = k - 1;
				if (k0 < 0)
					k0 = numPositionKeys - 1;
				int k1 = k;
				int k2 = k + 1;
				if (k2 >= numPositionKeys)
					k2 = 0;

				// calculate the tangent, which is the vector from key[k - 1] to key[k + 1]
				float tangent[3];
				tangent[0] = (joint->positionKeys[k2].key[0] - joint->positionKeys[k0].key[0]);
				tangent[1] = (joint->positionKeys[k2].key[1] - joint->positionKeys[k0].key[1]);
				tangent[2] = (joint->positionKeys[k2].key[2] - joint->positionKeys[k0].key[2]);

				// weight the incoming and outgoing tangent by their time to avoid changes in speed, if the keys are not within the same interval
				float dt1 = joint->positionKeys[k1].time - joint->positionKeys[k0].time;
				float dt2 = joint->positionKeys[k2].time - joint->positionKeys[k1].time;
				float dt = dt1 + dt2;
				joint->tangents[k1].tangentIn[0] = tangent[0] * dt1 / dt;
				joint->tangents[k1].tangentIn[1] = tangent[1] * dt1 / dt;
				joint->tangents[k1].tangentIn[2] = tangent[2] * dt1 / dt;

				joint->tangents[k1].tangentOut[0] = tangent[0] * dt2 / dt;
				joint->tangents[k1].tangentOut[1] = tangent[1] * dt2 / dt;
				joint->tangents[k1].tangentOut[2] = tangent[2] * dt2 / dt;
			}
		}
		else
		{
		    // clear all tangents (zero derivatives)
            for (int k = 0; k < numPositionKeys; k++)
            {
                joint->tangents[k].tangentIn[0] = 0.0f;
                joint->tangents[k].tangentIn[1] = 0.0f;
                joint->tangents[k].tangentIn[2] = 0.0f;
                joint->tangents[k].tangentOut[0] = 0.0f;
                joint->tangents[k].tangentOut[1] = 0.0f;
                joint->tangents[k].tangentOut[2] = 0.0f;
            }
		}
	}
}

float msModel::GetAnimationFps() const
{
	return m_animationFps;
}

float msModel::GetCurrentFrame() const
{
	return m_currentTime;
}

int msModel::GetTotalFrames() const
{
	return m_totalFrames;
}
