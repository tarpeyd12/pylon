#include "hud.h"

namespace Renderer
{
    namespace HUD
    {
        Renderer::Quad* quadList[NUM_QUAD_SLOTS];
        unsigned int lastKnownQuad = 0;

        int quadDeletionQueue[NUM_QUAD_SLOTS];
        unsigned int lastQuadDeletionQueue = 0;

        Renderer::Quad* quadInsertQueue[NUM_QUAD_SLOTS];
        unsigned int lastQuadInsertQueue = 0;

        Renderer::Quad* quadUpdateQueue[NUM_QUAD_SLOTS];

        bool clearNextCycle = false;

        void Init()
        {
            lastKnownQuad = lastQuadDeletionQueue = lastQuadInsertQueue = 0;
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS; i++)
            {
                quadDeletionQueue[i] = -1;
                quadList[i] = quadInsertQueue[i] = quadUpdateQueue[i] = NULL;
            }
            //Renderer::HUD::addQuad(new Renderer::Quad(0,0,0,0,NULL));
        }

        void Clear()
        {
            lastKnownQuad = lastQuadDeletionQueue = 0;
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS; i++)
            {
                quadDeletionQueue[i] = -1;
                if(quadList[i] != NULL)
                {
                    delete quadList[i];
                    quadList[i] = NULL;
                }
            }
            //Renderer::HUD::addQuad(new Renderer::Quad(0,0,0,0,NULL));
        }

        int addQuad(Renderer::Quad* quad)
        {
            /*if(lastKnownQuad >= NUM_QUAD_SLOTS) // out of range
                return -1;
            if(quadList[lastKnownQuad] != NULL) // slot taken
            {
                lastKnownQuad++;
                return addQuad(quad);
                //return -3;
            }
            quadList[lastKnownQuad] = quad;
            //cout << "added quad to slot: " << lastKnownQuad << endl;
            return lastKnownQuad++;*/

            if(lastQuadInsertQueue >= NUM_QUAD_SLOTS) // out of available add slots
                return -1;
            if(quadInsertQueue[lastQuadInsertQueue] != NULL) // slot taken
            {
                lastQuadInsertQueue++;
                return addQuad(quad);
                //return -3;
            }
            quadInsertQueue[lastQuadInsertQueue] = quad;
            return lastQuadInsertQueue++;
        }

        int updateQuad(Renderer::Quad* quad, int quadID)
        {
            if(quadID >= NUM_QUAD_SLOTS || quadID < 0) // out of range
                return -1;
            if(quadUpdateQueue[quadID] != NULL) // slot taken
            {
                Renderer::Quad* quadTmp = quadUpdateQueue[quadID];
                quadUpdateQueue[quadID] = quad;
                delete quadTmp;
            }
            else
                quadUpdateQueue[quadID] = quad;
            return quadID;
        }

        int removeQuad(unsigned int quadIndex)
        {
            if(quadIndex >= NUM_QUAD_SLOTS) // out of range
                return -1;
            if(lastQuadDeletionQueue >= NUM_QUAD_SLOTS) // out of slots
                return -2;
            if(quadDeletionQueue[lastQuadDeletionQueue] >= 0) // destination slot taken
            {
                lastQuadDeletionQueue++;
                return removeQuad(quadIndex);
                //return -3;
            }
            quadDeletionQueue[lastQuadDeletionQueue] = quadIndex;
            //return 0; // ok
            return lastQuadDeletionQueue++;
        }

        int checkQuad(unsigned int quadIndex)
        {
            if(quadIndex >= NUM_QUAD_SLOTS) // out of range
                return -1;
            if(quadList[quadIndex] != NULL) // slot taken
                return -3;
            return 0;
        }

        int removeQuadCycle()
        {
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS /*&& i < lastQuadDeletionQueue*/; i++)
                if(quadDeletionQueue[i] != -1 && quadList[quadDeletionQueue[i]] != NULL)
                {
                    Renderer::Quad* tmp = quadList[quadDeletionQueue[i]];
                    quadList[quadDeletionQueue[i]] = NULL;
                    cout << "removed quad" << quadDeletionQueue[i] << endl;
                    quadDeletionQueue[i] = -1;
                    delete tmp;

                }
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS; i++)
                if(quadList[i] != NULL)
                    lastKnownQuad = i+1;
            lastQuadDeletionQueue = 0;
            return 0; // ok
        }

        int addQuadCycle()
        {
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS && i < lastQuadInsertQueue; i++)
                if(quadInsertQueue[i] != NULL && lastKnownQuad < NUM_QUAD_SLOTS)
                {
                    quadList[lastKnownQuad] = quadInsertQueue[i];
                    quadInsertQueue[i] = NULL;
                }
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS; i++)
                if(quadList[i] != NULL)
                    lastKnownQuad = i+1;
            lastQuadInsertQueue = 0;
            return 0; // ok
        }

        int updateQuadCycle()
        {
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS; i++)
            {
                if(quadUpdateQueue[i] != NULL)
                {
                    if(quadList[i] != NULL)
                    {
                        Renderer::Quad* quadTmp = quadList[i];
                        quadList[i] = quadUpdateQueue[i];
                        delete quadTmp;
                    }
                    else
                    {
                        if(i >= lastKnownQuad)
                            lastKnownQuad = i;
                        quadList[i] = quadUpdateQueue[i];
                    }
                    quadUpdateQueue[i] = NULL;
                }
            }
            return 0; // ok
        }

        void draw()
        {
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS /*&& i < lastKnownQuad*/; i++)
                if(quadList[i] != NULL)
                    quadList[i]->draw();
        }


    }
}
