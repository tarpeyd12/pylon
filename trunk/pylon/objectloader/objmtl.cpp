#include "objectloader.h"

#include "../scriptengine/stringparser.h"

namespace ObjectLoader
{
    namespace objmtl
    {

        //union VertPos3f
        //{
            struct VertPos3f
            {
                float x, y, z;
            };
            //float pos[3];
        //};

        //union VertTex2f
        //{
            struct VertTex2f
            {
                float s, t;
            };
            //float tex[2];
        //};

        //union VertNorm3f
        //{
            struct VertNorm3f
            {
                float x, y, z;
            };
            //float norm[3];
        //};

        struct Material
        {
            std::string name;
            std::string filename;
            POGEL::IMAGE * img;
        };

        ClassList<Material>
        getMaterialsFromFile(std::string filename)
        {
            ClassList<Material> materials;

            std::string data = FileLoader::totalfile( filename );

            unsigned int numlines = ScriptEngine::Parse::getOccurrencesInString( '\n', data );

            for( unsigned int i = 0; i < numlines; ++i )
            {
                std::string currentline = ScriptEngine::Parse::getLine( data, i, '\n' );
                currentline = ScriptEngine::Parse::removeAllAfter( currentline, '#' );
                currentline = ScriptEngine::Parse::removeLeading( currentline, " \t" );
                currentline = ScriptEngine::Parse::removeTrailing( currentline, " \t\r\n\b" );
                if( !currentline.length() )
                {
                    continue;
                }
                std::string linetype = currentline.substr( 0, currentline.find_first_of(' ') );
                if( !linetype.compare("newmtl") )
                {
                    Material mat;
                    mat.filename = filename;
                    mat.name = currentline.substr(currentline.find_first_of(' ') + 1);
                    cout << "new material " << mat.name << endl;
                    mat.img = NULL;
                    materials += mat;
                }
                else
                if( !linetype.compare("map_Kd") )
                {
                    std::string imgname = currentline.substr(currentline.find_first_of(' ') + 1);
                    for(unsigned int c = 0; c < imgname.length(); ++c) if(imgname[c] == '\\') imgname[c] = '/';
                    cout << imgname << endl;
                    materials.getaddress(materials.length()-1)->img = POGEL::requestImage( "{[" + imgname + "]}" );
                }
            }
            return materials;
        }

