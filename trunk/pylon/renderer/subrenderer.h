#ifndef SUBRENDERER_H_INCLUDED
#define SUBRENDERER_H_INCLUDED

#include "../pogel/pogel.h"

namespace Renderer
{
    class SubRenderer;
}

#include "light.h"
#include "camera.h"
#include "physics.h"

#include "renderer.h"

namespace Renderer
{
    class SubRenderer : public POGEL::VIEW
    {
        private:
            ClassList<Renderer::Physics::Simulation*> simulationBindings;
        protected:
            POGEL::VECTOR globalTempRefpos;
            POGEL::POINT globalTempCampos;
            POGEL::POINT globalTempInvCampos;

        public:
            template<class T> inline ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > __sortedDraw(T*);

            Renderer::Camera::Viewpoint camera;
            Renderer::Lighting::Light lights[MAXNUMLIGHTS];

            SubRenderer();
            SubRenderer(std::string);
            SubRenderer(std::string,float);
            ~SubRenderer();

            void setLight(Renderer::Lighting::Light,int);

            Renderer::Physics::Simulation* getBoundSimulation(std::string);

            int addSimulationBinding(std::string);
            int removeSimulationBinding(std::string);
            int removeAllSimulationBindings();

            void scenesetup();
            void scene();

            void draw();
    };

    Renderer::SubRenderer* requestSubRenderer(std::string);
    void RenderAllSubRenderers();
}

#endif // SUBRENDERER_H_INCLUDED
