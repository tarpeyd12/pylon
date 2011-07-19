#include "hud.h"

namespace Renderer
{
    namespace HUD
    {
        Renderer::Quad* quadList[NUM_QUAD_SLOTS];
        unsigned int lastKnownQuad = 0;

        int quadDeletionQueue[NUM_QUAD_SLOTS];
        unsigned int lastQuadDeletionQueue = 0;

        bool clearNextCycle = false;

        void Init()
        {
            lastKnownQuad = lastQuadDeletionQueue = 0;
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS; i++)
            {
                quadDeletionQueue[i] = -1;
                quadList[i] = NULL;
            }
            Renderer::HUD::addQuad(new Renderer::Quad(0,0,0,0,NULL));
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
            Renderer::HUD::addQuad(new Renderer::Quad(0,0,0,0,NULL));
        }

        int addQuad(Renderer::Quad* quad)
        {
            if(lastKnownQuad >= NUM_QUAD_SLOTS) // out of range
                return -1;
            if(quadList[lastKnownQuad] != NULL) // slot taken
                return -3;
            quadList[lastKnownQuad] = quad;
            //cout << "added quad to slot: " << lastKnownQuad << endl;
            return lastKnownQuad++;
        }

        int removeQuad(unsigned int quadIndex)
        {
            if(quadIndex >= NUM_QUAD_SLOTS) // out of range
                return -1;
            if(lastQuadDeletionQueue >= NUM_QUAD_SLOTS) // out of slots
                return -2;
            if(quadDeletionQueue[lastQuadDeletionQueue] >= 0) // destination slot taken
            {
                return -3;
            }
            quadDeletionQueue[lastQuadDeletionQueue++] = quadIndex;
            //return 0; // ok
            return lastQuadDeletionQueue-1;
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
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS && i < lastQuadDeletionQueue; i++)
                if(quadDeletionQueue[i] != -1 && quadList[quadDeletionQueue[i]] != NULL)
                {
                    Renderer::Quad* tmp = quadList[quadDeletionQueue[i]];
                    quadList[quadDeletionQueue[i]] = NULL;
                    quadDeletionQueue[i] = -1;
                    delete tmp;
                }
            bool broke = false;
            for(unsigned int i = lastKnownQuad; i >= 0; i--) if(quadList[i-0] != NULL)
            {
                lastKnownQuad = i+1;
                broke = true;
                break;
            }
            if(!broke)
                lastKnownQuad = 0;
            lastQuadDeletionQueue = 0;
            return 0; // ok
        }

        void draw()
        {
            for(unsigned int i = 0; i < NUM_QUAD_SLOTS && i < lastKnownQuad; i++)
                if(quadList[i] != NULL)
                    quadList[i]->draw();
        }


    }
}