        POGEL::OBJECT *
        newFromObjMtlTextFile( const char * filename, const char * objname, POGEL::OBJECT * object )
        {
            if( !object )
            {
                object = new POGEL::OBJECT( objname );
            }

            ClassList<VertPos3f> positions;
            ClassList<VertTex2f> texcoords;
            ClassList<VertNorm3f> normals;
            ClassList<Material> materials;

            std::string data = FileLoader::totalfile( std::string( filename ) );

            POGEL::IMAGE * img = NULL;

            unsigned int numlines = ScriptEngine::Parse::getOccurrencesInString( '\n', data );

            for( unsigned int i = 0; i < numlines; ++i )
            {
                if( !(i % 100) )
                {
                    cout << "Loading: \"" << filename << "\" " << float(i)/float(numlines)*100.0f << "%" << endl;
                }

                std::string currentline = ScriptEngine::Parse::getLine( data, i, '\n' );
                currentline = ScriptEngine::Parse::removeAllAfter( currentline, '#' );
                currentline = ScriptEngine::Parse::removeLeading( currentline, " \t" );
                currentline = ScriptEngine::Parse::removeTrailing( currentline, " \t\r\n\b" );
                if( !currentline.length() )
                {
                    continue;
                }
                std::string linetype = currentline.substr( 0, currentline.find_first_of(' ') );
                std::string linedata = currentline.substr( currentline.find_first_of(' ') );
                linedata = ScriptEngine::Parse::removeLeading( linedata, " \t" );
                if( !linetype.compare("v") )
                {
                    VertPos3f v;
                    sscanf(linedata.c_str(), "%f %f %f", &v.x, &v.y, &v.z);
                    positions += v;
                }
                else
                if( !linetype.compare("vt") )
                {
                    VertTex2f vt;
                    sscanf(linedata.c_str(), "%f %f", &vt.s, &vt.t);
                    texcoords += vt;
                }
                else
                if( !linetype.compare("vn") )
                {
                    VertNorm3f vn;
                    sscanf(linedata.c_str(), "%f %f %f", &vn.x, &vn.y, &vn.z);
                    normals += vn;
                }
                else
                if( !linetype.compare("f") )
                {
                    POGEL::TRIANGLE tri;
                    tri.setproperties( 0 );
                    //tri.setproperties( TRIANGLE_DOUBLESIDED );
                    int pos[3], tex[3], norm[3];
                    switch( ScriptEngine::Parse::getOccurrencesInString( '/', linedata ) )
                    {
                        case 0:
                            sscanf( linedata.c_str(), "%d %d %d", &pos[ 0 ], &pos[ 1 ], &pos[ 2 ] );
                        break;

                        case 3:
                            sscanf( linedata.c_str(), "%d/%d %d/%d %d/%d", &pos[ 0 ], &tex[ 0 ], &pos[ 1 ], &tex[ 1 ], &pos[ 2 ], &tex[ 2 ] );
                            tri.vertex[ 0 ].u = texcoords[ tex[ 0 ]-1 ].s; tri.vertex[ 0 ].v = -1.0f*texcoords[ tex[ 0 ]-1 ].t;
                            tri.vertex[ 1 ].u = texcoords[ tex[ 1 ]-1 ].s; tri.vertex[ 1 ].v = -1.0f*texcoords[ tex[ 1 ]-1 ].t;
                            tri.vertex[ 2 ].u = texcoords[ tex[ 2 ]-1 ].s; tri.vertex[ 2 ].v = -1.0f*texcoords[ tex[ 2 ]-1 ].t;
                        break;

                        case 6:
                            if( std::string::npos == linedata.find("//") )
                            {
                                sscanf( linedata.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &pos[0], &tex[0], &norm[0], &pos[1], &tex[1], &norm[1], &pos[2], &tex[2], &norm[2]);
                                tri.vertex[ 0 ].u = texcoords[ tex[ 0 ]-1 ].s; tri.vertex[ 0 ].v = -1.0f*texcoords[ tex[ 0 ]-1 ].t;
                                tri.vertex[ 1 ].u = texcoords[ tex[ 1 ]-1 ].s; tri.vertex[ 1 ].v = -1.0f*texcoords[ tex[ 1 ]-1 ].t;
                                tri.vertex[ 2 ].u = texcoords[ tex[ 2 ]-1 ].s; tri.vertex[ 2 ].v = -1.0f*texcoords[ tex[ 2 ]-1 ].t;
                            }
                            else
                            {
                                sscanf( linedata.c_str(), "%d//%d %d//%d %d//%d", &pos[ 0 ], &norm[ 0 ], &pos[ 1 ], &norm[ 1 ], &pos[ 2 ], &norm[ 2 ] );
                            }
                            tri.addproperty(TRIANGLE_VERTEX_NORMALS);
                            tri.vertex[ 0 ].normal = POGEL::VECTOR( normals[ norm[ 0 ]-1 ].x, normals[ norm[ 0 ]-1 ].y, normals[ norm[ 0 ]-1 ].z );
                            tri.vertex[ 1 ].normal = POGEL::VECTOR( normals[ norm[ 1 ]-1 ].x, normals[ norm[ 1 ]-1 ].y, normals[ norm[ 1 ]-1 ].z );
                            tri.vertex[ 2 ].normal = POGEL::VECTOR( normals[ norm[ 2 ]-1 ].x, normals[ norm[ 2 ]-1 ].y, normals[ norm[ 2 ]-1 ].z );
                        break;

                        default:
                            continue;
                        break;
                    }
                    tri.vertex[ 0 ] = POGEL::POINT( positions[ pos[ 0 ]-1 ].x, positions[ pos[ 0 ]-1 ].y, positions[ pos[ 0 ]-1 ].z );
                    tri.vertex[ 1 ] = POGEL::POINT( positions[ pos[ 1 ]-1 ].x, positions[ pos[ 1 ]-1 ].y, positions[ pos[ 1 ]-1 ].z );
                    tri.vertex[ 2 ] = POGEL::POINT( positions[ pos[ 2 ]-1 ].x, positions[ pos[ 2 ]-1 ].y, positions[ pos[ 2 ]-1 ].z );
                    tri.texture = img;
                    tri.updateVert();
                    object->addtriangle( tri );
                }
                else
                if( !linetype.compare("mtllib") )
                {
                    std::string matfilename = currentline.substr(currentline.find_first_of(' ') + 1);
                    cout << matfilename << endl;
                    if( !FileLoader::checkfile( matfilename ) )
                    {
                        matfilename = std::string( filename ).substr(0,std::string( filename ).find_last_of('/')) + "/" + matfilename;
                    }
                    cout << matfilename << endl;
                    if( !FileLoader::checkfile( matfilename ) )
                    {
                        cout << "Could not find '" << matfilename << "'" << endl;
                    }
                    else
                    {
                        materials += getMaterialsFromFile( matfilename );
                    }
                }
                else
                if( !linetype.compare("usemtl") )
                {
                    std::string matname = currentline.substr(currentline.find_first_of(' ') + 1);
                    cout << matname << endl;
                    for( unsigned int i = 0; i < materials.length(); ++i )
                    {
                        if( !materials[i].name.compare(matname) )
                        {
                            img = materials[i].img;
                            break;
                        }
                    }
                }
                else
                if( !linetype.compare("g") )
                {

                }
                else
                if( !linetype.compare("o") )
                {

                }
            }

            return object;
        }
    }
}
