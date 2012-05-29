#include "objectloader.h"

#include "ms3d/msModel.h"

namespace ObjectLoader
{
    namespace ms3d
    {
        POGEL::OBJECT *
        newFromMs3dBinFile( const char * filename, const char * objname, POGEL::OBJECT * object )
        {
            msModel * mdl = new msModel();
            if(!mdl->Load(filename))
                return NULL;
            mdl->SetupJoints();

            if( !object )
            {
                object = new POGEL::OBJECT(objname);
            }

            object->setNumFrames(mdl->GetTotalFrames());
            object->setAnimationFPS(mdl->GetAnimationFps());

            for( int i = 0; i < mdl->GetNumVertices(); ++i )
            {
                ms3d_vertex_t * verttmp = mdl->GetVertex(i);
                POGEL::VERTEX vert;
                vert.x = verttmp->vertex[0];
                vert.y = verttmp->vertex[1];
                vert.z = verttmp->vertex[2];
                vert.boneID = verttmp->boneId;
                for( int a = 0; a < 3; ++a )
                {
                    vert.boneIDs[a] = verttmp->boneIds[a];
                    vert.weights[a] = verttmp->weights[a];
                }
                object->addVertex(vert);
            }

            object->addtrianglespace((unsigned long)mdl->GetNumTriangles());

            ClassList<int> failedParented(mdl->GetNumJoints());

            for( int i = 0; i < mdl->GetNumJoints(); ++i )
            {
                ms3d_joint_t * tmpjoint = mdl->GetJoint(i);
                char* name = new char[strlen(tmpjoint->name)];
                POGEL::OBJECT * pjoint = new POGEL::OBJECT(strcpy(name,tmpjoint->name));

                pjoint->position.x = tmpjoint->pos[0];
                pjoint->position.y = tmpjoint->pos[1];
                pjoint->position.z = tmpjoint->pos[2];

                for( int a = 0; a < (int)tmpjoint->positionKeys.size(); ++a )
                {
                    ms3d_keyframe_t * kf = &tmpjoint->positionKeys[a];
                    POGEL::KEY k(POGEL::POINT(kf->key[0],kf->key[1],kf->key[2]),kf->time);
                    pjoint->addPosKey(k);
                }


                // IMPORTANT: x = 1, y = 2, z = 0
                pjoint->rotation.x = tmpjoint->rot[1];
                pjoint->rotation.y = tmpjoint->rot[2];
                pjoint->rotation.z = tmpjoint->rot[0];

                for( int a = 0; a < (int)tmpjoint->rotationKeys.size(); ++a )
                {
                    ms3d_keyframe_t * kf = &tmpjoint->rotationKeys[a];
                    // IMPORTANT: x = 1, y = 2, z = 0
                    POGEL::KEY k(POGEL::POINT(kf->key[1],kf->key[2],kf->key[0]),kf->time);
                    pjoint->addRotKey(k);
                }

                for( int a = 0; a < (int)tmpjoint->tangents.size(); ++a )
                {
                    ms3d_tangent_t * ktan = &tmpjoint->tangents[a];
                    POGEL::POINT in( ktan->tangentIn[0], ktan->tangentIn[1], ktan->tangentIn[2] );
                    POGEL::POINT out( ktan->tangentOut[0], ktan->tangentOut[1], ktan->tangentOut[2] );
                    POGEL::TANGENT tan( in, out );
                    pjoint->addTangent( tan );
                }

                pjoint->addproperty(OBJECT_DRAW_CHILDREN);

                object->addJoint(pjoint, NULL);
                failedParented += i;
            }

            for( int n = 0; n < (int)failedParented.length(); ++n )
            {
                int i = failedParented[n];
                ms3d_joint_t * tmpjoint = mdl->GetJoint(i);
                POGEL::OBJECT * dec = object->getJoint(tmpjoint->parentName);
                POGEL::OBJECT * jnt = object->getJoint(tmpjoint->name);
                if( dec != NULL && jnt != NULL )
                {
                    //cout << "adding a joint to " << tmpjoint->parentName << endl;
                    dec->addobject(jnt);
                }
                else
                {
                    cout << "failed to add a joint to " << tmpjoint->parentName << endl;
                    if(!jnt)
                    {
                        cout << "jnt is null" << endl;
                    }
                    else
                    {
                        cout << "dec is null" << endl;
                        dec = object;
                        dec->addobject(jnt);
                    }
                }
            }

            failedParented.clear();

            POGEL::VERTEX* objverts = object->getVertexListAddress();

            int numverts = (int)mdl->GetNumVertices();

            for( int i = 0; i < mdl->GetNumTriangles(); ++i )
            {
                ms3d_triangle_t * tritmp = mdl->GetTriangle(i);

                int v1 = (int)tritmp->vertexIndices[ 0 ];
                int v2 = (int)tritmp->vertexIndices[ 1 ];
                int v3 = (int)tritmp->vertexIndices[ 2 ];

                POGEL::TRIANGLE tri(objverts,numverts,v1,v2,v3,NULL,TRIANGLE_VERTEX_NORMALS);
                //POGEL::TRIANGLE tri(objverts,numverts,v1,v2,v3,NULL,TRIANGLE_LIT);

                /*tri.normal.x = tritmp->normal[0];
                tri.normal.y = tritmp->normal[1];
                tri.normal.z = tritmp->normal[2];*/

                for( int a = 0; a < 3; ++a )
                {
                    tri.vertex[a].u = tritmp->s[ a ];
                    tri.vertex[a].v = tritmp->t[ a ];

                    tri.vertex[a].normal.x = tritmp->vertexNormals[ a ][ 0 ];
                    tri.vertex[a].normal.y = tritmp->vertexNormals[ a ][ 1 ];
                    tri.vertex[a].normal.z = tritmp->vertexNormals[ a ][ 2 ];
                    tri.vertnormals[a] = tri.vertex[a].normal;
                }

                object->addtriangle(tri);
            }

            objverts = NULL;

            POGEL::TRIANGLE * trilist = object->gettrianglelist();

            for( int i = 0; i < mdl->GetNumGroups(); ++i )
            {
                ms3d_group_t * group = mdl->GetGroup(i);

                if( group->materialIndex < 0 || group->materialIndex >= mdl->GetNumMaterials() )
                {
                    continue;
                }

                ms3d_material_t * material = mdl->GetMaterial(group->materialIndex);

                int texnamelen = strlen(material->texture);
                if( !texnamelen )
                {
                    continue;
                }

                for( int c = 0; c < texnamelen; ++c)
                {
                    if( material->texture[c] == '\\')
                    {
                        material->texture[c] = '/';
                    }
                }

                if( material->texture[0] == '.' )
                {
                    for( int c = 0; c < texnamelen-1; ++c)
                    {
                        material->texture[c] = material->texture[c+1];
                    }
                    material->texture[--texnamelen] = '\0';
                }

                if( material->texture[0] == '/' )
                {
                    for( int c = 0; c < texnamelen-1; ++c)
                    {
                        material->texture[c] = material->texture[c+1];
                    }
                    material->texture[--texnamelen] = '\0';
                }

                for( int p = 0; p < (int)group->triangleIndices.size(); ++p)
                {
                    trilist[group->triangleIndices[p]].texture = POGEL::requestImage("{["+std::string(material->texture)+"]}");
                }
            }

            trilist = NULL;

            object->addproperty(OBJECT_DRAW_CHILDREN);

            //object->build();

            mdl->Clear();

            delete mdl;

            return object;
        }
    }
}
